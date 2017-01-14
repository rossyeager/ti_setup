//#############################################################################
//
//  File:   f2802x_examples_ccsv4/lpm_idlewake/Example_F2802xIdleWake.c
//
//  Title:  Device Idle Mode and Wakeup Program.
//
//  Group:          C2000
//  Target Device:  TMS320F2802x
//
//! \addtogroup example_list
//!  <h1>Device Idle Mode and Wakeup</h1>
//!
//!    This example puts the device into IDLE mode.
//!
//!    The example then wakes up the device from IDLE using XINT1
//!    which triggers on a falling edge from GPIO0.
//!    This pin must be pulled from high to low by an external agent for
//!    wakeup.
//!
//!    To observe the device wakeup from IDLE mode, monitor GPIO1 with
//!    an oscilloscope, which toggles in the XINT_1_ISR.
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
#include "f2802x_common/include/pwr.h"
#include "f2802x_common/include/wdog.h"

// Prototype statements for functions found within this file.
interrupt void XINT_1_ISR(void);      // ISR

CLK_Handle myClk;
FLASH_Handle myFlash;
GPIO_Handle myGpio;
PIE_Handle myPie;

void main(void)
{
    CPU_Handle myCpu;
    PLL_Handle myPll;
    PWR_Handle myPwr;
    WDOG_Handle myWDog;
    
    // Initialize all the handles needed for this application 
    myClk = CLK_init((void *)CLK_BASE_ADDR, sizeof(CLK_Obj)); 
    myCpu = CPU_init((void *)NULL, sizeof(CPU_Obj));
    myFlash = FLASH_init((void *)FLASH_BASE_ADDR, sizeof(FLASH_Obj));
    myGpio = GPIO_init((void *)GPIO_BASE_ADDR, sizeof(GPIO_Obj));
    myPie = PIE_init((void *)PIE_BASE_ADDR, sizeof(PIE_Obj));
    myPll = PLL_init((void *)PLL_BASE_ADDR, sizeof(PLL_Obj));
    myPwr = PWR_init((void *)PWR_BASE_ADDR, sizeof(PWR_Obj));
    myWDog = WDOG_init((void *)WDOG_BASE_ADDR, sizeof(WDOG_Obj));

    // Perform basic system initialization    
    WDOG_disable(myWDog);
    CLK_enableAdcClock(myClk);
    (*Device_cal)();
    
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
    // Enable Pull-ups
    GPIO_setPullUp(myGpio, GPIO_Number_0, GPIO_PullUp_Enable); 
    GPIO_setPullUp(myGpio, GPIO_Number_1, GPIO_PullUp_Enable);
    
    // Choose GPIO0 as the XINT1 pin.
    GPIO_setExtInt(myGpio, GPIO_Number_0, CPU_ExtIntNumber_1);
    
    // GPIO1 set in the ISR to indicate device woken up.
    GPIO_setDirection(myGpio, GPIO_Number_1, GPIO_Direction_Output);
    
    // Enable XINT1 pin
    PIE_enableExtInt(myPie, CPU_ExtIntNumber_1);
    
    // Interrupt triggers on falling edge
    PIE_setExtIntPolarity(myPie, CPU_ExtIntNumber_1, PIE_ExtIntPolarity_FallingEdge);

    // Setup a debug vector table and enable the PIE
    PIE_setDebugIntVectorTable(myPie);
    PIE_enable(myPie);
    
    // Register interrupt handlers in the PIE vector table
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_1, PIE_SubGroupNumber_4, (intVec_t)&XINT_1_ISR);

    // Enable CPU INT1 which is connected to WakeInt
    CPU_enableInt(myCpu, CPU_IntNumber_1);

    // Enable XINT1 in the PIE: Group 1 interrupt 4
    PIE_enableInt(myPie, PIE_GroupNumber_1, PIE_InterruptSource_XINT_1);

    PIE_clearInt(myPie, PIE_GroupNumber_1);

    // Enable global Interrupts
    CPU_enableGlobalInts(myCpu);


    // Only enter Standby mode when PLL is not in limp mode.
    if ( PLL_getClkStatus(myPll) != PLL_PLLSTS_MCLKSTS_BITS)
    {
        // LPM mode = Standby
        PWR_setLowPowerMode(myPwr, PWR_LowPowerMode_Idle);
    }
    
    IDLE;                   // Device waits in IDLE until XINT1 interrupts
    for(;;){}
}

interrupt void XINT_1_ISR(void)
{

    // TOGGLE GPIO1 in the ISR - monitored with oscilloscope
    GPIO_toggle(myGpio, GPIO_Number_1);
    
    PIE_clearInt(myPie, PIE_GroupNumber_1);
    
}
