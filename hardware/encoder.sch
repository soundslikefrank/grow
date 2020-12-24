EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 9 11
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
L PEC11R-4220F-S0024:PEC11R-4220F-S0024 VR11
U 1 1 5FDF0E4F
P 5950 3050
F 0 "VR11" H 6800 3500 50  0000 L CNN
F 1 "PEC11R-4220F-S0024" H 6800 3400 50  0000 L CNN
F 2 "PEC11R-4220F-S0024:PEC11R4220FS0024" H 6800 3350 50  0001 L CNN
F 3 "https://www.bourns.com/docs/Product-Datasheets/PEC11R.pdf" H 6800 3250 50  0001 L CNN
F 4 "Bourns 24 Pulse Incremental Mechanical Rotary Encoder with a 6 mm Flat Shaft (Not Indexed), Through Hole" H 6800 3150 50  0001 L CNN "Description"
F 5 "27.5" H 6800 3050 50  0001 L CNN "Height"
F 6 "Bourns" H 6800 2950 50  0001 L CNN "Manufacturer_Name"
F 7 "PEC11R-4220F-S0024" H 6800 2850 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "PEC11R-4220F-S0024" H 6800 2750 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/pec11r-4220f-s0024/bourns" H 6800 2650 50  0001 L CNN "Arrow Price/Stock"
F 10 "652-PEC11R-4220F-S24" H 6800 2550 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Bourns/PEC11R-4220F-S0024?qs=Zq5ylnUbLm6NGsQdib%2Ffbw%3D%3D" H 6800 2450 50  0001 L CNN "Mouser Price/Stock"
	1    5950 3050
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5FDF2434
P 4950 3050
F 0 "#PWR0101" H 4950 2800 50  0001 C CNN
F 1 "GND" V 4955 2922 50  0000 R CNN
F 2 "" H 4950 3050 50  0001 C CNN
F 3 "" H 4950 3050 50  0001 C CNN
	1    4950 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	5450 1750 5450 1800
$Comp
L power:+3V3 #PWR?
U 1 1 5FDF7D49
P 5450 1750
AR Path="/5ED37B53/5FDF7D49" Ref="#PWR?"  Part="1" 
AR Path="/5FDF0A57/5FDF7D49" Ref="#PWR0102"  Part="1" 
F 0 "#PWR0102" H 5450 1600 50  0001 C CNN
F 1 "+3V3" H 5465 1923 50  0000 C CNN
F 2 "" H 5450 1750 50  0001 C CNN
F 3 "" H 5450 1750 50  0001 C CNN
	1    5450 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5FDF7D4F
P 5150 2100
AR Path="/5ED37B53/5FDF7D4F" Ref="R?"  Part="1" 
AR Path="/5FDF0A57/5FDF7D4F" Ref="R27"  Part="1" 
F 0 "R27" H 5220 2146 50  0000 L CNN
F 1 "10k" H 5220 2055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5080 2100 50  0001 C CNN
F 3 "~" H 5150 2100 50  0001 C CNN
	1    5150 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5FDFB593
P 5750 2100
AR Path="/5ED37B53/5FDFB593" Ref="R?"  Part="1" 
AR Path="/5FDF0A57/5FDFB593" Ref="R28"  Part="1" 
F 0 "R28" H 5820 2146 50  0000 L CNN
F 1 "10k" H 5820 2055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5680 2100 50  0001 C CNN
F 3 "~" H 5750 2100 50  0001 C CNN
	1    5750 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 2250 5150 2450
Wire Wire Line
	5150 2550 5350 2550
Wire Wire Line
	5750 2250 5750 2450
Wire Wire Line
	5750 2550 5550 2550
Text HLabel 6250 2450 2    50   Output ~ 0
encoder_b
Wire Wire Line
	5750 2450 6250 2450
Connection ~ 5750 2450
Wire Wire Line
	5750 2450 5750 2550
Text HLabel 4650 2450 0    50   Output ~ 0
encoder_a
Wire Wire Line
	5150 2450 4650 2450
Connection ~ 5150 2450
Wire Wire Line
	5150 2450 5150 2550
Text HLabel 6000 3600 2    50   Output ~ 0
encoder_sw
Wire Wire Line
	5550 3550 5550 3600
Wire Wire Line
	5550 3600 6000 3600
Wire Wire Line
	5450 2200 5450 2550
Wire Wire Line
	5450 1800 5150 1800
Wire Wire Line
	5150 1800 5150 1950
Wire Wire Line
	5450 1800 5750 1800
Wire Wire Line
	5750 1800 5750 1950
Connection ~ 5450 1800
$Comp
L power:GND #PWR0103
U 1 1 5FF3D410
P 5450 2200
F 0 "#PWR0103" H 5450 1950 50  0001 C CNN
F 1 "GND" H 5455 2027 50  0000 C CNN
F 2 "" H 5450 2200 50  0001 C CNN
F 3 "" H 5450 2200 50  0001 C CNN
	1    5450 2200
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5FF3E986
P 5450 3550
F 0 "#PWR0104" H 5450 3300 50  0001 C CNN
F 1 "GND" H 5455 3377 50  0000 C CNN
F 2 "" H 5450 3550 50  0001 C CNN
F 3 "" H 5450 3550 50  0001 C CNN
	1    5450 3550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5FF3FBE0
P 5950 3050
F 0 "#PWR0105" H 5950 2800 50  0001 C CNN
F 1 "GND" H 5955 2877 50  0000 C CNN
F 2 "" H 5950 3050 50  0001 C CNN
F 3 "" H 5950 3050 50  0001 C CNN
	1    5950 3050
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
