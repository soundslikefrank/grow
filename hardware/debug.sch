EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 11 11
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
L Connector_Generic:Conn_02x05_Odd_Even J11
U 1 1 5FE5287B
P 5500 2900
F 0 "J11" H 5550 3317 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 5550 3226 50  0000 C CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_2x05_P1.27mm_Vertical" H 5500 2900 50  0001 C CNN
F 3 "~" H 5500 2900 50  0001 C CNN
	1    5500 2900
	1    0    0    -1  
$EndComp
Text HLabel 5800 2800 2    50   Output ~ 0
jtag_clk
Text HLabel 5800 2700 2    50   Output ~ 0
jtag_tms
Text HLabel 5800 2900 2    50   Output ~ 0
jtag_tdo
Text HLabel 5800 3000 2    50   Output ~ 0
jtag_tdi
Text HLabel 5800 3100 2    50   Output ~ 0
jtag_reset
$Comp
L power:+3V3 #PWR?
U 1 1 5FE5C21A
P 5300 2700
AR Path="/5FDE753F/5FE5C21A" Ref="#PWR?"  Part="1" 
AR Path="/5FE5C21A" Ref="#PWR?"  Part="1" 
AR Path="/5FEE41D4/5FE5C21A" Ref="#PWR0116"  Part="1" 
F 0 "#PWR0116" H 5300 2550 50  0001 C CNN
F 1 "+3V3" V 5315 2828 50  0000 L CNN
F 2 "" H 5300 2700 50  0001 C CNN
F 3 "" H 5300 2700 50  0001 C CNN
	1    5300 2700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FE5CC83
P 5150 3100
AR Path="/5FE5CC83" Ref="#PWR?"  Part="1" 
AR Path="/5FEE41D4/5FE5CC83" Ref="#PWR0115"  Part="1" 
F 0 "#PWR0115" H 5150 2850 50  0001 C CNN
F 1 "GND" H 5155 2927 50  0000 C CNN
F 2 "" H 5150 3100 50  0001 C CNN
F 3 "" H 5150 3100 50  0001 C CNN
	1    5150 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	5300 3100 5200 3100
Wire Wire Line
	5300 2900 5200 2900
Wire Wire Line
	5200 2900 5200 3100
Connection ~ 5200 3100
Wire Wire Line
	5200 3100 5150 3100
NoConn ~ 5300 3000
Wire Wire Line
	5200 2900 5200 2800
Wire Wire Line
	5200 2800 5300 2800
Connection ~ 5200 2900
$Comp
L power:GND #PWR?
U 1 1 5FE69569
P 4950 3850
AR Path="/5FE69569" Ref="#PWR?"  Part="1" 
AR Path="/5FEE41D4/5FE69569" Ref="#PWR0114"  Part="1" 
F 0 "#PWR0114" H 4950 3600 50  0001 C CNN
F 1 "GND" H 4955 3677 50  0000 C CNN
F 2 "" H 4950 3850 50  0001 C CNN
F 3 "" H 4950 3850 50  0001 C CNN
	1    4950 3850
	0    1    1    0   
$EndComp
Text HLabel 5300 3650 0    50   Output ~ 0
usart_tx
Text HLabel 5300 3750 0    50   Output ~ 0
usart_rx
Text HLabel 5300 4300 0    50   Output ~ 0
debug_trst
$Comp
L Connector_Generic:Conn_01x03 J12
U 1 1 5FE72FDC
P 5500 3750
F 0 "J12" H 5580 3792 50  0000 L CNN
F 1 "Conn_01x03" H 5580 3701 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 5500 3750 50  0001 C CNN
F 3 "~" H 5500 3750 50  0001 C CNN
	1    5500 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 3850 5300 3850
$Comp
L Connector_Generic:Conn_01x01 J13
U 1 1 5FE748C4
P 5500 4300
F 0 "J13" H 5580 4342 50  0000 L CNN
F 1 "Conn_01x01" H 5580 4251 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 5500 4300 50  0001 C CNN
F 3 "~" H 5500 4300 50  0001 C CNN
	1    5500 4300
	1    0    0    -1  
$EndComp
$EndSCHEMATC
