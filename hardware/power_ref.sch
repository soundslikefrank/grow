EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 8 11
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	7500 1350 7500 1550
Wire Wire Line
	7500 1550 7800 1550
Wire Wire Line
	8350 1550 8350 1750
$Comp
L power:GND #PWR097
U 1 1 5FDFEFF3
P 8350 2400
F 0 "#PWR097" H 8350 2150 50  0001 C CNN
F 1 "GND" H 8355 2227 50  0000 C CNN
F 2 "" H 8350 2400 50  0001 C CNN
F 3 "" H 8350 2400 50  0001 C CNN
	1    8350 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 2050 8350 2400
Wire Wire Line
	8100 1550 8350 1550
$Comp
L Device:R R26
U 1 1 5FDFEFFC
P 7950 1550
F 0 "R26" V 7743 1550 50  0000 C CNN
F 1 "1k8" V 7834 1550 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7880 1550 50  0001 C CNN
F 3 "~" H 7950 1550 50  0001 C CNN
F 4 "0-2mA, 3k3 - 7k ohm" V 7950 1550 50  0001 C CNN "Note"
	1    7950 1550
	0    1    1    0   
$EndComp
$Comp
L Device:C C39
U 1 1 5FDFF002
P 9200 1900
F 0 "C39" H 9315 1946 50  0000 L CNN
F 1 "1u" H 9315 1855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9238 1750 50  0001 C CNN
F 3 "~" H 9200 1900 50  0001 C CNN
	1    9200 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 1550 9200 1550
Wire Wire Line
	9200 1550 9200 1750
Connection ~ 8350 1550
$Comp
L power:GND #PWR098
U 1 1 5FDFF00B
P 9200 2400
F 0 "#PWR098" H 9200 2150 50  0001 C CNN
F 1 "GND" H 9205 2227 50  0000 C CNN
F 2 "" H 9200 2400 50  0001 C CNN
F 3 "" H 9200 2400 50  0001 C CNN
	1    9200 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 2050 9200 2400
Connection ~ 9200 1550
Wire Wire Line
	9200 1550 9700 1550
Wire Notes Line
	7200 1000 7200 2750
Wire Notes Line
	7200 2750 10200 2750
Wire Notes Line
	10200 1000 7200 1000
Text Notes 7200 950  0    50   ~ 0
-10V reference
$Comp
L power:VEE #PWR095
U 1 1 5FDFF018
P 7500 1350
F 0 "#PWR095" H 7500 1200 50  0001 C CNN
F 1 "VEE" H 7515 1523 50  0000 C CNN
F 2 "" H 7500 1350 50  0001 C CNN
F 3 "" H 7500 1350 50  0001 C CNN
	1    7500 1350
	1    0    0    -1  
$EndComp
$Comp
L Reference_Voltage:LM4040DBZ-10 U5
U 1 1 5FDFF01E
P 8350 1900
F 0 "U5" V 8304 1979 50  0000 L CNN
F 1 "LM4040DBZ-10" V 8395 1979 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8350 1700 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm4040-n.pdf" H 8350 1900 50  0001 C CIN
	1    8350 1900
	0    1    1    0   
$EndComp
Text Notes 9400 1550 0    50   ~ 0
0.1mA
$Comp
L power:VCC #PWR077
U 1 1 5FDFF026
P 1600 4050
F 0 "#PWR077" H 1600 3900 50  0001 C CNN
F 1 "VCC" V 1618 4177 50  0000 L CNN
F 2 "" H 1600 4050 50  0001 C CNN
F 3 "" H 1600 4050 50  0001 C CNN
	1    1600 4050
	0    -1   -1   0   
$EndComp
Wire Notes Line
	1000 3550 1000 4750
Text Notes 1000 3500 0    50   ~ 0
+5V Voltage Regulator
Wire Notes Line
	1000 4750 5100 4750
Wire Notes Line
	5100 3550 1000 3550
Wire Notes Line
	5100 4750 5100 3550
