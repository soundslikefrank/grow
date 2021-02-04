EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 11
Title "frank.counts"
Date "2020-05-04"
Rev "2"
Comp "tbd"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 3750 4350 0    50   Input ~ 0
fader_a
Text GLabel 3750 4450 0    50   Input ~ 0
fader_b
Text GLabel 3750 4550 0    50   Input ~ 0
fader_c
Text GLabel 3750 4650 0    50   Input ~ 0
fader_d
Text GLabel 5050 2650 2    50   Input ~ 0
fader_e
Text GLabel 5050 2750 2    50   Input ~ 0
fader_f
Text GLabel 5050 2850 2    50   Input ~ 0
fader_g
Text GLabel 5050 2950 2    50   Input ~ 0
fader_h
Text GLabel 3750 4950 0    50   Input ~ 0
fader_a_led
Text GLabel 3750 5050 0    50   Input ~ 0
fader_b_led
Text GLabel 3750 5150 0    50   Input ~ 0
fader_c_led
Text GLabel 3750 5250 0    50   Input ~ 0
fader_d_led
Text GLabel 3750 5350 0    50   Input ~ 0
fader_e_led
Text GLabel 3750 5450 0    50   Input ~ 0
fader_f_led
Text GLabel 3750 5550 0    50   Input ~ 0
fader_g_led
Text GLabel 3750 5650 0    50   Input ~ 0
fader_h_led
$Comp
L MCU_ST_STM32L4:STM32L452RETx U1
U 1 1 5FDEF22A
P 4450 4250
F 0 "U1" H 4800 2450 50  0000 C CNN
F 1 "STM32L452RETx" H 5050 2350 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 3850 2550 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00340549.pdf" H 4450 4250 50  0001 C CNN
	1    4450 4250
	1    0    0    -1  
$EndComp
Text GLabel 5050 5550 2    50   Input ~ 0
dac_cs
Text GLabel 5050 5650 2    50   Input ~ 0
dac_clk
Text GLabel 5050 5850 2    50   Input ~ 0
dac_mosi
Text GLabel 5050 4350 2    50   Input ~ 0
led_sin
Text GLabel 5050 4450 2    50   Input ~ 0
led_lat
Text GLabel 5050 5350 2    50   Input ~ 0
led_clk
Text GLabel 5050 5750 2    50   Input ~ 0
led_gsclk
Text GLabel 5050 4050 2    50   Input ~ 0
jtag_clk
Text GLabel 5050 4650 2    50   Input ~ 0
jtag_tdo
Text GLabel 3750 3750 0    50   Input ~ 0
hse_in
Text GLabel 3750 3850 0    50   Input ~ 0
hse_out
Text GLabel 5050 3250 2    50   Input ~ 0
cv_in_a
Text GLabel 5050 3350 2    50   Input ~ 0
cv_in_b
Text GLabel 5050 3550 2    50   Input ~ 0
usart_tx
Text GLabel 5050 3650 2    50   Input ~ 0
usart_rx
Text GLabel 5050 4550 2    50   Input ~ 0
trigger_in
Text GLabel 5050 3750 2    50   Input ~ 0
trigger_out_a
Text GLabel 5050 3850 2    50   Input ~ 0
trigger_out_b
Text GLabel 5050 5450 2    50   Input ~ 0
jack_detect
Text GLabel 5050 4850 2    50   Input ~ 0
encoder_a
Text GLabel 5050 4950 2    50   Input ~ 0
encoder_b
Text GLabel 5050 5050 2    50   Input ~ 0
encoder_sw
Text GLabel 5050 3050 2    50   Input ~ 0
pot_a
Text GLabel 5050 3150 2    50   Input ~ 0
pot_b
$Comp
L power:+3V3 #PWR?
U 1 1 5FE09053
P 4150 2450
AR Path="/5FDE753F/5FE09053" Ref="#PWR?"  Part="1" 
AR Path="/5FE09053" Ref="#PWR08"  Part="1" 
F 0 "#PWR08" H 4150 2300 50  0001 C CNN
F 1 "+3V3" V 4165 2578 50  0000 L CNN
F 2 "" H 4150 2450 50  0001 C CNN
F 3 "" H 4150 2450 50  0001 C CNN
	1    4150 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 2450 4250 2450
Connection ~ 4150 2450
Connection ~ 4250 2450
Wire Wire Line
	4250 2450 4350 2450
Connection ~ 4350 2450
Wire Wire Line
	4350 2450 4450 2450
NoConn ~ 4650 2450
$Comp
L power:+3.3VA #PWR010
U 1 1 5FE0A2DA
P 4550 2450
F 0 "#PWR010" H 4550 2300 50  0001 C CNN
F 1 "+3.3VA" H 4565 2623 50  0000 C CNN
F 2 "" H 4550 2450 50  0001 C CNN
F 3 "" H 4550 2450 50  0001 C CNN
	1    4550 2450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5FE0D43A
P 4150 6050
F 0 "#PWR09" H 4150 5800 50  0001 C CNN
F 1 "GND" H 4155 5877 50  0000 C CNN
F 2 "" H 4150 6050 50  0001 C CNN
F 3 "" H 4150 6050 50  0001 C CNN
	1    4150 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 6050 4250 6050
Connection ~ 4150 6050
Connection ~ 4250 6050
Wire Wire Line
	4250 6050 4350 6050
Connection ~ 4350 6050
Wire Wire Line
	4350 6050 4450 6050
Connection ~ 4450 6050
Wire Wire Line
	4450 6050 4550 6050
$Comp
L Device:C C1
U 1 1 5FE0F027
P 1050 1350
F 0 "C1" H 1165 1396 50  0000 L CNN
F 1 "4u7" H 1165 1305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1088 1200 50  0001 C CNN
F 3 "~" H 1050 1350 50  0001 C CNN
F 4 "C19666" H 1050 1350 50  0001 C CNN "LCSC Part #"
F 5 "C19666" H 1050 1350 50  0001 C CNN "LCSC"
	1    1050 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5FE10C2E
P 1450 1350
F 0 "C3" H 1565 1396 50  0000 L CNN
F 1 "100n" H 1565 1305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1488 1200 50  0001 C CNN
F 3 "~" H 1450 1350 50  0001 C CNN
F 4 "C14663" H 1450 1350 50  0001 C CNN "LCSC Part #"
F 5 "C14663" H 1450 1350 50  0001 C CNN "LCSC"
	1    1450 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5FE10F5D
P 1850 1350
F 0 "C5" H 1965 1396 50  0000 L CNN
F 1 "100n" H 1965 1305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1888 1200 50  0001 C CNN
F 3 "~" H 1850 1350 50  0001 C CNN
F 4 "C14663" H 1850 1350 50  0001 C CNN "LCSC Part #"
F 5 "C14663" H 1850 1350 50  0001 C CNN "LCSC"
	1    1850 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5FE11357
P 2250 1350
F 0 "C6" H 2365 1396 50  0000 L CNN
F 1 "100n" H 2365 1305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2288 1200 50  0001 C CNN
F 3 "~" H 2250 1350 50  0001 C CNN
F 4 "C14663" H 2250 1350 50  0001 C CNN "LCSC Part #"
F 5 "C14663" H 2250 1350 50  0001 C CNN "LCSC"
	1    2250 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 5FE11893
P 2650 1350
F 0 "C7" H 2765 1396 50  0000 L CNN
F 1 "100n" H 2765 1305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2688 1200 50  0001 C CNN
F 3 "~" H 2650 1350 50  0001 C CNN
F 4 "C14663" H 2650 1350 50  0001 C CNN "LCSC Part #"
F 5 "C14663" H 2650 1350 50  0001 C CNN "LCSC"
	1    2650 1350
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5FE11C48
P 1050 1200
AR Path="/5FDE753F/5FE11C48" Ref="#PWR?"  Part="1" 
AR Path="/5FE11C48" Ref="#PWR01"  Part="1" 
F 0 "#PWR01" H 1050 1050 50  0001 C CNN
F 1 "+3V3" V 1065 1328 50  0000 L CNN
F 2 "" H 1050 1200 50  0001 C CNN
F 3 "" H 1050 1200 50  0001 C CNN
	1    1050 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5FE1224A
P 1050 1500
F 0 "#PWR02" H 1050 1250 50  0001 C CNN
F 1 "GND" H 1055 1327 50  0000 C CNN
F 2 "" H 1050 1500 50  0001 C CNN
F 3 "" H 1050 1500 50  0001 C CNN
	1    1050 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 1200 1450 1200
Connection ~ 1050 1200
Connection ~ 1450 1200
Wire Wire Line
	1450 1200 1850 1200
Connection ~ 1850 1200
Wire Wire Line
	1850 1200 2250 1200
Connection ~ 2250 1200
Wire Wire Line
	2250 1200 2650 1200
Wire Wire Line
	1050 1500 1450 1500
Connection ~ 1050 1500
Connection ~ 1450 1500
Wire Wire Line
	1450 1500 1850 1500
Connection ~ 1850 1500
Wire Wire Line
	1850 1500 2250 1500
Connection ~ 2250 1500
Wire Wire Line
	2250 1500 2650 1500
Text Notes 850  750  0    50   ~ 0
Bypass caps
$Comp
L Device:C C9
U 1 1 5FEDDFA9
P 4000 1350
F 0 "C9" H 4115 1396 50  0000 L CNN
F 1 "100n" H 4115 1305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4038 1200 50  0001 C CNN
F 3 "~" H 4000 1350 50  0001 C CNN
F 4 "C14663" H 4000 1350 50  0001 C CNN "LCSC Part #"
F 5 "C14663" H 4000 1350 50  0001 C CNN "LCSC"
	1    4000 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 5FEDE17B
P 3600 1350
F 0 "C8" H 3715 1396 50  0000 L CNN
F 1 "1u" H 3715 1305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3638 1200 50  0001 C CNN
F 3 "~" H 3600 1350 50  0001 C CNN
F 4 "C15849" H 3600 1350 50  0001 C CNN "LCSC Part #"
F 5 "C15849" H 3600 1350 50  0001 C CNN "LCSC"
	1    3600 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 1200 4000 1200
Wire Wire Line
	3600 1500 4000 1500
$Comp
L power:GND #PWR07
U 1 1 5FEE0737
P 3600 1500
F 0 "#PWR07" H 3600 1250 50  0001 C CNN
F 1 "GND" H 3605 1327 50  0000 C CNN
F 2 "" H 3600 1500 50  0001 C CNN
F 3 "" H 3600 1500 50  0001 C CNN
	1    3600 1500
	1    0    0    -1  
$EndComp
Connection ~ 3600 1500
$Comp
L power:+3.3VA #PWR06
U 1 1 5FEE0C27
P 3600 1200
F 0 "#PWR06" H 3600 1050 50  0001 C CNN
F 1 "+3.3VA" H 3615 1373 50  0000 C CNN
F 2 "" H 3600 1200 50  0001 C CNN
F 3 "" H 3600 1200 50  0001 C CNN
	1    3600 1200
	1    0    0    -1  
$EndComp
Connection ~ 3600 1200
Wire Notes Line
	850  800  850  1800
Wire Notes Line
	850  1800 4400 1800
Wire Notes Line
	4400 1800 4400 800 
Wire Notes Line
	4400 800  850  800 
$Comp
L Device:Crystal Y1
U 1 1 5FEE5D61
P 1400 3150
F 0 "Y1" H 1400 3350 50  0000 C CNN
F 1 "ABM3-8.000MHZ" H 1400 2973 50  0000 C CNN
F 2 "Crystal:Crystal_SMD_Abracon_ABM3-2Pin_5.0x3.2mm_HandSoldering" H 1400 3150 50  0001 C CNN
F 3 "~" H 1400 3150 50  0001 C CNN
	1    1400 3150
	-1   0    0    1   
$EndComp
$Comp
L Device:C C2
U 1 1 5FEE6FDE
P 1050 2800
F 0 "C2" H 1165 2846 50  0000 L CNN
F 1 "22-26p" H 1165 2755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1088 2650 50  0001 C CNN
F 3 "~" H 1050 2800 50  0001 C CNN
F 4 "C388039" H 1050 2800 50  0001 C CNN "LCSC Part #"
F 5 "C388039" H 1050 2800 50  0001 C CNN "LCSC"
	1    1050 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5FEE75BB
P 1750 2800
F 0 "C4" H 1865 2846 50  0000 L CNN
F 1 "22-26p" H 1865 2755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1788 2650 50  0001 C CNN
F 3 "~" H 1750 2800 50  0001 C CNN
F 4 "C388039" H 1750 2800 50  0001 C CNN "LCSC Part #"
F 5 "C388039" H 1750 2800 50  0001 C CNN "LCSC"
	1    1750 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 2950 1050 3150
Wire Wire Line
	1050 3150 1250 3150
Wire Wire Line
	1550 3150 1750 3150
Wire Wire Line
	1750 3150 1750 2950
$Comp
L power:GND #PWR03
U 1 1 5FEEBE5C
P 1400 2550
F 0 "#PWR03" H 1400 2300 50  0001 C CNN
F 1 "GND" H 1405 2377 50  0000 C CNN
F 2 "" H 1400 2550 50  0001 C CNN
F 3 "" H 1400 2550 50  0001 C CNN
	1    1400 2550
	-1   0    0    1   
$EndComp
Wire Wire Line
	1050 2650 1400 2650
Wire Wire Line
	1400 2550 1400 2650
Connection ~ 1400 2650
Wire Wire Line
	1400 2650 1750 2650
$Comp
L Device:R R1
U 1 1 5FEEED16
P 1750 3350
F 0 "R1" H 1820 3396 50  0000 L CNN
F 1 "750R" H 1820 3305 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1680 3350 50  0001 C CNN
F 3 "~" H 1750 3350 50  0001 C CNN
F 4 "C23241" H 1750 3350 50  0001 C CNN "LCSC Part #"
F 5 "C23241" H 1750 3350 50  0001 C CNN "LCSC"
	1    1750 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 3150 1750 3200
Connection ~ 1750 3150
Text GLabel 1750 3600 3    50   Input ~ 0
hse_out
Text GLabel 1050 3650 3    50   Input ~ 0
hse_in
Wire Wire Line
	1050 3650 1050 3150
Connection ~ 1050 3150
Wire Wire Line
	1750 3500 1750 3600
Wire Notes Line
	850  2250 850  4050
Wire Notes Line
	2250 4050 2250 2250
Text Notes 850  2200 0    50   ~ 0
Crystal oscillator
Text GLabel 7200 1050 0    50   Input ~ 0
trigger_in
Text GLabel 7450 3050 0    50   Input ~ 0
trigger_out_b
Text GLabel 7450 2850 0    50   Input ~ 0
trigger_out_a
$Sheet
S 7450 2700 900  500 
U 5FDBBE2F
F0 "Trigger Output" 50
F1 "trigger_output.sch" 50
F2 "trigger_out_a" I L 7450 2850 50 
F3 "trigger_out_b" I L 7450 3050 50 
$EndSheet
Text GLabel 7300 4450 0    50   Input ~ 0
led_gsclk
Text GLabel 7300 4150 0    50   Input ~ 0
led_clk
Text GLabel 7300 4300 0    50   Input ~ 0
led_lat
Text GLabel 7300 4000 0    50   Input ~ 0
led_sin
$Sheet
S 7300 3850 800  750 
U 5FDF6408
F0 "Step LEDs" 50
F1 "step_leds.sch" 50
F2 "led_sin" I L 7300 4000 50 
F3 "led_clk" I L 7300 4150 50 
F4 "led_lat" I L 7300 4300 50 
F5 "led_gsclk" I L 7300 4450 50 
$EndSheet
Text GLabel 7150 2150 0    50   Input ~ 0
dac_mosi
Text GLabel 7150 2000 0    50   Input ~ 0
dac_clk
Text GLabel 7150 1850 0    50   Input ~ 0
dac_cs
$Sheet
S 7150 1700 550  600 
U 5ED37B53
F0 "DAC" 50
F1 "dac.sch" 50
F2 "dac_clk" I L 7150 2000 50 
F3 "dac_cs" I L 7150 1850 50 
F4 "dac_mosi" I L 7150 2150 50 
$EndSheet
$Sheet
S 7200 950  850  400 
U 5ED4085B
F0 "Trigger Input" 50
F1 "trigger_input.sch" 50
F2 "trigger_in" O L 7200 1050 50 
F3 "jack_detect" I L 7200 1250 50 
$EndSheet
$Sheet
S 9500 3150 950  1750
U 5FD4CB96
F0 "Faders & Pots" 50
F1 "faders_pots.sch" 50
F2 "fader_a" O L 9500 3350 50 
F3 "fader_a_led" I R 10450 3350 50 
F4 "fader_b" O L 9500 3500 50 
F5 "fader_b_led" I R 10450 3500 50 
F6 "fader_c" O L 9500 3650 50 
F7 "fader_c_led" I R 10450 3650 50 
F8 "fader_d" O L 9500 3800 50 
F9 "fader_d_led" I R 10450 3800 50 
F10 "fader_e" O L 9500 3950 50 
F11 "fader_e_led" I R 10450 3950 50 
F12 "fader_f" O L 9500 4100 50 
F13 "fader_f_led" I R 10450 4100 50 
F14 "fader_g" O L 9500 4250 50 
F15 "fader_g_led" I R 10450 4250 50 
F16 "fader_h" O L 9500 4400 50 
F17 "fader_h_led" I R 10450 4400 50 
F18 "pot_a" O L 9500 4550 50 
F19 "pot_b" O L 9500 4700 50 
$EndSheet
Text GLabel 9500 3350 0    50   Input ~ 0
fader_a
Text GLabel 9500 3500 0    50   Input ~ 0
fader_b
Text GLabel 9500 3650 0    50   Input ~ 0
fader_c
Text GLabel 9500 3800 0    50   Input ~ 0
fader_d
Text GLabel 9500 3950 0    50   Input ~ 0
fader_e
Text GLabel 9500 4100 0    50   Input ~ 0
fader_f
Text GLabel 9500 4250 0    50   Input ~ 0
fader_g
Text GLabel 9500 4400 0    50   Input ~ 0
fader_h
Text GLabel 10450 3350 2    50   Input ~ 0
fader_a_led
Text GLabel 10450 3500 2    50   Input ~ 0
fader_b_led
Text GLabel 10450 3650 2    50   Input ~ 0
fader_c_led
Text GLabel 10450 3800 2    50   Input ~ 0
fader_d_led
Text GLabel 10450 3950 2    50   Input ~ 0
fader_e_led
Text GLabel 10450 4100 2    50   Input ~ 0
fader_f_led
Text GLabel 10450 4250 2    50   Input ~ 0
fader_g_led
Text GLabel 10450 4400 2    50   Input ~ 0
fader_h_led
Text GLabel 9500 4550 0    50   Input ~ 0
pot_a
Text GLabel 9500 4700 0    50   Input ~ 0
pot_b
$Sheet
S 9500 750  950  450 
U 5FDE753F
F0 "Power & Vref" 50
F1 "power_ref.sch" 50
$EndSheet
Text Notes 9500 1400 0    50   ~ 0
v_ee, v_cc, 5v, 3v3, 3.3va, ref_-10v
Text GLabel 9500 5950 0    50   Input ~ 0
encoder_sw
Text GLabel 9500 5800 0    50   Input ~ 0
encoder_b
Text GLabel 9500 5650 0    50   Input ~ 0
encoder_a
$Sheet
S 9500 5500 950  600 
U 5FDF0A57
F0 "Encoder" 50
F1 "encoder.sch" 50
F2 "encoder_b" O L 9500 5800 50 
F3 "encoder_a" O L 9500 5650 50 
F4 "encoder_sw" O L 9500 5950 50 
$EndSheet
Text GLabel 7200 1250 0    50   Input ~ 0
jack_detect
Text GLabel 9500 2400 0    50   Input ~ 0
jack_detect
Text GLabel 9500 2200 0    50   Input ~ 0
cv_in_b
Text GLabel 9500 2000 0    50   Input ~ 0
cv_in_a
$Sheet
S 9500 1850 950  700 
U 5FCA3E21
F0 "CV Input" 50
F1 "cv_input.sch" 50
F2 "cv_in_a" O L 9500 2000 50 
F3 "cv_in_b" O L 9500 2200 50 
F4 "jack_detect" I L 9500 2400 50 
$EndSheet
Text GLabel 7300 5200 0    50   Input ~ 0
jtag_tms
Text GLabel 7300 5350 0    50   Input ~ 0
jtag_clk
Text GLabel 7300 5650 0    50   Input ~ 0
jtag_tdi
Text GLabel 7300 5500 0    50   Input ~ 0
jtag_tdo
Text GLabel 7300 5800 0    50   Input ~ 0
jtag_reset
Text GLabel 5050 3950 2    50   Input ~ 0
jtag_tms
$Sheet
S 7300 5050 850  1300
U 5FEE41D4
F0 "JTAG & Debug Connectors" 50
F1 "debug.sch" 50
F2 "jtag_clk" O L 7300 5350 50 
F3 "jtag_tms" O L 7300 5200 50 
F4 "jtag_tdo" O L 7300 5500 50 
F5 "jtag_tdi" O L 7300 5650 50 
F6 "jtag_reset" O L 7300 5800 50 
F7 "usart_tx" O L 7300 5950 50 
F8 "usart_rx" O L 7300 6100 50 
F9 "debug_trst" O L 7300 6250 50 
$EndSheet
Text GLabel 3750 2650 0    50   Input ~ 0
jtag_reset
Text GLabel 7300 5950 0    50   Input ~ 0
usart_tx
Text GLabel 7300 6100 0    50   Input ~ 0
usart_rx
Text GLabel 5050 4750 2    50   Input ~ 0
debug_trst
Text GLabel 7300 6250 0    50   Input ~ 0
debug_trst
NoConn ~ 3750 4150
NoConn ~ 3750 4750
NoConn ~ 3750 4850
NoConn ~ 3750 5750
NoConn ~ 3750 5850
NoConn ~ 5050 5250
NoConn ~ 5050 5150
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5FF24863
P 1450 7100
F 0 "H1" H 1550 7149 50  0000 L CNN
F 1 "MountingHole_Pad" H 1550 7058 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 1450 7100 50  0001 C CNN
F 3 "~" H 1450 7100 50  0001 C CNN
	1    1450 7100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 5FF250F3
P 2600 7100
F 0 "H2" H 2700 7149 50  0000 L CNN
F 1 "MountingHole_Pad" H 2700 7058 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 2600 7100 50  0001 C CNN
F 3 "~" H 2600 7100 50  0001 C CNN
	1    2600 7100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5FF255F2
P 1450 7200
F 0 "#PWR04" H 1450 6950 50  0001 C CNN
F 1 "GND" H 1455 7027 50  0000 C CNN
F 2 "" H 1450 7200 50  0001 C CNN
F 3 "" H 1450 7200 50  0001 C CNN
	1    1450 7200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5FF25A97
P 2600 7200
F 0 "#PWR05" H 2600 6950 50  0001 C CNN
F 1 "GND" H 2605 7027 50  0000 C CNN
F 2 "" H 2600 7200 50  0001 C CNN
F 3 "" H 2600 7200 50  0001 C CNN
	1    2600 7200
	1    0    0    -1  
$EndComp
NoConn ~ 5050 3450
$Comp
L Diode:BAT54S D1
U 1 1 5FE6281C
P 5700 6950
F 0 "D1" V 5746 7038 50  0000 L CNN
F 1 "BAT54S" V 5655 7038 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5775 7075 50  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds11005.pdf" H 5580 6950 50  0001 C CNN
	1    5700 6950
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5FE64126
P 5700 6650
AR Path="/5FDE753F/5FE64126" Ref="#PWR?"  Part="1" 
AR Path="/5FE64126" Ref="#PWR011"  Part="1" 
F 0 "#PWR011" H 5700 6500 50  0001 C CNN
F 1 "+3V3" V 5715 6778 50  0000 L CNN
F 2 "" H 5700 6650 50  0001 C CNN
F 3 "" H 5700 6650 50  0001 C CNN
	1    5700 6650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5FE64C03
P 5700 7250
F 0 "#PWR012" H 5700 7000 50  0001 C CNN
F 1 "GND" H 5705 7077 50  0000 C CNN
F 2 "" H 5700 7250 50  0001 C CNN
F 3 "" H 5700 7250 50  0001 C CNN
	1    5700 7250
	1    0    0    -1  
$EndComp
Text GLabel 5900 6950 2    50   Input ~ 0
jack_detect
Wire Notes Line
	850  2250 2250 2250
Wire Notes Line
	2250 4050 850  4050
Text GLabel 5050 4150 2    50   Input ~ 0
jtag_tdi
$Comp
L Device:R R39
U 1 1 5FEA3E52
P 3150 3700
F 0 "R39" H 3220 3746 50  0000 L CNN
F 1 "10k" H 3220 3655 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3080 3700 50  0001 C CNN
F 3 "~" H 3150 3700 50  0001 C CNN
F 4 "C25804" H 3150 3700 50  0001 C CNN "LCSC Part #"
F 5 "C25804" H 3150 3700 50  0001 C CNN "LCSC"
	1    3150 3700
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0124
U 1 1 5FEA54EC
P 3150 3550
F 0 "#PWR0124" H 3150 3300 50  0001 C CNN
F 1 "GND" H 3155 3377 50  0000 C CNN
F 2 "" H 3150 3550 50  0001 C CNN
F 3 "" H 3150 3550 50  0001 C CNN
	1    3150 3550
	-1   0    0    1   
$EndComp
Wire Wire Line
	3150 3850 3150 3950
Wire Wire Line
	3150 3950 3750 3950
Text Notes 2850 3300 0    50   ~ 0
BOOT0 needs to\nbe tied to GND
$EndSCHEMATC
