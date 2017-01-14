;;*****************************************************************************
;;  \file source/vcu0/vcu0_cfft_twiddleFactors.asm
;; 
;;  \brief  Twiddle factors for VCU-0 Code
;;
;;  \date   Apr 7, 2011
;;
;;  Group:            C2000
;;  Target Family:    F2837x
;;
;; (C)Copyright 2012, Texas Instruments, Inc.
;;*****************************************************************************
;;$TI Release: C28x VCU Library Version v2.00.00.00 $
;;$Release Date: Dec 6, 2013 $
;;*****************************************************************************
;;
;############################################################################
;
;/*! \page CFFT16_TF (Set of Twiddle Factors)
;This file contains 512 pairs of twiddle factors arragned in the following 
; format:
;
; Each twiddle factor is a complex number and takes up 2 words. They are
; ordered as Imaginary : Real pairs in the Q15 format. They are arranged as
; follows:
; W(2,0)
; W(4,0)  W(4,2)
; W(8,0)  W(8,1)  W(8,2)  W(8,3)
; W(16,0) W(16,1) W(16,2) W(16,3) W(16,4) W(16,5) W(16,6) W(16,7)
; W(32,0) ... W(32,15)
; W(64,0) ... W(64,31)
; W(128,0)... W(128,63)
; W(256,0)... W(256,127)
; W(512,0)... W(512,255)
;*/
;############################################################################
       
        .global _CFFT16_TF
        .sect .econst  
                
