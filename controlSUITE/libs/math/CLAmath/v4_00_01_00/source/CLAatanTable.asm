;******************************************************************************
; 
; FILE: CLAatanTable.asm
; 
; DESCRIPTION: atan Tables
; 
;******************************************************************************
;  $TI Release: CLA Math Library for CLA C Compiler V4.00.01.00 $
;  $Release Date: Apr 23, 2014 $
;******************************************************************************
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2014 Texas Instruments, Incorporated.
;                          All Rights Reserved.
;******************************************************************************
	
	.def	_CLAatan2HalfPITable
	.def	_CLAINV2PI
	.def	_CLAatan2Table
	.def	_CLAatan2TableEnd

   .sect    "CLA1mathTables"
   
_CLAatan2HalfPITable:
	.float	 2.0	; 2.0
	.float	 1.570796327	; PI/2
_CLAINV2PI:
	.float   0.159154943    ;1 / {2*PI}

_CLAatan2Table:
	.float	  0.000000000000	;   0 x0 =   0.000000000000 -> a0 =   0.000000000000
	.float	  1.000040679675	;   0 x1 =   0.007812500000 -> a1 =   1.000040679675
	.float	 -0.007811069750	;   0 x2 =   0.015625000000 -> a2 =  -0.007811069750

	.float	 -0.000003807022	;   1 x0 =   0.015625000000 -> a0 =  -0.000003807022
	.float	  1.000528067772	;   1 x1 =   0.023437500000 -> a1 =   1.000528067772
	.float	 -0.023410345493	;   1 x2 =   0.031250000000 -> a2 =  -0.023410345493

	.float	 -0.000018968310	;   2 x0 =   0.031250000000 -> a0 =  -0.000018968310
	.float	  1.001498568106	;   2 x1 =   0.039062500000 -> a1 =   1.001498568106
	.float	 -0.038941197075	;   2 x2 =   0.046875000000 -> a2 =  -0.038941197075

	.float	 -0.000052831927	;   3 x0 =   0.046875000000 -> a0 =  -0.000052831927
	.float	  1.002943680965	;   3 x1 =   0.054687500000 -> a1 =   1.002943680965
	.float	 -0.054358563160	;   3 x2 =   0.062500000000 -> a2 =  -0.054358563160

	.float	 -0.000112417996	;   4 x0 =   0.062500000000 -> a0 =  -0.000112417996
	.float	  1.004850785788	;   4 x1 =   0.070312500000 -> a1 =   1.004850785788
	.float	 -0.069618206649	;   4 x2 =   0.078125000000 -> a2 =  -0.069618206649

	.float	 -0.000204295885	;   5 x0 =   0.078125000000 -> a0 =  -0.000204295885
	.float	  1.007203293243	;   5 x1 =   0.085937500000 -> a1 =   1.007203293243
	.float	 -0.084677028723	;   5 x2 =   0.093750000000 -> a2 =  -0.084677028723
	.float	 -0.000334469493	;   6 x0 =   0.093750000000 -> a0 =  -0.000334469493
	.float	  1.009980843501	;   6 x1 =   0.101562500000 -> a1 =   1.009980843501
	.float	 -0.099493367628	;   6 x2 =   0.109375000000 -> a2 =  -0.099493367628
	.float	 -0.000508272606	;   7 x0 =   0.109375000000 -> a0 =  -0.000508272606
	.float	  1.013159547023	;   7 x1 =   0.117187500000 -> a1 =   1.013159547023
	.float	 -0.114027278430	;   7 x2 =   0.125000000000 -> a2 =  -0.114027278430
	.float	 -0.000730276035	;   8 x0 =   0.125000000000 -> a0 =  -0.000730276035
	.float	  1.016712263449	;   8 x1 =   0.132812500000 -> a1 =   1.016712263449
	.float	 -0.128240790343	;   8 x2 =   0.140625000000 -> a2 =  -0.128240790343
	.float	 -0.001004207980	;   9 x0 =   0.140625000000 -> a0 =  -0.001004207980
	.float	  1.020608913557	;   9 x1 =   0.148437500000 -> a1 =   1.020608913557
	.float	 -0.142098138715	;   9 x2 =   0.156250000000 -> a2 =  -0.142098138715
	.float	 -0.001332888717	;  10 x0 =   0.156250000000 -> a0 =  -0.001332888717
	.float	  1.024816818801	;  10 x1 =   0.164062500000 -> a1 =   1.024816818801
	.float	 -0.155565969259	;  10 x2 =   0.171875000000 -> a2 =  -0.155565969259
	.float	 -0.001718180431	;  11 x0 =   0.171875000000 -> a0 =  -0.001718180431
	.float	  1.029301062569	;  11 x1 =   0.179687500000 -> a1 =   1.029301062569
	.float	 -0.168613512667	;  11 x2 =   0.187500000000 -> a2 =  -0.168613512667
	.float	 -0.002160952612	;  12 x0 =   0.187500000000 -> a0 =  -0.002160952612
	.float	  1.034024867135	;  12 x1 =   0.195312500000 -> a1 =   1.034024867135
	.float	 -0.181212728329	;  12 x2 =   0.203125000000 -> a2 =  -0.181212728329
	.float	 -0.002661063159	;  13 x0 =   0.203125000000 -> a0 =  -0.002661063159
	.float	  1.038949980222	;  13 x1 =   0.210937500000 -> a1 =   1.038949980222
	.float	 -0.193338416410	;  13 x2 =   0.218750000000 -> a2 =  -0.193338416410
	.float	 -0.003217354977	;  14 x0 =   0.218750000000 -> a0 =  -0.003217354977
	.float	  1.044037065160	;  14 x1 =   0.226562500000 -> a1 =   1.044037065160
	.float	 -0.204968298146	;  14 x2 =   0.234375000000 -> a2 =  -0.204968298146
	.float	 -0.003827667546	;  15 x0 =   0.234375000000 -> a0 =  -0.003827667546
	.float	  1.049246088868	;  15 x1 =   0.242187500000 -> a1 =   1.049246088868
	.float	 -0.216083064706	;  15 x2 =   0.250000000000 -> a2 =  -0.216083064706
	.float	 -0.004488862702	;  16 x0 =   0.250000000000 -> a0 =  -0.004488862702
	.float	  1.054536702192	;  16 x1 =   0.257812500000 -> a1 =   1.054536702192
	.float	 -0.226666395507	;  16 x2 =   0.265625000000 -> a2 =  -0.226666395507
	.float	 -0.005196863579	;  17 x0 =   0.265625000000 -> a0 =  -0.005196863579
	.float	  1.059868607573	;  17 x1 =   0.273437500000 -> a1 =   1.059868607573
	.float	 -0.236704947279	;  17 x2 =   0.281250000000 -> a2 =  -0.236704947279
	.float	 -0.005946705500	;  18 x0 =   0.281250000000 -> a0 =  -0.005946705500
	.float	  1.065201909527	;  18 x1 =   0.289062500000 -> a1 =   1.065201909527
	.float	 -0.246188315613	;  18 x2 =   0.296875000000 -> a2 =  -0.246188315613
	.float	 -0.006732597422	;  19 x0 =   0.296875000000 -> a0 =  -0.006732597422
	.float	  1.070497443994	;  19 x1 =   0.304687500000 -> a1 =   1.070497443994
	.float	 -0.255108971022	;  19 x2 =   0.312500000000 -> a2 =  -0.255108971022
	.float	 -0.007547992413	;  20 x0 =   0.312500000000 -> a0 =  -0.007547992413
	.float	  1.075717083222	;  20 x1 =   0.320312500000 -> a1 =   1.075717083222
	.float	 -0.263462171840	;  20 x2 =   0.328125000000 -> a2 =  -0.263462171840
	.float	 -0.008385665599	;  21 x0 =   0.328125000000 -> a0 =  -0.008385665599
	.float	  1.080824013499	;  21 x1 =   0.335937500000 -> a1 =   1.080824013499
	.float	 -0.271245856476	;  21 x2 =   0.343750000000 -> a2 =  -0.271245856476
	.float	 -0.009237797924	;  22 x0 =   0.343750000000 -> a0 =  -0.009237797924
	.float	  1.085782983693	;  22 x1 =   0.351562500000 -> a1 =   1.085782983693
	.float	 -0.278460517693	;  22 x2 =   0.359375000000 -> a2 =  -0.278460517693
	.float	 -0.010096064139	;  23 x0 =   0.359375000000 -> a0 =  -0.010096064139
	.float	  1.090560523211	;  23 x1 =   0.367187500000 -> a1 =   1.090560523211
	.float	 -0.285109061650	;  23 x2 =   0.375000000000 -> a2 =  -0.285109061650
	.float	 -0.010951723407	;  24 x0 =   0.375000000000 -> a0 =  -0.010951723407
	.float	  1.095125128557	;  24 x1 =   0.382812500000 -> a1 =   1.095125128557
	.float	 -0.291196654447	;  24 x2 =   0.390625000000 -> a2 =  -0.291196654447
	.float	 -0.011795711029	;  25 x0 =   0.390625000000 -> a0 =  -0.011795711029
	.float	  1.099447418304	;  25 x1 =   0.398437500000 -> a1 =   1.099447418304
	.float	 -0.296730558920	;  25 x2 =   0.406250000000 -> a2 =  -0.296730558920
	.float	 -0.012618729873	;  26 x0 =   0.406250000000 -> a0 =  -0.012618729873
	.float	  1.103500256784	;  26 x1 =   0.414062500000 -> a1 =   1.103500256784
	.float	 -0.301719964310	;  26 x2 =   0.421875000000 -> a2 =  -0.301719964310
	.float	 -0.013411340199	;  27 x0 =   0.421875000000 -> a0 =  -0.013411340199
	.float	  1.107258847274	;  27 x1 =   0.429687500000 -> a1 =   1.107258847274
	.float	 -0.306175811325	;  27 x2 =   0.437500000000 -> a2 =  -0.306175811325
	.float	 -0.014164046711	;  28 x0 =   0.437500000000 -> a0 =  -0.014164046711
	.float	  1.110700795887	;  28 x1 =   0.445312500000 -> a1 =   1.110700795887
	.float	 -0.310110614947	;  28 x2 =   0.453125000000 -> a2 =  -0.310110614947
	.float	 -0.014867381831	;  29 x0 =   0.453125000000 -> a0 =  -0.014867381831
	.float	  1.113806147717	;  29 x1 =   0.460937500000 -> a1 =   1.113806147717
	.float	 -0.313538287176	;  29 x2 =   0.468750000000 -> a2 =  -0.313538287176
	.float	 -0.015511984298	;  30 x0 =   0.468750000000 -> a0 =  -0.015511984298
	.float	  1.116557397059	;  30 x1 =   0.476562500000 -> a1 =   1.116557397059
	.float	 -0.316473961655	;  30 x2 =   0.484375000000 -> a2 =  -0.316473961655
	.float	 -0.016088672395	;  31 x0 =   0.484375000000 -> a0 =  -0.016088672395
	.float	  1.118939473766	;  31 x1 =   0.492187500000 -> a1 =   1.118939473766
	.float	 -0.318933821948	;  31 x2 =   0.500000000000 -> a2 =  -0.318933821948
	.float	 -0.016588511229	;  32 x0 =   0.500000000000 -> a0 =  -0.016588511229
	.float	  1.120939707956	;  32 x1 =   0.507812500000 -> a1 =   1.120939707956
	.float	 -0.320934934991	;  32 x2 =   0.515625000000 -> a2 =  -0.320934934991
	.float	 -0.017002873645	;  33 x0 =   0.515625000000 -> a0 =  -0.017002873645
	.float	  1.122547775367	;  33 x1 =   0.523437500000 -> a1 =   1.122547775367
	.float	 -0.322495091022	;  33 x2 =   0.531250000000 -> a2 =  -0.322495091022
	.float	 -0.017323494499	;  34 x0 =   0.531250000000 -> a0 =  -0.017323494499
	.float	  1.123755625749	;  34 x1 =   0.539062500000 -> a1 =   1.123755625749
	.float	 -0.323632651068	;  34 x2 =   0.546875000000 -> a2 =  -0.323632651068
	.float	 -0.017542518140	;  35 x0 =   0.546875000000 -> a0 =  -0.017542518140
	.float	  1.124557396633	;  35 x1 =   0.554687500000 -> a1 =   1.124557396633
	.float	 -0.324366402860	;  35 x2 =   0.562500000000 -> a2 =  -0.324366402860
	.float	 -0.017652539065	;  36 x0 =   0.562500000000 -> a0 =  -0.017652539065
	.float	  1.124949314810	;  36 x1 =   0.570312500000 -> a1 =   1.124949314810
	.float	 -0.324715425833	;  36 x2 =   0.578125000000 -> a2 =  -0.324715425833
	.float	 -0.017646635823	;  37 x0 =   0.578125000000 -> a0 =  -0.017646635823
	.float	  1.124929587773	;  37 x1 =   0.585937500000 -> a1 =   1.124929587773
	.float	 -0.324698965683	;  37 x2 =   0.593750000000 -> a2 =  -0.324698965683
	.float	 -0.017518398344	;  38 x0 =   0.593750000000 -> a0 =  -0.017518398344
	.float	  1.124498287266	;  38 x1 =   0.601562500000 -> a1 =   1.124498287266
	.float	 -0.324336318787	;  38 x2 =   0.609375000000 -> a2 =  -0.324336318787
	.float	 -0.017261948920	;  39 x0 =   0.609375000000 -> a0 =  -0.017261948920
	.float	  1.123657226955	;  39 x1 =   0.617187500000 -> a1 =   1.123657226955
	.float	 -0.323646726613	;  39 x2 =   0.625000000000 -> a2 =  -0.323646726613
	.float	 -0.016871957164	;  40 x0 =   0.625000000000 -> a0 =  -0.016871957164
	.float	  1.122409836098	;  40 x1 =   0.632812500000 -> a1 =   1.122409836098
	.float	 -0.322649280139	;  40 x2 =   0.640625000000 -> a2 =  -0.322649280139
	.float	 -0.016343649294	;  41 x0 =   0.640625000000 -> a0 =  -0.016343649294
	.float	  1.120761030918	;  41 x1 =   0.648437500000 -> a1 =   1.120761030918
	.float	 -0.321362834119	;  41 x2 =   0.656250000000 -> a2 =  -0.321362834119
	.float	 -0.015672812166	;  42 x0 =   0.656250000000 -> a0 =  -0.015672812166
	.float	  1.118717085258	;  42 x1 =   0.664062500000 -> a1 =   1.118717085258
	.float	 -0.319805931024	;  42 x2 =   0.671875000000 -> a2 =  -0.319805931024
	.float	 -0.014855792451	;  43 x0 =   0.671875000000 -> a0 =  -0.014855792451
	.float	  1.116285501852	;  43 x1 =   0.679687500000 -> a1 =   1.116285501852
	.float	 -0.317996734279	;  43 x2 =   0.687500000000 -> a2 =  -0.317996734279
	.float	 -0.013889491441	;  44 x0 =   0.687500000000 -> a0 =  -0.013889491441
	.float	  1.113474885484	;  44 x1 =   0.695312500000 -> a1 =   1.113474885484
	.float	 -0.315952970460	;  44 x2 =   0.703125000000 -> a2 =  -0.315952970460
	.float	 -0.012771355912	;  45 x0 =   0.703125000000 -> a0 =  -0.012771355912
	.float	  1.110294819035	;  45 x1 =   0.710937500000 -> a1 =   1.110294819035
	.float	 -0.313691879968	;  45 x2 =   0.718750000000 -> a2 =  -0.313691879968
	.float	 -0.011499365513	;  46 x0 =   0.718750000000 -> a0 =  -0.011499365513
	.float	  1.106755743329	;  46 x1 =   0.726562500000 -> a1 =   1.106755743329
	.float	 -0.311230175714	;  46 x2 =   0.734375000000 -> a2 =  -0.311230175714
	.float	 -0.010072017131	;  47 x0 =   0.734375000000 -> a0 =  -0.010072017131
	.float	  1.102868841531	;  47 x1 =   0.742187500000 -> a1 =   1.102868841531
	.float	 -0.308584009287	;  47 x2 =   0.750000000000 -> a2 =  -0.308584009287
	.float	 -0.008488306656	;  48 x0 =   0.750000000000 -> a0 =  -0.008488306656
	.float	  1.098645928648	;  48 x1 =   0.757812500000 -> a1 =   1.098645928648
	.float	 -0.305768944066	;  48 x2 =   0.765625000000 -> a2 =  -0.305768944066
	.float	 -0.006747708579	;  49 x0 =   0.765625000000 -> a0 =  -0.006747708579
	.float	  1.094099346648	;  49 x1 =   0.773437500000 -> a1 =   1.094099346648
	.float	 -0.302799934724	;  49 x2 =   0.781250000000 -> a2 =  -0.302799934724
	.float	 -0.004850153815	;  50 x0 =   0.781250000000 -> a0 =  -0.004850153815
	.float	  1.089241865523	;  50 x1 =   0.789062500000 -> a1 =   1.089241865523
	.float	 -0.299691312610	;  50 x2 =   0.796875000000 -> a2 =  -0.299691312610
	.float	 -0.002796006119	;  51 x0 =   0.796875000000 -> a0 =  -0.002796006119
	.float	  1.084086590517	;  51 x1 =   0.804687500000 -> a1 =   1.084086590517
	.float	 -0.296456776409	;  51 x2 =   0.812500000000 -> a2 =  -0.296456776409
	.float	 -0.000586037441	;  52 x0 =   0.812500000000 -> a0 =  -0.000586037441
	.float	  1.078646875666	;  52 x1 =   0.820312500000 -> a1 =   1.078646875666
	.float	 -0.293109387609	;  52 x2 =   0.828125000000 -> a2 =  -0.293109387609
	.float	  0.001778597452	;  53 x0 =   0.828125000000 -> a0 =   0.001778597452
	.float	  1.072936243727	;  53 x1 =   0.835937500000 -> a1 =   1.072936243727
	.float	 -0.289661570229	;  53 x2 =   0.843750000000 -> a2 =  -0.289661570229
	.float	  0.004296386804	;  54 x0 =   0.843750000000 -> a0 =   0.004296386804
	.float	  1.066968312440	;  54 x1 =   0.851562500000 -> a1 =   1.066968312440
	.float	 -0.286125114351	;  54 x2 =   0.859375000000 -> a2 =  -0.286125114351
	.float	  0.006965487894	;  55 x0 =   0.859375000000 -> a0 =   0.006965487894
	.float	  1.060756727064	;  55 x1 =   0.867187500000 -> a1 =   1.060756727064
	.float	 -0.282511182960	;  55 x2 =   0.875000000000 -> a2 =  -0.282511182960
	.float	  0.009783753017	;  56 x0 =   0.875000000000 -> a0 =   0.009783753017
	.float	  1.054315099009	;  56 x1 =   0.882812500000 -> a1 =   1.054315099009
	.float	 -0.278830321668	;  56 x2 =   0.890625000000 -> a2 =  -0.278830321668
	.float	  0.012748755207	;  57 x0 =   0.890625000000 -> a0 =   0.012748755207
	.float	  1.047656950440	;  57 x1 =   0.898437500000 -> a1 =   1.047656950440
	.float	 -0.275092470943	;  57 x2 =   0.906250000000 -> a2 =  -0.275092470943
	.float	  0.015857813546	;  58 x0 =   0.906250000000 -> a0 =   0.015857813546
	.float	  1.040795664582	;  58 x1 =   0.914062500000 -> a1 =   1.040795664582
	.float	 -0.271306980411	;  58 x2 =   0.921875000000 -> a2 =  -0.271306980411
	.float	  0.019108017893	;  59 x0 =   0.921875000000 -> a0 =   0.019108017893
	.float	  1.033744441476	;  59 x1 =   0.929687500000 -> a1 =   1.033744441476
	.float	 -0.267482624928	;  59 x2 =   0.937500000000 -> a2 =  -0.267482624928
	.float	  0.022496252887	;  60 x0 =   0.937500000000 -> a0 =   0.022496252887
	.float	  1.026516258989	;  60 x1 =   0.945312500000 -> a1 =   1.026516258989
	.float	 -0.263627622089	;  60 x2 =   0.953125000000 -> a2 =  -0.263627622089
	.float	  0.026019221162	;  61 x0 =   0.953125000000 -> a0 =   0.026019221162
	.float	  1.019123838651	;  61 x1 =   0.960937500000 -> a1 =   1.019123838651
	.float	 -0.259749650860	;  61 x2 =   0.968750000000 -> a2 =  -0.259749650860
	.float	  0.029673465636	;  62 x0 =   0.968750000000 -> a0 =   0.029673465636
	.float	  1.011579616186	;  62 x1 =   0.976562500000 -> a1 =   1.011579616186
	.float	 -0.255855871106	;  62 x2 =   0.984375000000 -> a2 =  -0.255855871106

	.float	  0.033455390838	;  63 x0 =   0.984375000000 -> a0 =   0.033455390838
	.float	  1.003895716322	;  63 x1 =   0.992187500000 -> a1 =   1.003895716322
	.float	 -0.251952943763	;  63 x2 =   1.000000000000 -> a2 =  -0.251952943763

	.float	  0.037361283212	;  64 x0 =   1.000000000000 -> a0 =   0.037361283212
	.float	  0.996083931611	;  64 x1 =   1.007812500000 -> a1 =   0.996083931611
	.float	 -0.248047051426	;  64 x2 =   1.015625000000 -> a2 =  -0.248047051426
_CLAatan2TableEnd:
