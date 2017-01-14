//#############################################################################
//
//  File:   f2802x_examples_ccsv4/epwm_timer_interrupts/Example_F2802xEPwmTimerInt.c
//
//  Title:  F2802x ePWM Timer Interrupt example.
//
//  Group:          C2000
//  Target Device:  TMS320F2802x
//
//! \addtogroup example_list
//!  <h1>PWM Timer Interrupt</h1>
//!
//!   This example configures the ePWM Timers and increments
//!   a counter each time an interrupt is taken.
//!
//!   As supplied:
//!
//!   All ePWM's are initalized.
//!
//!   All timers have the same period. \n
//!   The timers are started sync'ed. \n
//!   An interrupt is taken on a zero event for each ePWM timer.
//!
//!      ePWM1: takes an interrupt every event \n
//!      ePWM2: takes an interrupt every 2nd event \n
//!      ePWM3: takes an interrupt every 3rd event 
//!
//!   Thus the Interrupt count for ePWM1 and ePWM4 should be equal.
//!   The interrupt count for ePWM2 should be about half that of ePWM1,
//!   and the interrupt count for ePWM3 should be about 1/3 that of ePWM1
//!
//!   Watch Variables:
//!   - EPwm1TimerIntCount
//!   - EPwm2TimerIntCount
//!   - EPwm3TimerIntCount
//
//  (C) Copyright 2012, Texas Instruments, Inc.
//#############################################################################
// $TI Release: f2802x Support Library v210 $
// $Release Date: Mon Sep 17 09:13:31 CDT 2012 $
//#############################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

#include "f2802x_common/include/clk.h"
#include "f2802x_common/include/flash.h"
#include "f2802x_common/include/gpio.h"
#include "f2802x_common/include/pie.h"
#include "f2802x_common/include/pll.h"
#include "f2802x_common/include/pwm.h"
#include "f2802x_common/include/wdog.h"

// Configure which ePWM timer interrupts are enabled at the PIE level:
// 1 = enabled,  0 = disabled
#define PWM1_INT_ENABLE  1
#define PWM2_INT_ENABLE  1
#define PWM3_INT_ENABLE  1

// Configure the period for each timer
#define PWM1_TIMER_TBPRD   0x1FFF
#define PWM2_TIMER_TBPRD   0x1FFF
#define PWM3_TIMER_TBPRD   0x1FFF


// Prototype statements for functions found within this file.
interrupt void epwm1_timer_isr(void);
interrupt void epwm2_timer_isr(void);
interrupt void epwm3_timer_isr(void);
void InitEPwmTimer(void);

// Global variables used in this example
uint32_t  EPwm1TimerIntCount;
uint32_t  EPwm2TimerIntCount;
uint32_t  EPwm3TimerIntCount;

CLK_Handle myClk;
FLASH_Handle myFlash;
GPIO_Handle myGpio;
PIE_Handle myPie;
PWM_Handle myPwm1, myPwm2, myPwm3;

void main(void)
{
    int i;
    CPU_Handle myCpu;
    PLL_Handle myPll;
    WDOG_Handle myWDog;
    
    // Initialize all the handles needed for this application    
    myClk = CLK_init((void *)CLK_BASE_ADDR, sizeof(CLK_Obj));
    myCpu = CPU_init((void *)NULL, sizeof(CPU_Obj));
    myFlash = FLASH_init((void *)FLASH_BASE_ADDR, sizeof(FLASH_Obj));
    myGpio = GPIO_init((void *)GPIO_BASE_ADDR, sizeof(GPIO_Obj));
    myPie = PIE_init((void *)PIE_BASE_ADDR, sizeof(PIE_Obj));
    myPll = PLL_init((void *)PLL_BASE_ADDR, sizeof(PLL_Obj));
    myPwm1 = PWM_init((void *)PWM_ePWM1_BASE_ADDR, sizeof(PWM_Obj));
    myPwm2 = PWM_init((void *)PWM_ePWM2_BASE_ADDR, sizeof(PWM_Obj));
    myPwm3 = PWM_init((void *)PWM_ePWM3_BASE_ADDR, sizeof(PWM_Obj));
    myWDog = WDOG_init((void *)WDOG_BASE_ADDR, sizeof(WDOG_Obj));
    
    // Perform basic system initialization    
    WDOG_disable(myWDog);
    CLK_enableAdcClock(myClk);
    (*Device_cal)();
    CLK_disableAdcClock(myClk);
    
    //Select the internal oscillator 1 as the clock source
    CLK_setOscSrc(myClk, CLK_OscSrc_Internal);
    
    // Setup the PLL for x12 /2 which will yield 60Mhz = 10Mhz * 12 / 2
    PLL_setup(myPll, PLL_Multiplier_12, PLL_DivideSelect_ClkIn_by_2);
    
    // Disable the PIE and all interrupts
    PIE_disable(myPie);
    PIE_disableAllInts(myPie);
    CPU_disableGlobalInts(myCpu);
    CPU_clearIntFlags(myCpu);
    
    // If running from flash copy RAM only functions to RAM   
#ifdef _FLASH
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
#endif 

    // Setup a debug vector table and enable the PIE
    PIE_setDebugIntVectorTable(myPie);
    PIE_enable(myPie);
    
    // Register interrupt handlers in the PIE vector table
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_3, PIE_SubGroupNumber_1, (intVec_t)&epwm1_timer_isr);
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_3, PIE_SubGroupNumber_2, (intVec_t)&epwm2_timer_isr);
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_3, PIE_SubGroupNumber_3, (intVec_t)&epwm3_timer_isr);

    InitEPwmTimer();    // For this example, only initialize the ePWM Timers

    // Initalize counters:
    EPwm1TimerIntCount = 0;
    EPwm2TimerIntCount = 0;
    EPwm3TimerIntCount = 0;

    // Enable CPU INT3 which is connected to EPWM1-6 INT
    CPU_enableInt(myCpu, CPU_IntNumber_3);

    // Enable EPWM INTn in the PIE: Group 3 interrupt 1-6
    PIE_enablePwmInt(myPie, PWM_Number_1);
    PIE_enablePwmInt(myPie, PWM_Number_2);
    PIE_enablePwmInt(myPie, PWM_Number_3);

    // Enable global Interrupts and higher priority real-time debug events
    CPU_enableGlobalInts(myCpu);
    CPU_enableDebugInt(myCpu);

    for(;;) {
        asm(" NOP");
        for(i=1;i<=10;i++) {
        }
    }
}


