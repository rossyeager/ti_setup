//#############################################################################
//
//  File:   f2802x_examples_ccsv4/epwm_deadband/Example_F2802xEpwmDeadBand.c
//
//  Title:  Check PWM deadband generation
//
//  Group:          C2000
//  Target Device:  TMS320F2802x
//
//! \addtogroup example_list
//!  <h1>PWM deadband generation</h1>
//!
//!   This example configures ePWM1, ePWM2 and ePWM3 for:
//!   - Count up/down
//!   - Deadband
//!
//!   3 Examples are included:
//!   - ePWM1: Active low PWMs
//!   - ePWM2: Active low complementary PWMs
//!   - ePWM3: Active high complementary PWMs
//!
//!   Each ePWM is configured to interrupt on the 3rd zero event/
//!   When this happens, the deadband is modified such that
//!   0 <= DB <= DB_MAX.  That is, the deadband will move up and
//!   down between 0 and the maximum value.
//!
//!   View the EPWM1A/B, EPWM2A/B and EPWM3A/B waveforms
//!   via an oscilloscope:
//!      EPWM1A is on GPIO0 \n
//!      EPWM1B is on GPIO1
//!
//!      EPWM2A is on GPIO2 \n
//!      EPWM2B is on GPIO3
//!
//!      EPWM3A is on GPIO4 \n
//!      EPWM3B is on GPIO5
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

// Prototype statements for functions found within this file.
void InitEPwm1Example(void);
void InitEPwm2Example(void);
void InitEPwm3Example(void);
interrupt void epwm1_isr(void);
interrupt void epwm2_isr(void);
interrupt void epwm3_isr(void);

// Global variables used in this example
uint32_t  EPwm1TimerIntCount;
uint32_t  EPwm2TimerIntCount;
uint32_t  EPwm3TimerIntCount;
uint16_t  EPwm1_DB_Direction;
uint16_t  EPwm2_DB_Direction;
uint16_t  EPwm3_DB_Direction;

// Maximum Dead Band values
#define EPWM1_MAX_DB   0x03FF
#define EPWM2_MAX_DB   0x03FF
#define EPWM3_MAX_DB   0x03FF

#define EPWM1_MIN_DB   0
#define EPWM2_MIN_DB   0
#define EPWM3_MIN_DB   0

// To keep track of which way the Dead Band is moving
#define DB_UP   1
#define DB_DOWN 0

CLK_Handle myClk;
FLASH_Handle myFlash;
GPIO_Handle myGpio;
PIE_Handle myPie;
PWM_Handle myPwm1, myPwm2, myPwm3;

void main(void)
{
    
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

    // Initalize GPIO
    GPIO_setPullUp(myGpio, GPIO_Number_0, GPIO_PullUp_Disable);
    GPIO_setPullUp(myGpio, GPIO_Number_1, GPIO_PullUp_Disable);
    GPIO_setMode(myGpio, GPIO_Number_0, GPIO_0_Mode_EPWM1A);
    GPIO_setMode(myGpio, GPIO_Number_1, GPIO_1_Mode_EPWM1B);
    
    GPIO_setPullUp(myGpio, GPIO_Number_2, GPIO_PullUp_Disable);
    GPIO_setPullUp(myGpio, GPIO_Number_3, GPIO_PullUp_Disable);
    GPIO_setMode(myGpio, GPIO_Number_2, GPIO_2_Mode_EPWM2A);
    GPIO_setMode(myGpio, GPIO_Number_3, GPIO_3_Mode_EPWM2B);
    
    GPIO_setPullUp(myGpio, GPIO_Number_4, GPIO_PullUp_Disable);
    GPIO_setPullUp(myGpio, GPIO_Number_5, GPIO_PullUp_Disable);
    GPIO_setMode(myGpio, GPIO_Number_4, GPIO_4_Mode_EPWM3A);
    GPIO_setMode(myGpio, GPIO_Number_5, GPIO_5_Mode_EPWM3B);

    // Setup a debug vector table and enable the PIE
    PIE_setDebugIntVectorTable(myPie);
    PIE_enable(myPie);
    
    // Register interrupt handlers in the PIE vector table
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_3, PIE_SubGroupNumber_1, (intVec_t)&epwm1_isr);
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_3, PIE_SubGroupNumber_2, (intVec_t)&epwm2_isr);
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_3, PIE_SubGroupNumber_3, (intVec_t)&epwm3_isr);

    CLK_disableTbClockSync(myClk);

    InitEPwm1Example();
    InitEPwm2Example();
    InitEPwm3Example();
    
    CLK_enableTbClockSync(myClk);

    // Initalize counters:
    EPwm1TimerIntCount = 0;
    EPwm2TimerIntCount = 0;
    EPwm3TimerIntCount = 0;

    // Enable CPU INT3 which is connected to EPWM1-3 INT
    CPU_enableInt(myCpu, CPU_IntNumber_3);

    // Enable EPWM INTn in the PIE: Group 3 interrupt 1-3
    PIE_enablePwmInt(myPie, PWM_Number_1);
    PIE_enablePwmInt(myPie, PWM_Number_2);
    PIE_enablePwmInt(myPie, PWM_Number_3);

    // Enable global Interrupts and higher priority real-time debug events
    CPU_enableGlobalInts(myCpu);
    CPU_enableDebugInt(myCpu);

    for(;;) {
        asm(" NOP");
    }

}

