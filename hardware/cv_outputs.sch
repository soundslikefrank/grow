EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 6
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:R R?
U 1 1 5FB847A2
P 1450 1050
F 0 "R?" V 1243 1050 50  0000 C CNN
F 1 "36k" V 1334 1050 50  0000 C CNN
F 2 "" V 1380 1050 50  0001 C CNN
F 3 "~" H 1450 1050 50  0001 C CNN
F 4 "0.1%" V 1450 1050 50  0001 C CNN "Notes"
	1    1450 1050
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 5FB847A9
P 1450 1550
F 0 "R?" V 1243 1550 50  0000 C CNN
F 1 "56k" V 1334 1550 50  0000 C CNN
F 2 "" V 1380 1550 50  0001 C CNN
F 3 "~" H 1450 1550 50  0001 C CNN
F 4 "0.1%" V 1450 1550 50  0001 C CNN "Notes"
	1    1450 1550
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FB847AF
P 1450 2000
F 0 "#PWR?" H 1450 1750 50  0001 C CNN
F 1 "GND" V 1455 1872 50  0000 R CNN
F 2 "" H 1450 2000 50  0001 C CNN
F 3 "" H 1450 2000 50  0001 C CNN
	1    1450 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 2000 1450 1700
Wire Wire Line
	1450 1400 1450 1200
Wire Wire Line
	1450 900  1250 900 
Text GLabel 1450 1300 2    50   Input ~ 0
ref_cv_out
$Comp
L Amplifier_Operational:TL072 U?
U 1 1 5FB8EC32
P 6600 2850
F 0 "U?" H 6558 2896 50  0000 L CNN
F 1 "TL072" H 6558 2805 50  0000 L CNN
F 2 "" H 6600 2850 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 6600 2850 50  0001 C CNN
F 4 "X" H 6600 2850 50  0001 C CNN "Spice_Primitive"
F 5 "TL072D" H 6600 2850 50  0001 C CNN "Spice_Model"
F 6 "Y" H 6600 2850 50  0001 C CNN "Spice_Netlist_Enabled"
F 7 "tl072-dual.cir" H 6600 2850 50  0001 C CNN "Spice_Lib_File"
	1    6600 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5FB847D0
P 6500 2250
F 0 "C?" V 6248 2250 50  0000 C CNN
F 1 "18p" V 6339 2250 50  0000 C CNN
F 2 "" H 6538 2100 50  0001 C CNN
F 3 "~" H 6500 2250 50  0001 C CNN
	1    6500 2250
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5FB847CA
P 7450 2850
F 0 "R?" V 7243 2850 50  0000 C CNN
F 1 "500" V 7334 2850 50  0000 C CNN
F 2 "" V 7380 2850 50  0001 C CNN
F 3 "~" H 7450 2850 50  0001 C CNN
	1    7450 2850
	0    1    1    0   
$EndComp
Text GLabel 6250 2500 2    50   Input ~ 0
ref_cv_out
Wire Wire Line
	5550 3450 6750 3450
Wire Wire Line
	7600 2850 7700 2850
Wire Wire Line
	7150 2850 7300 2850
Wire Wire Line
	5350 2950 5550 2950
Wire Wire Line
	7150 2850 7150 2250
Connection ~ 7150 2850
Wire Wire Line
	7150 2850 6900 2850
Wire Wire Line
	7150 2250 6650 2250
Wire Wire Line
	6350 2250 5850 2250
Wire Wire Line
	7050 3450 7700 3450
Wire Wire Line
	7700 3450 7700 2850
$Comp
L Device:R R?
U 1 1 5FB8476D
P 6900 3450
F 0 "R?" V 6693 3450 50  0000 C CNN
F 1 "36k" V 6784 3450 50  0000 C CNN
F 2 "" V 6830 3450 50  0001 C CNN
F 3 "~" H 6900 3450 50  0001 C CNN
	1    6900 3450
	0    1    1    0   
$EndComp
Wire Wire Line
	5850 2950 6300 2950
Connection ~ 5850 2950
Wire Wire Line
	5850 2250 5850 2950
Wire Wire Line
	5550 2950 5850 2950
Connection ~ 5550 2950
Wire Wire Line
	4750 2950 5050 2950
Wire Wire Line
	6150 2750 6300 2750
$Comp
L Device:R R?
U 1 1 5FB84736
P 5200 2950
F 0 "R?" V 4993 2950 50  0000 C CNN
F 1 "10k" V 5084 2950 50  0000 C CNN
F 2 "" V 5130 2950 50  0001 C CNN
F 3 "~" H 5200 2950 50  0001 C CNN
	1    5200 2950
	0    1    1    0   
