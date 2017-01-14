; =============================================================================
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2011-2012 Texas Instruments, Incorporated.
;                          All Rights Reserved.
; =============================================================================
;
; FILE:        abs_SP_CV.asm
;
; AUTHOR:      David M. Alter, Texas Instruments Inc.
;
; HISTORY:
;   07/20/11 - original (D. Alter)
;
; DESCRIPTION: C-Callable absolute value of a complex vector
;              y[i] = sqrt(x_re[i]^2 + x_im[i]^2)
;
; FUNCTION: 
;   void abs_SP_CV(float32 *y, const complex_float *x, const Uint16 N)
; USAGE:      abs_SP_CV(x, y, N);
; PARAMETERS: float32 *y = output array
;             complex_float *x = input array
;             Uint16 N = length of x and y arrays
; RETURNS:    none
; BENCHMARK:  28*N+9 cycles (including the call and return)
; NOTES:
;   1) The type 'complex_float' is defined as
;
;      typedef struct {
;         float32 dat[2];
;      } complex_float;
;
;    Element dat[0] is the real part, dat[1] is the imag part.
;
; =============================================================================
; ###########################################################################
; $TI Release: C28x Floating Point Unit Library V1.31 $
; $Release Date: Sep 10, 2012 $
; ###########################################################################

		.global _abs_SP_CV
		.text

_abs_SP_CV:
		ADDB AL, #-1							;Subtract 1 from N since RPTB is 'n-1' times

;---Main loop
		RPTB end_loop, @AL

;Compute the magnitude squared
		MOV32 R0H, *XAR5++						;R0H = x_re
		MPYF32 R1H, R0H, R0H					;R1H = x_re * x_re
		|| MOV32 R2H, *XAR5++					;R2H = x_im
		MPYF32 R3H, R2H, R2H					;R3H = x_im * x_im (also delay slot for MPYF32||MOV32)
		NOP										;delay slot
		ADDF32 R0H, R1H, R3H					;R0H = (x_re * x_re) + (x_im * x_im)
		NOP										;delay slot

;Compute sqrt.  Use the code from the DSP28 Fast FPU Library!
        EISQRTF32   R1H, R0H            ; R1H = Ye = Estimate(1/sqrt(X))
        MPYF32      R2H, R0H, #0.5      ; R2H = X*0.5
        MPYF32      R3H, R1H, R1H       ; R3H = Ye*Ye
        NOP
        MPYF32      R3H, R3H, R2H       ; R3H = Ye*Ye*X*0.5
        NOP
        SUBF32      R3H, #1.5, R3H      ; R3H = 1.5 - Ye*Ye*X*0.5
        NOP
        MPYF32      R1H, R1H, R3H       ; R2H = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
        NOP
        MPYF32      R3H, R1H, R2H       ; R3H = Ye*X*0.5
        NOP
        MPYF32      R3H, R1H, R3H       ; R3H = Ye*Ye*X*0.5
        NOP
        SUBF32      R3H, #1.5, R3H      ; R3H = 1.5 - Ye*Ye*X*0.5
        CMPF32      R0H, #0.0           ; Check if X == 0
        MPYF32      R1H, R1H, R3H       ; R2H = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
        NOP
        MOV32       R1H, R0H, EQ        ; If X is zero, change the Ye estimate to 0
        MPYF32      R0H, R0H, R1H       ; R0H = Y = X*Ye = sqrt(X)
        NOP
   		MOV32 *XAR4++, R0H				;store the result to memory

end_loop:

;Finish up
		LRETR									;return

;end of function abs_SP_CV()
;*********************************************************************

       .end
;--------------------------------------------------------------------------
;            Copyright (c) 2011-2012 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================