interrupt void epwm1_isr(void)
{
    if(EPwm1_DB_Direction == DB_UP) {
        if(PWM_getDeadBandFallingEdgeDelay(myPwm1) < EPWM1_MAX_DB) {
          PWM_incrementDeadBandFallingEdgeDelay(myPwm1);
          PWM_incrementDeadBandRisingEdgeDelay(myPwm1);
        }
        else {
          EPwm1_DB_Direction = DB_DOWN;
          PWM_decrementDeadBandFallingEdgeDelay(myPwm1);
          PWM_decrementDeadBandRisingEdgeDelay(myPwm1);
        }
    }
    else {
        if(PWM_getDeadBandFallingEdgeDelay(myPwm1) == EPWM1_MIN_DB) {
          EPwm1_DB_Direction = DB_UP;
          PWM_incrementDeadBandFallingEdgeDelay(myPwm1);
          PWM_incrementDeadBandRisingEdgeDelay(myPwm1);
        }
        else {
          PWM_decrementDeadBandFallingEdgeDelay(myPwm1);
          PWM_decrementDeadBandRisingEdgeDelay(myPwm1);
        }
    }
    EPwm1TimerIntCount++;

    // Clear INT flag for this timer
    PWM_clearIntFlag(myPwm1);

    // Acknowledge this interrupt to receive more interrupts from group 3
    PIE_clearInt(myPie, PIE_GroupNumber_3);

}

interrupt void epwm2_isr(void)
{

    if(EPwm2_DB_Direction == DB_UP) {
        if(PWM_getDeadBandFallingEdgeDelay(myPwm2) < EPWM2_MAX_DB) {
          PWM_incrementDeadBandFallingEdgeDelay(myPwm2);
          PWM_incrementDeadBandRisingEdgeDelay(myPwm2);
        }
        else {
          EPwm2_DB_Direction = DB_DOWN;
          PWM_decrementDeadBandFallingEdgeDelay(myPwm2);
          PWM_decrementDeadBandRisingEdgeDelay(myPwm2);
        }
    }
    else {
        if(PWM_getDeadBandFallingEdgeDelay(myPwm2) == EPWM2_MIN_DB) {
          EPwm2_DB_Direction = DB_UP;
          PWM_incrementDeadBandFallingEdgeDelay(myPwm2);
          PWM_incrementDeadBandRisingEdgeDelay(myPwm2);
        }
        else {
          PWM_decrementDeadBandFallingEdgeDelay(myPwm2);
          PWM_decrementDeadBandRisingEdgeDelay(myPwm2);
        }
    }

    EPwm2TimerIntCount++;

    // Clear INT flag for this timer
    PWM_clearIntFlag(myPwm2);

    // Acknowledge this interrupt to receive more interrupts from group 3
    PIE_clearInt(myPie, PIE_GroupNumber_3);

}