void InitEPwmTimer()
{

    // Stop all the TB clocks
    CLK_disableTbClockSync(myClk);
    
    CLK_enablePwmClock(myClk, PWM_Number_1);
    CLK_enablePwmClock(myClk, PWM_Number_2);
    CLK_enablePwmClock(myClk, PWM_Number_3);

    // Setup Sync
    PWM_setSyncMode(myPwm1, PWM_SyncMode_EPWMxSYNC);
    PWM_setSyncMode(myPwm2, PWM_SyncMode_EPWMxSYNC);
    PWM_setSyncMode(myPwm3, PWM_SyncMode_EPWMxSYNC);

    // Allow each timer to be sync'ed
    PWM_enableCounterLoad(myPwm1);
    PWM_enableCounterLoad(myPwm2);
    PWM_enableCounterLoad(myPwm3);

    PWM_setPhase(myPwm1, 100);
    PWM_setPhase(myPwm2, 200);
    PWM_setPhase(myPwm3, 300);

    PWM_setPeriod(myPwm1, PWM1_TIMER_TBPRD);
    PWM_setCounterMode(myPwm1, PWM_CounterMode_Up);         // Count up
    PWM_setIntMode(myPwm1, PWM_IntMode_CounterEqualZero);   // Select INT on Zero event
    PWM_enableInt(myPwm1);                                  // Enable INT
    PWM_setIntPeriod(myPwm1, PWM_IntPeriod_FirstEvent);     // Generate INT on 1st event

    PWM_setPeriod(myPwm2, PWM2_TIMER_TBPRD);
    PWM_setCounterMode(myPwm2, PWM_CounterMode_Up);         // Count up
    PWM_setIntMode(myPwm2, PWM_IntMode_CounterEqualZero);   // Enable INT on Zero event
    PWM_enableInt(myPwm2);                                  // Enable INT
    PWM_setIntPeriod(myPwm2, PWM_IntPeriod_SecondEvent);    // Generate INT on 2nd event

    PWM_setPeriod(myPwm3, PWM3_TIMER_TBPRD);
    PWM_setCounterMode(myPwm3, PWM_CounterMode_Up);         // Count up
    PWM_setIntMode(myPwm3, PWM_IntMode_CounterEqualZero);   // Enable INT on Zero event
    PWM_enableInt(myPwm3);                                  // Enable INT
    PWM_setIntPeriod(myPwm3, PWM_IntPeriod_ThirdEvent);     // Generate INT on 3rd event

    // Start all the timers synced
    CLK_enableTbClockSync(myClk);

}


// Interrupt routines uses in this example:
interrupt void epwm1_timer_isr(void)
{
    EPwm1TimerIntCount++;

    // Clear INT flag for this timer
    PWM_clearIntFlag(myPwm1);

    // Acknowledge this interrupt to receive more interrupts from group 3
    PIE_clearInt(myPie, PIE_GroupNumber_3);
}

interrupt void epwm2_timer_isr(void)
{
    EPwm2TimerIntCount++;

    // Clear INT flag for this timer
    PWM_clearIntFlag(myPwm2);

    // Acknowledge this interrupt to receive more interrupts from group 3
    PIE_clearInt(myPie, PIE_GroupNumber_3);
}

interrupt void epwm3_timer_isr(void)
{
    EPwm3TimerIntCount++;

    // Clear INT flag for this timer
    PWM_clearIntFlag(myPwm3);

    // Acknowledge this interrupt to receive more interrupts from group 3
    PIE_clearInt(myPie, PIE_GroupNumber_3);
}





//===========================================================================
// No more.
//===========================================================================
