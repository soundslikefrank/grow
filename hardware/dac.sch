EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 9
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
L power:GND #PWR0106
U 1 1 5ED3A9D0
P 6400 3950
F 0 "#PWR0106" H 6400 3700 50  0001 C CNN
F 1 "GND" V 6405 3822 50  0000 R CNN
F 2 "" H 6400 3950 50  0001 C CNN
F 3 "" H 6400 3950 50  0001 C CNN
	1    6400 3950
	0    -1   -1   0   
$EndComp
Text HLabel 4450 3850 0    50   Input ~ 0
dac_clk
Text HLabel 4450 3950 0    50   Input ~ 0
dac_mosi
Text HLabel 4450 3750 0    50   Input ~ 0
dac_cs
$Comp
L DAC8562:DAC8562SDGSR IC?
U 1 1 5FB5B9A5
P 6150 4150
F 0 "IC?" H 7000 4415 50  0000 C CNN
F 1 "DAC8562SDGSR" H 7000 4324 50  0000 C CNN
F 2 "SOP50P490X110-10N" H 7700 4250 50  0001 L CNN
F 3 "http://www.ti.com/lit/gpn/dac8562" H 7700 4150 50  0001 L CNN
F 4 "16-bit, dual-channel, low-power, ultra-low glitch, voltage output DAC with 2.5V, 4ppm/C reference" H 7700 4050 50  0001 L CNN "Description"
F 5 "1.1" H 7700 3950 50  0001 L CNN "Height"
F 6 "Texas Instruments" H 7700 3850 50  0001 L CNN "Manufacturer_Name"
F 7 "DAC8562SDGSR" H 7700 3750 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "DAC8562SDGSR" H 7700 3650 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/dac8562sdgsr/texas-instruments" H 7700 3550 50  0001 L CNN "Arrow Price/Stock"
F 10 "595-DAC8562SDGSR" H 7700 3450 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Texas-Instruments/DAC8562SDGSR?qs=L4ss%2FyqpMWQjhHzbOFnTNg%3D%3D" H 7700 3350 50  0001 L CNN "Mouser Price/Stock"
	1    6150 4150
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5FB5E7F1
P 6550 2150
F 0 "#PWR0107" H 6550 1900 50  0001 C CNN
F 1 "GND" H 6555 1977 50  0000 C CNN
F 2 "" H 6550 2150 50  0001 C CNN
F 3 "" H 6550 2150 50  0001 C CNN
	1    6550 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 3950 6300 3950
Wire Wire Line
	6150 3850 6300 3850
Wire Wire Line
	6300 3850 6300 3950
Connection ~ 6300 3950
Wire Wire Line
	6300 3950 6400 3950
$Comp
L Device:C C?
U 1 1 5FB6035A
P 6550 2000
F 0 "C?" H 6435 1954 50  0000 R CNN
F 1 "220n" H 6435 2045 50  0000 R CNN
F 2 "" H 6588 1850 50  0001 C CNN
F 3 "~" H 6550 2000 50  0001 C CNN
	1    6550 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5FB6078F
P 4600 2000
F 0 "C?" H 4485 1954 50  0000 R CNN
F 1 "1u" H 4485 2045 50  0000 R CNN
F 2 "" H 4638 1850 50  0001 C CNN
F 3 "~" H 4600 2000 50  0001 C CNN
	1    4600 2000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5FB62572
P 4800 2300
F 0 "#PWR0108" H 4800 2050 50  0001 C CNN
F 1 "GND" H 4805 2127 50  0000 C CNN
F 2 "" H 4800 2300 50  0001 C CNN
F 3 "" H 4800 2300 50  0001 C CNN
	1    4800 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 4050 7200 4050
Wire Wire Line
	6150 4150 6600 4150
Wire Wire Line
	6600 4150 6600 4300
Wire Wire Line
	6600 4300 7200 4300
$Sheet
S 7200 3950 950  650 
U 5FB5AC07
F0 "CV Outputs" 50
F1 "cv_outputs.sch" 50
F2 "dac_channel_a" I L 7200 4050 50 
F3 "dac_channel_b" I L 7200 4300 50 
F4 "dac_ref" I L 7200 4500 50 
$EndSheet
$Comp
L Device:C C?
U 1 1 5FB90B4F
P 5000 2000
F 0 "C?" H 5115 2046 50  0000 L CNN
F 1 "100n" H 5115 1955 50  0000 L CNN
F 2 "" H 5038 1850 50  0001 C CNN
F 3 "~" H 5000 2000 50  0001 C CNN
	1    5000 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 2150 4600 2300
Wire Wire Line
	4600 2300 4800 2300
Wire Wire Line
	5000 2300 4800 2300
Wire Wire Line
	5000 2150 5000 2300
Connection ~ 4800 2300
Text GLabel 5350 1850 2    50   Input ~ 0
dac_avdd
Text GLabel 4450 4050 0    50   Input ~ 0
dac_avdd
Text GLabel 4450 4150 0    50   Input ~ 0
dac_vref
Text GLabel 7200 4500 0    50   Input ~ 0
dac_vref
Text GLabel 6550 1850 1    50   Input ~ 0
dac_vref
Wire Wire Line
	5000 1850 5350 1850
Text Notes 4400 4650 0    50   ~ 0
Check Layout example in datasheet!!
$Comp
L power:+3V3 #PWR0109
U 1 1 5FD27C48
P 6400 3350
F 0 "#PWR0109" H 6400 3200 50  0001 C CNN
F 1 "+3V3" H 6415 3523 50  0000 C CNN
F 2 "" H 6400 3350 50  0001 C CNN
F 3 "" H 6400 3350 50  0001 C CNN
	1    6400 3350
	1    0    0    -1  
$EndComp
Text GLabel 4250 1850 0    50   Input ~ 0
ref_5v
Connection ~ 5000 1850
Wire Wire Line
	4250 1850 4600 1850
Connection ~ 4600 1850
Wire Wire Line
	4600 1850 5000 1850
Wire Wire Line
	6150 3750 6400 3750
Wire Wire Line
	6400 3750 6400 3700
$Comp
L Device:R R?
U 1 1 5FB72111
P 6400 3550
F 0 "R?" H 6470 3596 50  0000 L CNN
F 1 "10k" H 6470 3505 50  0000 L CNN
F 2 "" V 6330 3550 50  0001 C CNN
F 3 "~" H 6400 3550 50  0001 C CNN
	1    6400 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 3350 6400 3400
$EndSCHEMATC