interrupt void epwm3_isr(void)
{
    if(EPwm3_DB_Direction == DB_UP) {
        if(PWM_getDeadBandFallingEdgeDelay(myPwm3) < EPWM3_MAX_DB) {
          PWM_incrementDeadBandFallingEdgeDelay(myPwm3);
          PWM_incrementDeadBandRisingEdgeDelay(myPwm3);
        }
        else {
          EPwm3_DB_Direction = DB_DOWN;
          PWM_decrementDeadBandFallingEdgeDelay(myPwm3);
          PWM_decrementDeadBandRisingEdgeDelay(myPwm3);
        }
    }
    else {
        if(PWM_getDeadBandFallingEdgeDelay(myPwm3) == EPWM3_MIN_DB) {
          EPwm3_DB_Direction = DB_UP;
          PWM_incrementDeadBandFallingEdgeDelay(myPwm3);
          PWM_incrementDeadBandRisingEdgeDelay(myPwm3);
        }
        else {
          PWM_decrementDeadBandFallingEdgeDelay(myPwm3);
          PWM_decrementDeadBandRisingEdgeDelay(myPwm3);
        }
    }


    EPwm3TimerIntCount++;

    // Clear INT flag for this timer
    PWM_clearIntFlag(myPwm3);

    // Acknowledge this interrupt to receive more interrupts from group 3
    PIE_clearInt(myPie, PIE_GroupNumber_3);

}



void InitEPwm1Example()
{
    
    CLK_enablePwmClock(myClk, PWM_Number_1);

    PWM_setPeriod(myPwm1, 6000);    // Set timer period
    PWM_setPhase(myPwm1, 0x0000);   // Phase is 0
    PWM_setCount(myPwm1, 0x0000);   // Clear counter

    // Setup TBCLK
    PWM_setCounterMode(myPwm1, PWM_CounterMode_UpDown); // Count up
    PWM_disableCounterLoad(myPwm1);                     // Disable phase loading
    PWM_setHighSpeedClkDiv(myPwm1, PWM_HspClkDiv_by_4); // Clock ratio to SYSCLKOUT
    PWM_setClkDiv(myPwm1, PWM_ClkDiv_by_4);

    PWM_setShadowMode_CmpA(myPwm1, PWM_ShadowMode_Shadow);  // Load registers every ZERO
    PWM_setShadowMode_CmpB(myPwm1, PWM_ShadowMode_Shadow);
    PWM_setLoadMode_CmpA(myPwm1, PWM_LoadMode_Zero);
    PWM_setLoadMode_CmpB(myPwm1, PWM_LoadMode_Zero);

    // Setup compare
    PWM_setCmpA(myPwm1, 3000);

    // Set actions
    PWM_setActionQual_CntUp_CmpA_PwmA(myPwm1, PWM_ActionQual_Set);
    PWM_setActionQual_CntDown_CmpA_PwmA(myPwm1, PWM_ActionQual_Clear);

    PWM_setActionQual_CntUp_CmpA_PwmB(myPwm1, PWM_ActionQual_Clear);
    PWM_setActionQual_CntDown_CmpA_PwmB(myPwm1, PWM_ActionQual_Set);

    // Active Low PWMs - Setup Deadband
    PWM_setDeadBandOutputMode(myPwm1, PWM_DeadBandOutputMode_EPWMxA_Rising_EPWMxB_Falling);
    PWM_setDeadBandPolarity(myPwm1, PWM_DeadBandPolarity_EPWMxA_Inverted_EPWMxB_Inverted);
    PWM_setDeadBandInputMode(myPwm1, PWM_DeadBandInputMode_EPWMxA_Rising_and_Falling);
    PWM_setDeadBandRisingEdgeDelay(myPwm1, EPWM1_MIN_DB);
    PWM_setDeadBandFallingEdgeDelay(myPwm1, EPWM1_MIN_DB);
    EPwm1_DB_Direction = DB_UP;

    // Interrupt where we will change the Deadband
    PWM_setIntMode(myPwm1, PWM_IntMode_CounterEqualZero);   // Select INT on Zero event
    PWM_enableInt(myPwm1);                                  // Enable INT
    PWM_setIntPeriod(myPwm1, PWM_IntPeriod_ThirdEvent);     // Generate INT on 3rd event


}