Connection ~ 4500 4050
$Comp
L Device:C C37
U 1 1 5FDFF032
P 4500 4200
F 0 "C37" H 4385 4154 50  0000 R CNN
F 1 "22u" H 4385 4245 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4538 4050 50  0001 C CNN
F 3 "~" H 4500 4200 50  0001 C CNN
	1    4500 4200
	-1   0    0    1   
$EndComp
Wire Wire Line
	2650 4050 3000 4050
Connection ~ 2650 4050
$Comp
L Device:C C31
U 1 1 5FDFF03C
P 2650 4200
F 0 "C31" H 2535 4154 50  0000 R CNN
F 1 "10u" H 2535 4245 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2688 4050 50  0001 C CNN
F 3 "~" H 2650 4200 50  0001 C CNN
	1    2650 4200
	-1   0    0    1   
$EndComp
Wire Wire Line
	2450 4050 2650 4050
$Comp
L power:+5V #PWR091
U 1 1 5FDFF049
P 4500 4050
F 0 "#PWR091" H 4500 3900 50  0001 C CNN
F 1 "+5V" H 4515 4223 50  0000 C CNN
F 2 "" H 4500 4050 50  0001 C CNN
F 3 "" H 4500 4050 50  0001 C CNN
	1    4500 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR088
U 1 1 5FDFF04F
P 3950 4350
F 0 "#PWR088" H 3950 4100 50  0001 C CNN
F 1 "GND" H 3955 4177 50  0000 C CNN
F 2 "" H 3950 4350 50  0001 C CNN
F 3 "" H 3950 4350 50  0001 C CNN
	1    3950 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 4050 4500 4050
Connection ~ 3950 4050
Wire Wire Line
	3600 4050 3950 4050
$Comp
L Device:C C34
U 1 1 5FDFF058
P 3950 4200
F 0 "C34" H 4065 4246 50  0000 L CNN
F 1 "100n" H 4065 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3988 4050 50  0001 C CNN
F 3 "~" H 3950 4200 50  0001 C CNN
	1    3950 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR092
U 1 1 5FDFF05E
P 4500 4350
F 0 "#PWR092" H 4500 4100 50  0001 C CNN
F 1 "GND" H 4505 4177 50  0000 C CNN
F 2 "" H 4500 4350 50  0001 C CNN
F 3 "" H 4500 4350 50  0001 C CNN
	1    4500 4350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR083
U 1 1 5FDFF064
P 2650 4350
F 0 "#PWR083" H 2650 4100 50  0001 C CNN
F 1 "GND" H 2655 4177 50  0000 C CNN
F 2 "" H 2650 4350 50  0001 C CNN
F 3 "" H 2650 4350 50  0001 C CNN
	1    2650 4350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR081
U 1 1 5FDFF06A
P 1950 4350
F 0 "#PWR081" H 1950 4100 50  0001 C CNN
F 1 "GND" H 1955 4177 50  0000 C CNN
F 2 "" H 1950 4350 50  0001 C CNN
F 3 "" H 1950 4350 50  0001 C CNN
	1    1950 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:L L1
U 1 1 5FDFF070
P 2300 4050
F 0 "L1" V 2490 4050 50  0000 C CNN
F 1 "10u" V 2399 4050 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" H 2300 4050 50  0001 C CNN
F 3 "~" H 2300 4050 50  0001 C CNN
	1    2300 4050
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR085
U 1 1 5FDFF076
P 3300 4350
F 0 "#PWR085" H 3300 4100 50  0001 C CNN
F 1 "GND" H 3305 4177 50  0000 C CNN
F 2 "" H 3300 4350 50  0001 C CNN
F 3 "" H 3300 4350 50  0001 C CNN
	1    3300 4350
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Switching:R-78E5.0-0.5 U4
U 1 1 5FDFF07C
P 3300 4050
F 0 "U4" H 3300 4292 50  0000 C CNN
F 1 "R-78E5.0-0.5" H 3300 4201 50  0000 C CNN
F 2 "Converter_DCDC:Converter_DCDC_RECOM_R-78E-0.5_THT" H 3350 3800 50  0001 L CIN
F 3 "https://www.recom-power.com/pdf/Innoline/R-78Exx-0.5.pdf" H 3300 4050 50  0001 C CNN
	1    3300 4050
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J8
U 1 1 5FDFF083
P 2050 1900
F 0 "J8" H 2100 2317 50  0000 C CNN
F 1 "Eurorack PWR" H 2100 2226 50  0000 C CNN
F 2 "Connector_IDC:IDC-Header_2x05_P2.54mm_Vertical" H 2050 1900 50  0001 C CNN
F 3 "~" H 2050 1900 50  0001 C CNN
	1    2050 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 1700 2350 1700