$EndComp
Wire Wire Line
	5550 2950 5550 3450
$Comp
L Amplifier_Operational:TL072 U?
U 3 1 5FB8478A
P 2750 1700
F 0 "U?" H 2708 1746 50  0000 L CNN
F 1 "TL072" H 2708 1655 50  0000 L CNN
F 2 "" H 2750 1700 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 2750 1700 50  0001 C CNN
F 4 "X" H 2750 1700 50  0001 C CNN "Spice_Primitive"
F 5 "TL072D" H 2750 1700 50  0001 C CNN "Spice_Model"
F 6 "Y" H 2750 1700 50  0001 C CNN "Spice_Netlist_Enabled"
F 7 "tl072-dual.cir" H 2750 1700 50  0001 C CNN "Spice_Lib_File"
	3    2750 1700
	1    0    0    -1  
$EndComp
$Comp
L power:VEE #PWR?
U 1 1 5FB9194E
P 2650 2000
F 0 "#PWR?" H 2650 1850 50  0001 C CNN
F 1 "VEE" H 2665 2173 50  0000 C CNN
F 2 "" H 2650 2000 50  0001 C CNN
F 3 "" H 2650 2000 50  0001 C CNN
	1    2650 2000
	-1   0    0    1   
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 5FB924D1
P 2650 1400
F 0 "#PWR?" H 2650 1250 50  0001 C CNN
F 1 "VCC" H 2665 1573 50  0000 C CNN
F 2 "" H 2650 1400 50  0001 C CNN
F 3 "" H 2650 1400 50  0001 C CNN
	1    2650 1400
	1    0    0    -1  
$EndComp
Text HLabel 4750 2950 0    50   Input ~ 0
dac_channel_a
$Comp
L Amplifier_Operational:TL072 U?
U 2 1 5FB82D06
P 6600 4700
F 0 "U?" H 6558 4746 50  0000 L CNN
F 1 "TL072" H 6558 4655 50  0000 L CNN
F 2 "" H 6600 4700 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 6600 4700 50  0001 C CNN
F 4 "X" H 6600 4700 50  0001 C CNN "Spice_Primitive"
F 5 "TL072D" H 6600 4700 50  0001 C CNN "Spice_Model"
F 6 "Y" H 6600 4700 50  0001 C CNN "Spice_Netlist_Enabled"
F 7 "tl072-dual.cir" H 6600 4700 50  0001 C CNN "Spice_Lib_File"
	2    6600 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5FB82D0C
P 6500 4100
F 0 "C?" V 6248 4100 50  0000 C CNN
F 1 "18p" V 6339 4100 50  0000 C CNN
F 2 "" H 6538 3950 50  0001 C CNN
F 3 "~" H 6500 4100 50  0001 C CNN
	1    6500 4100
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5FB82D12
P 7450 4700
F 0 "R?" V 7243 4700 50  0000 C CNN
F 1 "500" V 7334 4700 50  0000 C CNN
F 2 "" V 7380 4700 50  0001 C CNN
F 3 "~" H 7450 4700 50  0001 C CNN
	1    7450 4700
	0    1    1    0   
$EndComp
Wire Wire Line
	5550 5300 6750 5300
Wire Wire Line
	7600 4700 7700 4700
Wire Wire Line
	7150 4700 7300 4700
Wire Wire Line
	5350 4800 5550 4800
Wire Wire Line
	7150 4700 7150 4100
Connection ~ 7150 4700
Wire Wire Line
	7150 4700 6900 4700
Wire Wire Line
	7150 4100 6650 4100
Wire Wire Line
	6350 4100 5850 4100
Wire Wire Line
	7050 5300 7700 5300
Wire Wire Line
	7700 5300 7700 4700
Connection ~ 7700 4700
$Comp
L Device:R R?
U 1 1 5FB82D26
P 6900 5300
F 0 "R?" V 6693 5300 50  0000 C CNN
F 1 "36k" V 6784 5300 50  0000 C CNN
F 2 "" V 6830 5300 50  0001 C CNN
F 3 "~" H 6900 5300 50  0001 C CNN
	1    6900 5300
	0    1    1    0   
$EndComp
Wire Wire Line
	5850 4800 6300 4800
Connection ~ 5850 4800
Wire Wire Line
	5850 4100 5850 4800
Wire Wire Line
	5550 4800 5850 4800
Connection ~ 5550 4800
Wire Wire Line
	4750 4800 5050 4800
$Comp
L Device:R R?
U 1 1 5FB82D35
P 5200 4800
F 0 "R?" V 4993 4800 50  0000 C CNN
F 1 "10k" V 5084 4800 50  0000 C CNN
F 2 "" V 5130 4800 50  0001 C CNN
F 3 "~" H 5200 4800 50  0001 C CNN
	1    5200 4800
	0    1    1    0   