void InitEPwm2Example()
{

    CLK_enablePwmClock(myClk, PWM_Number_2);

    PWM_setPeriod(myPwm2, 6000);    // Set timer period
    PWM_setPhase(myPwm2, 0x0000);   // Phase is 0
    PWM_setCount(myPwm2, 0x0000);   // Clear counter

    // Setup TBCLK
    PWM_setCounterMode(myPwm2, PWM_CounterMode_UpDown); // Count up
    PWM_disableCounterLoad(myPwm2);                     // Disable phase loading
    PWM_setHighSpeedClkDiv(myPwm2, PWM_HspClkDiv_by_4); // Clock ratio to SYSCLKOUT
    PWM_setClkDiv(myPwm2, PWM_ClkDiv_by_4);             // Slow just to observe on the scope

    // Setup compare
    PWM_setCmpA(myPwm2, 3000);

    // Set actions
    PWM_setActionQual_CntUp_CmpA_PwmA(myPwm2, PWM_ActionQual_Set);
    PWM_setActionQual_CntDown_CmpA_PwmA(myPwm2, PWM_ActionQual_Clear);

    PWM_setActionQual_CntUp_CmpA_PwmB(myPwm2, PWM_ActionQual_Clear);
    PWM_setActionQual_CntDown_CmpA_PwmB(myPwm2, PWM_ActionQual_Set);

    // Active Low complementary PWMs - setup the deadband
    PWM_setDeadBandOutputMode(myPwm2, PWM_DeadBandOutputMode_EPWMxA_Rising_EPWMxB_Falling);
    PWM_setDeadBandPolarity(myPwm2, PWM_DeadBandPolarity_EPWMxA_Inverted_EPWMxB_Inverted);
    PWM_setDeadBandInputMode(myPwm2, PWM_DeadBandInputMode_EPWMxA_Rising_and_Falling);
    PWM_setDeadBandRisingEdgeDelay(myPwm2, EPWM2_MIN_DB);
    PWM_setDeadBandFallingEdgeDelay(myPwm2, EPWM2_MIN_DB);
    EPwm2_DB_Direction = DB_UP;

    // Interrupt where we will modify the deadband
    PWM_setIntMode(myPwm2, PWM_IntMode_CounterEqualZero);   // Select INT on Zero event
    PWM_enableInt(myPwm2);                                  // Enable INT
    PWM_setIntPeriod(myPwm2, PWM_IntPeriod_ThirdEvent);     // Generate INT on 3rd event

}

void InitEPwm3Example()
{
    
    CLK_enablePwmClock(myClk, PWM_Number_3);

    PWM_setPeriod(myPwm3, 6000);    // Set timer period
    PWM_setPhase(myPwm3, 0x0000);   // Phase is 0
    PWM_setCount(myPwm3, 0x0000);   // Clear counter


    // Setup TBCLK
    PWM_setCounterMode(myPwm3, PWM_CounterMode_UpDown); // Count up
    PWM_disableCounterLoad(myPwm3);                     // Disable phase loading
    PWM_setHighSpeedClkDiv(myPwm3, PWM_HspClkDiv_by_4); // Clock ratio to SYSCLKOUT
    PWM_setClkDiv(myPwm3, PWM_ClkDiv_by_4);             // Slow so we can observe on the scope

    // Setup compare
    PWM_setCmpA(myPwm3, 3000);

    // Set actions
    PWM_setActionQual_CntUp_CmpA_PwmA(myPwm3, PWM_ActionQual_Set);
    PWM_setActionQual_CntDown_CmpA_PwmA(myPwm3, PWM_ActionQual_Clear);

    PWM_setActionQual_CntUp_CmpA_PwmB(myPwm3, PWM_ActionQual_Clear);
    PWM_setActionQual_CntDown_CmpA_PwmB(myPwm3, PWM_ActionQual_Set);

    // Active high complementary PWMs - Setup the deadband
    PWM_setDeadBandOutputMode(myPwm3, PWM_DeadBandOutputMode_EPWMxA_Rising_EPWMxB_Falling);
    PWM_setDeadBandPolarity(myPwm3, PWM_DeadBandPolarity_EPWMxB_Inverted);
    PWM_setDeadBandInputMode(myPwm3, PWM_DeadBandInputMode_EPWMxA_Rising_and_Falling);
    PWM_setDeadBandRisingEdgeDelay(myPwm3, EPWM3_MIN_DB);
    PWM_setDeadBandFallingEdgeDelay(myPwm3, EPWM3_MIN_DB);
    EPwm3_DB_Direction = DB_UP;

    // Interrupt where we will change the deadband
    PWM_setIntMode(myPwm3, PWM_IntMode_CounterEqualZero);   // Select INT on Zero event
    PWM_enableInt(myPwm3);                                  // Enable INT
    PWM_setIntPeriod(myPwm3, PWM_IntPeriod_ThirdEvent);     // Generate INT on 3rd event

}

//===========================================================================
// No more.
//===========================================================================