Wire Wire Line
	1850 2100 2350 2100
Wire Wire Line
	2350 1800 1850 1800
Wire Wire Line
	2350 1900 1850 1900
Wire Wire Line
	2350 2000 1850 2000
Wire Wire Line
	1850 1800 1850 1900
Connection ~ 1850 1800
Connection ~ 1850 1900
Wire Wire Line
	1850 2000 1850 1900
Connection ~ 1850 2000
$Comp
L power:GND #PWR078
U 1 1 5FDFF093
P 1700 1900
F 0 "#PWR078" H 1700 1650 50  0001 C CNN
F 1 "GND" V 1705 1772 50  0000 R CNN
F 2 "" H 1700 1900 50  0001 C CNN
F 3 "" H 1700 1900 50  0001 C CNN
	1    1700 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	1850 1900 1700 1900
$Comp
L Device:Ferrite_Bead FB2
U 1 1 5FDFF09C
P 3600 2100
F 0 "FB2" V 3326 2100 50  0000 C CNN
F 1 "100 @ 100MHz" V 3417 2100 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" V 3530 2100 50  0001 C CNN
F 3 "~" H 3600 2100 50  0001 C CNN
	1    3600 2100
	0    1    1    0   
$EndComp
$Comp
L Device:Ferrite_Bead FB1
U 1 1 5FDFF0A2
P 3600 1700
F 0 "FB1" V 3326 1700 50  0000 C CNN
F 1 "100 @ 100MHz" V 3417 1700 50  0000 C CNN
F 2 "Inductor_SMD:L_0805_2012Metric" V 3530 1700 50  0001 C CNN
F 3 "~" H 3600 1700 50  0001 C CNN
	1    3600 1700
	0    1    1    0   
$EndComp
$Comp
L power:-12V #PWR079
U 1 1 5FDFF0A8
P 1850 1700
F 0 "#PWR079" H 1850 1800 50  0001 C CNN
F 1 "-12V" V 1865 1828 50  0000 L CNN
F 2 "" H 1850 1700 50  0001 C CNN
F 3 "" H 1850 1700 50  0001 C CNN
	1    1850 1700
	0    -1   -1   0   
$EndComp
Connection ~ 1850 1700
$Comp
L power:+12V #PWR080
U 1 1 5FDFF0AF
P 1850 2100
F 0 "#PWR080" H 1850 1950 50  0001 C CNN
F 1 "+12V" V 1865 2228 50  0000 L CNN
F 2 "" H 1850 2100 50  0001 C CNN
F 3 "" H 1850 2100 50  0001 C CNN
	1    1850 2100
	0    -1   -1   0   
$EndComp
Connection ~ 1850 2100
Wire Wire Line
	2350 1800 2350 1900
Connection ~ 2350 1800
Connection ~ 2350 1900
Wire Wire Line
	2350 1900 2350 2000
Connection ~ 2350 2000
$Comp
L power:GND #PWR093
U 1 1 5FDFF0BB
P 4750 1900
F 0 "#PWR093" H 4750 1650 50  0001 C CNN
F 1 "GND" V 4755 1772 50  0000 R CNN
F 2 "" H 4750 1900 50  0001 C CNN
F 3 "" H 4750 1900 50  0001 C CNN
	1    4750 1900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4550 2100 4750 2100
Wire Wire Line
	4750 2100 4750 1900
Wire Wire Line
	4550 1700 4750 1700
Wire Wire Line
	4750 1700 4750 1900
Connection ~ 4750 1900
Wire Wire Line
	3750 1700 4050 1700
Wire Wire Line
	4050 1450 4050 1700
Connection ~ 4050 1700
Wire Wire Line
	4050 1700 4250 1700
Wire Wire Line
	3750 2100 4050 2100
$Comp
L power:VEE #PWR089
U 1 1 5FDFF0D1
P 4050 1450
F 0 "#PWR089" H 4050 1300 50  0001 C CNN
F 1 "VEE" H 4067 1623 50  0000 C CNN
F 2 "" H 4050 1450 50  0001 C CNN
F 3 "" H 4050 1450 50  0001 C CNN
	1    4050 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 2100 4050 2350
Connection ~ 4050 2100
Wire Wire Line
	4050 2100 4250 2100
Wire Wire Line
	3050 1700 3450 1700
Wire Wire Line
	3050 2100 3450 2100
Wire Notes Line
	1000 1100 1000 2700
Wire Notes Line
	1000 2700 5500 2700
Wire Notes Line
	5500 2700 5500 1100
Wire Notes Line
	5500 1100 1000 1100
Text Notes 1000 1050 0    50   ~ 0
+12/-12V Power
$Comp
L Device:C C35
U 1 1 5FDFF0E1
P 4400 1700
F 0 "C35" V 4148 1700 50  0000 C CNN
F 1 "22u" V 4239 1700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4438 1550 50  0001 C CNN
F 3 "~" H 4400 1700 50  0001 C CNN
	1    4400 1700
	0    1    1    0   
$EndComp
$Comp
L Device:C C36
U 1 1 5FDFF0E7
P 4400 2100
F 0 "C36" V 4148 2100 50  0000 C CNN
F 1 "22u" V 4239 2100 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4438 1950 50  0001 C CNN
F 3 "~" H 4400 2100 50  0001 C CNN
	1    4400 2100
	0    1    1    0   
$EndComp
$Comp
L Diode:1N5819 D11
U 1 1 5FDFF0ED
P 2900 2100
F 0 "D11" H 2900 1884 50  0000 C CNN
F 1 "1N5819" H 2900 1975 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 2900 1925 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88525/1n5817.pdf" H 2900 2100 50  0001 C CNN
	1    2900 2100
	-1   0    0    1   
$EndComp
$Comp
L Diode:1N5819 D10
U 1 1 5FDFF0F3
P 2900 1700
F 0 "D10" H 2900 1916 50  0000 C CNN
F 1 "1N5819" H 2900 1825 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 2900 1525 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88525/1n5817.pdf" H 2900 1700 50  0001 C CNN
	1    2900 1700
	1    0    0    -1  
$EndComp
Wire Notes Line
	10200 2750 10200 1000
$Comp
L power:+5V #PWR076
U 1 1 5FDFF10A
P 1450 6150
F 0 "#PWR076" H 1450 6000 50  0001 C CNN
F 1 "+5V" V 1465 6278 50  0000 L CNN
F 2 "" H 1450 6150 50  0001 C CNN
F 3 "" H 1450 6150 50  0001 C CNN
	1    1450 6150
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C32
U 1 1 5FDFF116
P 2800 6300
F 0 "C32" H 2915 6346 50  0000 L CNN
F 1 "100n" H 2915 6255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2838 6150 50  0001 C CNN
F 3 "~" H 2800 6300 50  0001 C CNN
	1    2800 6300
	1    0    0    -1  
$EndComp
Connection ~ 2800 6150
$Comp
L power:GND #PWR084
U 1 1 5FDFF11D
P 2800 6450
F 0 "#PWR084" H 2800 6200 50  0001 C CNN
F 1 "GND" H 2805 6277 50  0000 C CNN
F 2 "" H 2800 6450 50  0001 C CNN
F 3 "" H 2800 6450 50  0001 C CNN
	1    2800 6450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR086
U 1 1 5FDFF123
P 3500 6450
F 0 "#PWR086" H 3500 6200 50  0001 C CNN
F 1 "GND" H 3505 6277 50  0000 C CNN
F 2 "" H 3500 6450 50  0001 C CNN
F 3 "" H 3500 6450 50  0001 C CNN
	1    3500 6450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR082
U 1 1 5FDFF12F
P 2050 6450
F 0 "#PWR082" H 2050 6200 50  0001 C CNN
F 1 "GND" H 2055 6277 50  0000 C CNN
F 2 "" H 2050 6450 50  0001 C CNN
F 3 "" H 2050 6450 50  0001 C CNN
	1    2050 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 6150 2350 6150
Wire Notes Line
	1050 6900 4400 6900
Wire Notes Line
	4400 6900 4400 5650
Wire Notes Line
	4400 5650 1050 5650
Wire Notes Line
	1050 5650 1050 6900
Text Notes 1050 5600 0    50   ~ 0
+3.3V Voltage Regulator
Wire Wire Line
	1450 6150 1750 6150
$Comp
L Device:C C33
U 1 1 5FDFF13C
P 3500 6300
F 0 "C33" H 3615 6346 50  0000 L CNN
F 1 "10u" H 3615 6255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3538 6150 50  0001 C CNN
F 3 "~" H 3500 6300 50  0001 C CNN
	1    3500 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 6150 3500 6150
Connection ~ 3500 6150
Wire Wire Line
	3500 6150 3850 6150
$Comp
L power:+3V3 #PWR087
U 1 1 5FE03B05
P 3850 6150
F 0 "#PWR087" H 3850 6000 50  0001 C CNN
F 1 "+3V3" V 3865 6278 50  0000 L CNN
F 2 "" H 3850 6150 50  0001 C CNN
F 3 "" H 3850 6150 50  0001 C CNN
	1    3850 6150
	0    1    1    0   
$EndComp
$Comp
L Regulator_Linear:LM1117-3.3 U3
U 1 1 5FE054D4
P 2050 6150
F 0 "U3" H 2050 6392 50  0000 C CNN
F 1 "LM1117-3.3" H 2050 6301 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223" H 2050 6150 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm1117.pdf" H 2050 6150 50  0001 C CNN
	1    2050 6150
	1    0    0    -1  
$EndComp
Text Notes 2950 3500 0    50   ~ 0
out ca. 250mA max (witth all LEDs on 100% brightness)
Wire Notes Line
	7050 4800 10400 4800
Wire Notes Line
	10400 4800 10400 3550
Wire Notes Line
	10400 3550 7050 3550
Wire Notes Line
	7050 3550 7050 4800
Text Notes 7050 3500 0    50   ~ 0
+3.3VA Voltage Regulator
$Comp
L ADP150AUJZ-3.3-R7:ADP150AUJZ-3.3-R7 IC5
U 1 1 5FEA5AF6
P 8350 4000
F 0 "IC5" H 8900 4265 50  0000 C CNN
F 1 "ADP150AUJZ-3.3-R7" H 8900 4174 50  0000 C CNN
F 2 "ADP150AUJZ-3.3-R7:SOT95P280X100-5N" H 9300 4100 50  0001 L CNN
F 3 "http://www.analog.com/media/en/technical-documentation/data-sheets/ADP150.pdf" H 9300 4000 50  0001 L CNN
F 4 "Linear Voltage Regulators Ultralow Noise 150mA CMOS" H 9300 3900 50  0001 L CNN "Description"
F 5 "1" H 9300 3800 50  0001 L CNN "Height"
F 6 "Linear Technology" H 9300 3700 50  0001 L CNN "Manufacturer_Name"
F 7 "ADP150AUJZ-3.3-R7" H 9300 3600 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 9300 3500 50  0001 L CNN "Arrow Part Number"
F 9 "" H 9300 3400 50  0001 L CNN "Arrow Price/Stock"
F 10 "584-ADP150AUJZ-3.3R7" H 9300 3300 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.com/Search/Refine.aspx?Keyword=584-ADP150AUJZ-3.3R7" H 9300 3200 50  0001 L CNN "Mouser Price/Stock"
	1    8350 4000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR094