$EndComp
Wire Wire Line
	5550 4800 5550 5300
Text HLabel 4750 4800 0    50   Input ~ 0
dac_channel_b
$Comp
L Device:C C?
U 1 1 5FB976CE
P 3650 1600
F 0 "C?" V 3398 1600 50  0000 C CNN
F 1 "100n" V 3489 1600 50  0000 C CNN
F 2 "" H 3688 1450 50  0001 C CNN
F 3 "~" H 3650 1600 50  0001 C CNN
	1    3650 1600
	-1   0    0    1   
$EndComp
$Comp
L Device:C C?
U 1 1 5FB97D49
P 4250 1600
F 0 "C?" V 3998 1600 50  0000 C CNN
F 1 "100n" V 4089 1600 50  0000 C CNN
F 2 "" H 4288 1450 50  0001 C CNN
F 3 "~" H 4250 1600 50  0001 C CNN
	1    4250 1600
	-1   0    0    1   
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 5FB9836B
P 3650 1450
F 0 "#PWR?" H 3650 1300 50  0001 C CNN
F 1 "VCC" H 3665 1623 50  0000 C CNN
F 2 "" H 3650 1450 50  0001 C CNN
F 3 "" H 3650 1450 50  0001 C CNN
	1    3650 1450
	1    0    0    -1  
$EndComp
$Comp
L power:VEE #PWR?
U 1 1 5FB98880
P 4250 1450
F 0 "#PWR?" H 4250 1300 50  0001 C CNN
F 1 "VEE" H 4265 1623 50  0000 C CNN
F 2 "" H 4250 1450 50  0001 C CNN
F 3 "" H 4250 1450 50  0001 C CNN
	1    4250 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FB99275
P 3950 1950
F 0 "#PWR?" H 3950 1700 50  0001 C CNN
F 1 "GND" V 3955 1822 50  0000 R CNN
F 2 "" H 3950 1950 50  0001 C CNN
F 3 "" H 3950 1950 50  0001 C CNN
	1    3950 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 1750 3650 1950
Wire Wire Line
	3650 1950 3950 1950
Wire Wire Line
	4250 1750 4250 1950
Wire Wire Line
	3950 1950 4250 1950
Connection ~ 3950 1950
Text HLabel 1250 900  0    50   Input ~ 0
dac_ref
Wire Wire Line
	6150 2500 6250 2500
Wire Wire Line
	6150 2500 6150 2750
Text GLabel 6250 4350 2    50   Input ~ 0
ref_cv_out
Wire Wire Line
	6150 4600 6300 4600
Wire Wire Line
	6150 4350 6250 4350
Wire Wire Line
	6150 4350 6150 4600
$Comp
L thonkiconn_jackSocket_fuzzySi:fuzzySI_thonkiconn J?
U 1 1 5FBBD658
P 8100 2750
F 0 "J?" H 7812 2726 50  0000 R CNN
F 1 "CV_OUT_A" H 7812 2817 50  0000 R CNN
F 2 "" H 8350 2850 50  0001 C CNN
F 3 "" H 8350 2850 50  0001 C CNN
	1    8100 2750
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FBBFB43
P 8300 2550
F 0 "#PWR?" H 8300 2300 50  0001 C CNN
F 1 "GND" V 8305 2422 50  0000 R CNN
F 2 "" H 8300 2550 50  0001 C CNN
F 3 "" H 8300 2550 50  0001 C CNN
	1    8300 2550
	-1   0    0    1   
$EndComp
Wire Wire Line
	8300 2550 8300 2650
$Comp
L thonkiconn_jackSocket_fuzzySi:fuzzySI_thonkiconn J?
U 1 1 5FBC556B
P 8100 4600
F 0 "J?" H 7812 4576 50  0000 R CNN
F 1 "CV_OUT_B" H 7812 4667 50  0000 R CNN
F 2 "" H 8350 4700 50  0001 C CNN
F 3 "" H 8350 4700 50  0001 C CNN
	1    8100 4600
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FBC5571
P 8300 4400
F 0 "#PWR?" H 8300 4150 50  0001 C CNN
F 1 "GND" V 8305 4272 50  0000 R CNN
F 2 "" H 8300 4400 50  0001 C CNN
F 3 "" H 8300 4400 50  0001 C CNN
	1    8300 4400
	-1   0    0    1   
$EndComp
Wire Wire Line
	8300 4400 8300 4500
Wire Wire Line
	7700 2850 7900 2850
Connection ~ 7700 2850
Wire Wire Line
	7700 4700 7900 4700
$EndSCHEMATC
