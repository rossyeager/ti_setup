//#############################################################################
//
//  File:   f2802x_examples/ecap_capture_pwm/Example_F2802xECap_Capture_Pwm.c
//
//  Title:  Capture EPwm3.
//
//  Group:          C2000
//  Target Device:  TMS320F2802x
//
//! \addtogroup example_list
//!  <h1>ECAP Capture EPwm3</h1>
//!
//!   This example configures EPWM3A for:
//!   - Up count
//!   - Period starts at 2 and goes up to 1000
//!   - Toggle output on PRD
//!
//!   eCAP1 is configured to capture the time between rising
//!   and falling edge of the PWM3A output.  Connect eCAP1 (GPIO5) to 
//!   ePWM3A (GPIO4).
//
//  (C) Copyright 2012, Texas Instruments, Inc.
//#############################################################################
// $TI Release: PACKAGE NAME $
// $Release Date: PACKAGE RELEASE DATE $
//#############################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

#include "f2802x_common/include/clk.h"
#include "f2802x_common/include/flash.h"
#include "f2802x_common/include/gpio.h"
#include "f2802x_common/include/pie.h"
#include "f2802x_common/include/pll.h"
#include "f2802x_common/include/pwm.h"
#include "f2802x_common/include/cap.h"
#include "f2802x_common/include/wdog.h"

// Configure the start/end period for the timer
#define PWM3_TIMER_MIN     10
#define PWM3_TIMER_MAX     8000

// Prototype statements for functions found within this file.
__interrupt void ecap1_isr(void);
void InitECapture(void);
void InitEPwmTimer(void);
void Fail(void);

// Global variables used in this example
uint32_t  ECap1IntCount;
uint32_t  ECap1PassCount;
uint32_t  EPwm3TimerDirection;

// To keep track of which way the timer value is moving
#define EPwm_TIMER_UP   1
#define EPwm_TIMER_DOWN 0

CAP_Handle myCap;
CLK_Handle myClk;
FLASH_Handle myFlash;
GPIO_Handle myGpio;
PIE_Handle myPie;
PWM_Handle myPwm;

void main(void)
{
    
    CPU_Handle myCpu;
    PLL_Handle myPll;
    WDOG_Handle myWDog;
    
    // Initialize all the handles needed for this application    
    myCap = CAP_init((void *)CAPA_BASE_ADDR, sizeof(CAP_Obj));
    myClk = CLK_init((void *)CLK_BASE_ADDR, sizeof(CLK_Obj));
    myCpu = CPU_init((void *)NULL, sizeof(CPU_Obj));
    myFlash = FLASH_init((void *)FLASH_BASE_ADDR, sizeof(FLASH_Obj));
    myGpio = GPIO_init((void *)GPIO_BASE_ADDR, sizeof(GPIO_Obj));
    myPie = PIE_init((void *)PIE_BASE_ADDR, sizeof(PIE_Obj));
    myPll = PLL_init((void *)PLL_BASE_ADDR, sizeof(PLL_Obj));
    myPwm = PWM_init((void *)PWM_ePWM3_BASE_ADDR, sizeof(PWM_Obj));
    myWDog = WDOG_init((void *)WDOG_BASE_ADDR, sizeof(WDOG_Obj));
    
    // Perform basic system initialization    
    WDOG_disable(myWDog);
    CLK_enableAdcClock(myClk);
    (*Device_cal)();
    CLK_disableAdcClock(myClk);
    
    //Select the internal oscillator 1 as the clock source
    CLK_setOscSrc(myClk, CLK_OscSrc_Internal);
    
    // Setup the PLL for x10 /2 which will yield 50Mhz = 10Mhz * 10 / 2
    PLL_setup(myPll, PLL_Multiplier_10, PLL_DivideSelect_ClkIn_by_2);
    
    // Disable the PIE and all interrupts
    PIE_disable(myPie);
    PIE_disableAllInts(myPie);
    CPU_disableGlobalInts(myCpu);
    CPU_clearIntFlags(myCpu);
    
    // If running from flash copy RAM only functions to RAM   
#ifdef _FLASH
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
#endif      

    // Initalize GPIO
    GPIO_setPullUp(myGpio, GPIO_Number_4, GPIO_PullUp_Disable);
    GPIO_setMode(myGpio, GPIO_Number_4, GPIO_4_Mode_EPWM3A);
    
    GPIO_setPullUp(myGpio, GPIO_Number_5, GPIO_PullUp_Enable);
    GPIO_setQualification(myGpio, GPIO_Number_5, GPIO_Qual_Sync);
    GPIO_setMode(myGpio, GPIO_Number_5, GPIO_5_Mode_ECAP1);

    // Setup a debug vector table and enable the PIE
    PIE_setDebugIntVectorTable(myPie);
    PIE_enable(myPie);

    // Register interrupt handlers in the PIE vector table
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_4, PIE_SubGroupNumber_1, (intVec_t)&ecap1_isr);

    // Setup peripherals used in this example
    InitEPwmTimer();    
    InitECapture();

    // Initalize counters:
    ECap1IntCount = 0;
    ECap1PassCount = 0;

    // Enable CPU INT4 which is connected to ECAP1-4 INT:
    CPU_enableInt(myCpu, CPU_IntNumber_4);

    // Enable eCAP INTn in the PIE: Group 3 interrupt 1-6
    PIE_enableCaptureInt(myPie);

    // Enable global Interrupts and higher priority real-time debug events:
    CPU_enableGlobalInts(myCpu);
    CPU_enableDebugInt(myCpu);

    for(;;)
    {
        __asm("          NOP");
    }

}

void InitEPwmTimer()
{
    
    CLK_disableTbClockSync(myClk);
    CLK_enablePwmClock(myClk, PWM_Number_3);

    PWM_setCounterMode(myPwm, PWM_CounterMode_Up);
    PWM_setPeriod(myPwm, PWM3_TIMER_MIN);
    PWM_setPhase(myPwm, 0x00000000);
    PWM_setActionQual_Period_PwmA(myPwm, PWM_ActionQual_Toggle);

    // TBCLK = SYSCLKOUT
    PWM_setHighSpeedClkDiv(myPwm, PWM_HspClkDiv_by_2);
    PWM_setClkDiv(myPwm, PWM_ClkDiv_by_1);

    EPwm3TimerDirection = EPwm_TIMER_UP;

    CLK_enableTbClockSync(myClk);

}



void InitECapture()
{
    
    CLK_enableEcap1Clock(myClk);

    CAP_disableInt(myCap, CAP_Int_Type_All);    // Disable all capture interrupts
    CAP_clearInt(myCap, CAP_Int_Type_All);      // Clear all CAP interrupt flags
    CAP_disableCaptureLoad(myCap);              // Disable CAP1-CAP4 register loads
    CAP_disableTimestampCounter(myCap);         // Make sure the counter is stopped

    // Configure peripheral registers
    CAP_setCapOneShot(myCap);                   // One-shot
    CAP_setStopWrap(myCap, CAP_Stop_Wrap_CEVT4);// Stop at 4 events
    CAP_setCapEvtPolarity(myCap, CAP_Event_1, CAP_Polarity_Falling);    // Falling edge
    CAP_setCapEvtPolarity(myCap, CAP_Event_2, CAP_Polarity_Rising);     // Rising edge
    CAP_setCapEvtPolarity(myCap, CAP_Event_3, CAP_Polarity_Falling);    // Falling edge
    CAP_setCapEvtPolarity(myCap, CAP_Event_4, CAP_Polarity_Rising);     // Rising edge
    
    CAP_setCapEvtReset(myCap, CAP_Event_1, CAP_Reset_Enable);   // Difference operation
    CAP_setCapEvtReset(myCap, CAP_Event_2, CAP_Reset_Enable);   // Difference operation
    CAP_setCapEvtReset(myCap, CAP_Event_3, CAP_Reset_Enable);   // Difference operation
    CAP_setCapEvtReset(myCap, CAP_Event_4, CAP_Reset_Enable);   // Difference operation
    
    CAP_enableSyncIn(myCap);                    // Enable sync in
    CAP_setSyncOut(myCap, CAP_SyncOut_SyncIn);  // Pass through
    
    CAP_enableCaptureLoad(myCap);

    CAP_enableTimestampCounter(myCap);          // Start Counter
    CAP_rearm(myCap);                           // arm one-shot
    CAP_enableCaptureLoad(myCap);               // Enable CAP1-CAP4 register loads
    CAP_enableInt(myCap, CAP_Int_Type_CEVT4);   // 4 events = interrupt

}

__interrupt void ecap1_isr(void)
{

    // Cap input is syc'ed to SYSCLKOUT so there may be
    // a +/- 1 cycle variation

    if(CAP_getCap2(myCap) > PWM_getPeriod(myPwm)*2+1 || CAP_getCap2(myCap) < PWM_getPeriod(myPwm)*2-1)
    {
        Fail();
    }

    if(CAP_getCap3(myCap) > PWM_getPeriod(myPwm)*2+1 || CAP_getCap3(myCap) < PWM_getPeriod(myPwm)*2-1)
    {
        Fail();
    }

    if(CAP_getCap4(myCap) > PWM_getPeriod(myPwm)*2+1 || CAP_getCap4(myCap) < PWM_getPeriod(myPwm)*2-1)
    {
        Fail();
    }

    ECap1IntCount++;

    if(EPwm3TimerDirection == EPwm_TIMER_UP) {
        if(PWM_getPeriod(myPwm) < PWM3_TIMER_MAX) {
            PWM_setPeriod(myPwm, PWM_getPeriod(myPwm) + 1);
        }
        else {
            EPwm3TimerDirection = EPwm_TIMER_DOWN;
            PWM_setPeriod(myPwm, PWM_getPeriod(myPwm) - 1);
        }
    }
    else {
        if(PWM_getPeriod(myPwm) > PWM3_TIMER_MIN) {
            PWM_setPeriod(myPwm, PWM_getPeriod(myPwm) - 1);
        }
        else {
            EPwm3TimerDirection = EPwm_TIMER_UP;
            PWM_setPeriod(myPwm, PWM_getPeriod(myPwm) + 1);
        }
    }

    ECap1PassCount++;

    CAP_clearInt(myCap, CAP_Int_Type_CEVT4);
    CAP_clearInt(myCap, CAP_Int_Type_Global);
    CAP_rearm(myCap);

    // Acknowledge this interrupt to receive more interrupts from group 4
    PIE_clearInt(myPie, PIE_GroupNumber_4);
}

void Fail()
{
    __asm("   ESTOP0");
}

//===========================================================================
// No more.
//===========================================================================