U 1 1 5FEA3E47
P 7450 4000
F 0 "#PWR094" H 7450 3850 50  0001 C CNN
F 1 "+5V" V 7465 4128 50  0000 L CNN
F 2 "" H 7450 4000 50  0001 C CNN
F 3 "" H 7450 4000 50  0001 C CNN
	1    7450 4000
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C38
U 1 1 5FEB0915
P 7750 4150
F 0 "C38" H 7865 4196 50  0000 L CNN
F 1 "1u" H 7865 4105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7788 4000 50  0001 C CNN
F 3 "~" H 7750 4150 50  0001 C CNN
	1    7750 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR096
U 1 1 5FEB2A32
P 7750 4350
F 0 "#PWR096" H 7750 4100 50  0001 C CNN
F 1 "GND" H 7755 4177 50  0000 C CNN
F 2 "" H 7750 4350 50  0001 C CNN
F 3 "" H 7750 4350 50  0001 C CNN
	1    7750 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 4000 7500 4000
Wire Wire Line
	7750 4000 8350 4000
Connection ~ 7750 4000
Wire Wire Line
	7500 4000 7500 4600
Wire Wire Line
	7500 4600 8350 4600
Wire Wire Line
	8350 4600 8350 4200
Connection ~ 7500 4000
Wire Wire Line
	7500 4000 7750 4000
Wire Wire Line
	7750 4300 7750 4350
Wire Wire Line
	7750 4300 8150 4300
Wire Wire Line
	8150 4300 8150 4100
Wire Wire Line
	8150 4100 8350 4100
Connection ~ 7750 4300
$Comp
L Device:C C40
U 1 1 5FEBB827
P 9600 4250
F 0 "C40" H 9715 4296 50  0000 L CNN
F 1 "1u" H 9715 4205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9638 4100 50  0001 C CNN
F 3 "~" H 9600 4250 50  0001 C CNN
	1    9600 4250
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3VA #PWR?
U 1 1 5FEBC275
P 9850 4100
AR Path="/5FEBC275" Ref="#PWR?"  Part="1" 
AR Path="/5FDE753F/5FEBC275" Ref="#PWR0100"  Part="1" 
F 0 "#PWR0100" H 9850 3950 50  0001 C CNN
F 1 "+3.3VA" V 9865 4228 50  0000 L CNN
F 2 "" H 9850 4100 50  0001 C CNN
F 3 "" H 9850 4100 50  0001 C CNN
	1    9850 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	9450 4100 9600 4100
Connection ~ 9600 4100
Wire Wire Line
	9600 4100 9850 4100
$Comp
L power:GND #PWR099
U 1 1 5FEBEC47
P 9600 4400
F 0 "#PWR099" H 9600 4150 50  0001 C CNN
F 1 "GND" H 9605 4227 50  0000 C CNN
F 2 "" H 9600 4400 50  0001 C CNN
F 3 "" H 9600 4400 50  0001 C CNN
	1    9600 4400
	1    0    0    -1  
$EndComp
Text GLabel 9700 1550 2    50   Input ~ 0
ref_-10v
Wire Wire Line
	2350 1700 2750 1700
Connection ~ 2350 1700
Wire Wire Line
	2350 2100 2750 2100
Connection ~ 2350 2100
$Comp
L power:VCC #PWR0119
U 1 1 5FF4123A
P 4050 2350
F 0 "#PWR0119" H 4050 2200 50  0001 C CNN
F 1 "VCC" V 4068 2477 50  0000 L CNN
F 2 "" H 4050 2350 50  0001 C CNN
F 3 "" H 4050 2350 50  0001 C CNN
	1    4050 2350
	-1   0    0    1   
$EndComp
Connection ~ 1950 4050
Wire Wire Line
	1600 4050 1950 4050
Wire Wire Line
	1950 4050 2150 4050
$Comp
L Device:C C30
U 1 1 5FDFF043
P 1950 4200
F 0 "C30" H 2065 4246 50  0000 L CNN
F 1 "10u" H 2065 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1988 4050 50  0001 C CNN
F 3 "~" H 1950 4200 50  0001 C CNN
	1    1950 4200
	1    0    0    -1  
$EndComp
$EndSCHEMATC