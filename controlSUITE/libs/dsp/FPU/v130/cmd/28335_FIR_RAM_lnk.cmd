/*
/* Define the memory block start/length for the F28335
   Notes:
         Doing so will result in corruption of program
         L0/L1/L2 and L3 memory blocks are mirrored - that is
MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to SARAM" bootloader mode      */
   BEGIN      : origin = 0x000000, length = 0x000002     /* Boot to M0 will go here                      */
PAGE 1 :
   /* BOOT_RSVD is used by the boot ROM for stack.               */
   BOOT_RSVD  : origin = 0x000002, length = 0x00004E     /* Part of M0, BOOT rom will use this for stack */
{
   .stack           : > RAMM1,     PAGE = 1
   firldb   align(0x800) > RAML0   PAGE = 0
   IQmath           : > RAML1,     PAGE = 0
   IQmathTables     : > IQTABLES,  PAGE = 0, TYPE = NOLOAD

   /* Uncomment the section below if calling the IQNexp() or IQexp()
   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used                    */
   /* Allocate ADC_cal function (pre-programmed by factory into TI reserved memory) */
//===========================================================================