_CFFT16_TF:
        .word   0, 32767,  0, 32767,  -32767, 0,  0, 32767
        .word   -23170, 23170,  -32767, 0,  -23170, -23170,  0, 32767
        .word   -12539, 30273,  -23170, 23170,  -30273, 12539,  -32767, 0
        .word   -30273, -12539,  -23170, -23170,  -12539, -30273,  0, 32767
        .word   -6393, 32137,  -12539, 30273,  -18204, 27245,  -23170, 23170
        .word   -27245, 18204,  -30273, 12539,  -32137, 6393,  -32767, 0
        .word   -32137, -6393,  -30273, -12539,  -27245, -18204,  -23170, -23170
        .word   -18204, -27245,  -12539, -30273,  -6393, -32137,  0, 32767
        .word   -3212, 32609,  -6393, 32137,  -9512, 31356,  -12539, 30273
        .word   -15446, 28898,  -18204, 27245,  -20787, 25329,  -23170, 23170
        .word   -25329, 20787,  -27245, 18204,  -28898, 15446,  -30273, 12539
        .word   -31356, 9512,  -32137, 6393,  -32609, 3212,  -32767, 0
        .word   -32609, -3212,  -32137, -6393,  -31356, -9512,  -30273, -12539
        .word   -28898, -15446,  -27245, -18204,  -25329, -20787,  -23170, -23170
        .word   -20787, -25329,  -18204, -27245,  -15446, -28898,  -12539, -30273
        .word   -9512, -31356,  -6393, -32137,  -3212, -32609,  0, 32767
        .word   -1608, 32728,  -3212, 32609,  -4808, 32412,  -6393, 32137
        .word   -7962, 31785,  -9512, 31356,  -11039, 30852,  -12539, 30273
        .word   -14010, 29621,  -15446, 28898,  -16846, 28105,  -18204, 27245
        .word   -19519, 26319,  -20787, 25329,  -22005, 24279,  -23170, 23170
        .word   -24279, 22005,  -25329, 20787,  -26319, 19519,  -27245, 18204
        .word   -28105, 16846,  -28898, 15446,  -29621, 14010,  -30273, 12539
        .word   -30852, 11039,  -31356, 9512,  -31785, 7962,  -32137, 6393
        .word   -32412, 4808,  -32609, 3212,  -32728, 1608,  -32767, 0
        .word   -32728, -1608,  -32609, -3212,  -32412, -4808,  -32137, -6393
        .word   -31785, -7962,  -31356, -9512,  -30852, -11039,  -30273, -12539
        .word   -29621, -14010,  -28898, -15446,  -28105, -16846,  -27245, -18204
        .word   -26319, -19519,  -25329, -20787,  -24279, -22005,  -23170, -23170
        .word   -22005, -24279,  -20787, -25329,  -19519, -26319,  -18204, -27245
        .word   -16846, -28105,  -15446, -28898,  -14010, -29621,  -12539, -30273
        .word   -11039, -30852,  -9512, -31356,  -7962, -31785,  -6393, -32137
        .word   -4808, -32412,  -3212, -32609,  -1608, -32728,  0, 32767
        .word   -804, 32757,  -1608, 32728,  -2410, 32678,  -3212, 32609
        .word   -4011, 32521,  -4808, 32412,  -5602, 32285,  -6393, 32137
        .word   -7179, 31971,  -7962, 31785,  -8739, 31580,  -9512, 31356
        .word   -10278, 31113,  -11039, 30852,  -11793, 30571,  -12539, 30273
        .word   -13279, 29956,  -14010, 29621,  -14732, 29268,  -15446, 28898
        .word   -16151, 28510,  -16846, 28105,  -17530, 27683,  -18204, 27245
        .word   -18868, 26790,  -19519, 26319,  -20159, 25832,  -20787, 25329
        .word   -21403, 24811,  -22005, 24279,  -22594, 23731,  -23170, 23170
        .word   -23731, 22594,  -24279, 22005,  -24811, 21403,  -25329, 20787
        .word   -25832, 20159,  -26319, 19519,  -26790, 18868,  -27245, 18204
        .word   -27683, 17530,  -28105, 16846,  -28510, 16151,  -28898, 15446
        .word   -29268, 14732,  -29621, 14010,  -29956, 13279,  -30273, 12539
        .word   -30571, 11793,  -30852, 11039,  -31113, 10278,  -31356, 9512
        .word   -31580, 8739,  -31785, 7962,  -31971, 7179,  -32137, 6393
        .word   -32285, 5602,  -32412, 4808,  -32521, 4011,  -32609, 3212
        .word   -32678, 2410,  -32728, 1608,  -32757, 804,  -32767, 0
        .word   -32757, -804,  -32728, -1608,  -32678, -2410,  -32609, -3212
        .word   -32521, -4011,  -32412, -4808,  -32285, -5602,  -32137, -6393
        .word   -31971, -7179,  -31785, -7962,  -31580, -8739,  -31356, -9512
        .word   -31113, -10278,  -30852, -11039,  -30571, -11793,  -30273, -12539
        .word   -29956, -13279,  -29621, -14010,  -29268, -14732,  -28898, -15446
        .word   -28510, -16151,  -28105, -16846,  -27683, -17530,  -27245, -18204
        .word   -26790, -18868,  -26319, -19519,  -25832, -20159,  -25329, -20787
        .word   -24811, -21403,  -24279, -22005,  -23731, -22594,  -23170, -23170
        .word   -22594, -23731,  -22005, -24279,  -21403, -24811,  -20787, -25329
        .word   -20159, -25832,  -19519, -26319,  -18868, -26790,  -18204, -27245
        .word   -17530, -27683,  -16846, -28105,  -16151, -28510,  -15446, -28898
        .word   -14732, -29268,  -14010, -29621,  -13279, -29956,  -12539, -30273
        .word   -11793, -30571,  -11039, -30852,  -10278, -31113,  -9512, -31356
        .word   -8739, -31580,  -7962, -31785,  -7179, -31971,  -6393, -32137
        .word   -5602, -32285,  -4808, -32412,  -4011, -32521,  -3212, -32609
        .word   -2410, -32678,  -1608, -32728,  -804, -32757, 0, 32767 
        .word   -402, 32765,  -804, 32757,  -1206, 32745,  -1608, 32728
        .word   -2009, 32705,  -2410, 32678,  -2811, 32646,  -3212, 32609
        .word   -3612, 32567,  -4011, 32521,  -4410, 32469,  -4808, 32412
        .word   -5205, 32351,  -5602, 32285,  -5998, 32213,  -6393, 32137
        .word   -6786, 32057,  -7179, 31971,  -7571, 31880,  -7962, 31785
        .word   -8351, 31685,  -8739, 31580,  -9126, 31470,  -9512, 31356
        .word   -9896, 31237,  -10278, 31113,  -10659, 30985,  -11039, 30852
        .word   -11417, 30714,  -11793, 30571,  -12167, 30424,  -12539, 30273
        .word   -12910, 30117,  -13279, 29956,  -13645, 29791,  -14010, 29621
        .word   -14372, 29447,  -14732, 29268,  -15090, 29085,  -15446, 28898
        .word   -15800, 28706,  -16151, 28510,  -16499, 28310,  -16846, 28105
        .word   -17189, 27896,  -17530, 27683,  -17869, 27466,  -18204, 27245
        .word   -18537, 27019,  -18868, 26790,  -19195, 26556,  -19519, 26319
        .word   -19841, 26077,  -20159, 25832,  -20475, 25582,  -20787, 25329
        .word   -21096, 25072,  -21403, 24811,  -21705, 24547,  -22005, 24279
        .word   -22301, 24007,  -22594, 23731,  -22884, 23452,  -23170, 23170
        .word   -23452, 22884,  -23731, 22594,  -24007, 22301,  -24279, 22005
        .word   -24547, 21705,  -24811, 21403,  -25072, 21096,  -25329, 20787
        .word   -25582, 20475,  -25832, 20159,  -26077, 19841,  -26319, 19519
        .word   -26556, 19195,  -26790, 18868,  -27019, 18537,  -27245, 18204
        .word   -27466, 17869,  -27683, 17530,  -27896, 17189,  -28105, 16846
        .word   -28310, 16499,  -28510, 16151,  -28706, 15800,  -28898, 15446
        .word   -29085, 15090,  -29268, 14732,  -29447, 14372,  -29621, 14010
        .word   -29791, 13645,  -29956, 13279,  -30117, 12910,  -30273, 12539
        .word   -30424, 12167,  -30571, 11793,  -30714, 11417,  -30852, 11039
        .word   -30985, 10659,  -31113, 10278,  -31237, 9896,  -31356, 9512
        .word   -31470, 9126,  -31580, 8739,  -31685, 8351,  -31785, 7962
        .word   -31880, 7571,  -31971, 7179,  -32057, 6786,  -32137, 6393
        .word   -32213, 5998,  -32285, 5602,  -32351, 5205,  -32412, 4808
        .word   -32469, 4410,  -32521, 4011,  -32567, 3612,  -32609, 3212
        .word   -32646, 2811,  -32678, 2410,  -32705, 2009,  -32728, 1608
        .word   -32745, 1206,  -32757, 804,  -32765, 402,  -32767, 0
        .word   -32765, -402,  -32757, -804,  -32745, -1206,  -32728, -1608
        .word   -32705, -2009,  -32678, -2410,  -32646, -2811,  -32609, -3212
        .word   -32567, -3612,  -32521, -4011,  -32469, -4410,  -32412, -4808
        .word   -32351, -5205,  -32285, -5602,  -32213, -5998,  -32137, -6393
        .word   -32057, -6786,  -31971, -7179,  -31880, -7571,  -31785, -7962
        .word   -31685, -8351,  -31580, -8739,  -31470, -9126,  -31356, -9512
        .word   -31237, -9896,  -31113, -10278,  -30985, -10659,  -30852, -11039
        .word   -30714, -11417,  -30571, -11793,  -30424, -12167,  -30273, -12539
        .word   -30117, -12910,  -29956, -13279,  -29791, -13645,  -29621, -14010
        .word   -29447, -14372,  -29268, -14732,  -29085, -15090,  -28898, -15446
        .word   -28706, -15800,  -28510, -16151,  -28310, -16499,  -28105, -16846
        .word   -27896, -17189,  -27683, -17530,  -27466, -17869,  -27245, -18204
        .word   -27019, -18537,  -26790, -18868,  -26556, -19195,  -26319, -19519
        .word   -26077, -19841,  -25832, -20159,  -25582, -20475,  -25329, -20787
        .word   -25072, -21096,  -24811, -21403,  -24547, -21705,  -24279, -22005
        .word   -24007, -22301,  -23731, -22594,  -23452, -22884,  -23170, -23170
        .word   -22884, -23452,  -22594, -23731,  -22301, -24007,  -22005, -24279
        .word   -21705, -24547,  -21403, -24811,  -21096, -25072,  -20787, -25329
        .word   -20475, -25582,  -20159, -25832,  -19841, -26077,  -19519, -26319
        .word   -19195, -26556,  -18868, -26790,  -18537, -27019,  -18204, -27245
        .word   -17869, -27466,  -17530, -27683,  -17189, -27896,  -16846, -28105
        .word   -16499, -28310,  -16151, -28510,  -15800, -28706,  -15446, -28898
        .word   -15090, -29085,  -14732, -29268,  -14372, -29447,  -14010, -29621
        .word   -13645, -29791,  -13279, -29956,  -12910, -30117,  -12539, -30273
        .word   -12167, -30424,  -11793, -30571,  -11417, -30714,  -11039, -30852
        .word   -10659, -30985,  -10278, -31113,  -9896, -31237,  -9512, -31356
        .word   -9126, -31470,  -8739, -31580,  -8351, -31685,  -7962, -31785
        .word   -7571, -31880,  -7179, -31971,  -6786, -32057,  -6393, -32137
        .word   -5998, -32213,  -5602, -32285,  -5205, -32351,  -4808, -32412
        .word   -4410, -32469,  -4011, -32521,  -3612, -32567,  -3212, -32609
        .word   -2811, -32646,  -2410, -32678,  -2009, -32705,  -1608, -32728
        .word   -1206, -32745,  -804, -32757,  -402, -32765, 0, 0

;; End of file
