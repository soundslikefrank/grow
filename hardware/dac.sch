EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
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
L Analog_DAC:MCP4822 U?
U 1 1 5ED37FE9
P 5600 3200
F 0 "U?" H 5850 3700 50  0000 C CNN
F 1 "MCP4822" H 5850 3600 50  0000 C CNN
F 2 "" H 6400 2900 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20002249B.pdf" H 6400 2900 50  0001 C CNN
	1    5600 3200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5ED397CF
P 5600 2550
F 0 "#PWR?" H 5600 2400 50  0001 C CNN
F 1 "+5V" H 5615 2723 50  0000 C CNN
F 2 "" H 5600 2550 50  0001 C CNN
F 3 "" H 5600 2550 50  0001 C CNN
	1    5600 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 2550 5600 2800
$Comp
L power:GND #PWR?
U 1 1 5ED3A5A6
P 5600 4000
F 0 "#PWR?" H 5600 3750 50  0001 C CNN
F 1 "GND" H 5605 3827 50  0000 C CNN
F 2 "" H 5600 4000 50  0001 C CNN
F 3 "" H 5600 4000 50  0001 C CNN
	1    5600 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 3700 5600 4000
$Comp
L power:GND #PWR?
U 1 1 5ED3A9D0
P 4600 3200
F 0 "#PWR?" H 4600 2950 50  0001 C CNN
F 1 "GND" V 4605 3072 50  0000 R CNN
F 2 "" H 4600 3200 50  0001 C CNN
F 3 "" H 4600 3200 50  0001 C CNN
	1    4600 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	5100 3200 4600 3200
NoConn ~ 6100 3400
Text HLabel 4000 3100 0    50   Input ~ 0
SCK
Wire Wire Line
	4000 3100 5100 3100
Text HLabel 4000 3300 0    50   Input ~ 0
MOSI
Wire Wire Line
	4000 3300 5100 3300
Text HLabel 4550 3400 0    50   Input ~ 0
CS
Wire Wire Line
	4550 3400 5100 3400
$EndSCHEMATC
