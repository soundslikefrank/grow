EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 9
Title "frank.counts"
Date "2020-05-04"
Rev "2"
Comp "tbd"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 9050 1350 1100 650 
U 5ED4085B
F0 "Trigger Input" 50
F1 "trigger_input.sch" 50
F2 "trigger_in" O L 9050 1450 50 
F3 "jack_detect" I L 9050 1650 50 
$EndSheet
$Sheet
S 7900 2250 550  600 
U 5ED37B53
F0 "DAC" 50
F1 "dac.sch" 50
F2 "dac_clk" I L 7900 2550 50 
F3 "dac_cs" I L 7900 2400 50 
F4 "dac_mosi" I L 7900 2700 50 
$EndSheet
$Sheet
S 1700 2950 1050 800 
U 5FCA3E21
F0 "CV Input" 50
F1 "cv_input.sch" 50
F2 "cv_in_a" O L 1700 3150 50 
F3 "cv_in_b" O L 1700 3350 50 
F4 "jack_detect" I L 1700 3550 50 
$EndSheet
$Sheet
S 1850 1400 900  450 
U 5FCB1CD7
F0 "Power" 50
F1 "power.sch" 50
$EndSheet
$Sheet
S 1650 5050 950  1500
U 5FD4CB96
F0 "Faders" 50
F1 "faders.sch" 50
F2 "fader_a" O L 1650 5250 50 
F3 "fader_a_led" I R 2600 5250 50 
F4 "fader_b" O L 1650 5400 50 
F5 "fader_b_led" I R 2600 5400 50 
F6 "fader_c" O L 1650 5550 50 
F7 "fader_c_led" I R 2600 5550 50 
F8 "fader_d" O L 1650 5700 50 
F9 "fader_d_led" I R 2600 5700 50 
F10 "fader_e" O L 1650 5850 50 
F11 "fader_e_led" I R 2600 5850 50 
F12 "fader_f" O L 1650 6000 50 
F13 "fader_f_led" I R 2600 6000 50 
F14 "fader_g" O L 1650 6150 50 
F15 "fader_g_led" I R 2600 6150 50 
F16 "fader_h" O L 1650 6300 50 
F17 "fader_h_led" I R 2600 6300 50 
$EndSheet
Text GLabel 1650 5250 0    50   Input ~ 0
fader_a
Text GLabel 4750 3700 0    50   Input ~ 0
fader_a
Text GLabel 1650 5400 0    50   Input ~ 0
fader_b
Text GLabel 1650 5550 0    50   Input ~ 0
fader_c
Text GLabel 1650 5700 0    50   Input ~ 0
fader_d
Text GLabel 1650 5850 0    50   Input ~ 0
fader_e
Text GLabel 1650 6000 0    50   Input ~ 0
fader_f
Text GLabel 1650 6150 0    50   Input ~ 0
fader_g
Text GLabel 1650 6300 0    50   Input ~ 0
fader_h
Text GLabel 4750 3800 0    50   Input ~ 0
fader_b
Text GLabel 4750 3900 0    50   Input ~ 0
fader_c
Text GLabel 4750 4000 0    50   Input ~ 0
fader_d
Text GLabel 6050 2000 2    50   Input ~ 0
fader_e
Text GLabel 6050 2100 2    50   Input ~ 0
fader_f
Text GLabel 6050 2200 2    50   Input ~ 0
fader_g
Text GLabel 6050 2300 2    50   Input ~ 0
fader_h
Text GLabel 2600 5250 2    50   Input ~ 0
fader_a_led
Text GLabel 2600 5400 2    50   Input ~ 0
fader_b_led
Text GLabel 2600 5550 2    50   Input ~ 0
fader_c_led
Text GLabel 2600 5700 2    50   Input ~ 0
fader_d_led
Text GLabel 2600 5850 2    50   Input ~ 0
fader_e_led
Text GLabel 2600 6000 2    50   Input ~ 0
fader_f_led
Text GLabel 2600 6150 2    50   Input ~ 0
fader_g_led
Text GLabel 2600 6300 2    50   Input ~ 0
fader_h_led
Text GLabel 4750 4300 0    50   Input ~ 0
fader_a_led
Text GLabel 4750 4400 0    50   Input ~ 0
fader_b_led
Text GLabel 4750 4500 0    50   Input ~ 0
fader_c_led
Text GLabel 4750 4600 0    50   Input ~ 0
fader_d_led
Text GLabel 4750 4700 0    50   Input ~ 0
fader_e_led
Text GLabel 4750 4800 0    50   Input ~ 0
fader_f_led
Text GLabel 4750 4900 0    50   Input ~ 0
fader_g_led
Text GLabel 4750 5000 0    50   Input ~ 0
fader_h_led
Text GLabel 7900 2400 0    50   Input ~ 0
dac_cs
Text GLabel 7900 2550 0    50   Input ~ 0
dac_clk
Text GLabel 7900 2700 0    50   Input ~ 0
dac_mosi
$Comp
L MCU_ST_STM32L4:STM32L452RETx U?
U 1 1 5FDEF22A
P 5450 3600
F 0 "U?" H 5400 1711 50  0000 C CNN
F 1 "STM32L452RETx" H 5400 1620 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 4850 1900 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00340549.pdf" H 5450 3600 50  0001 C CNN
	1    5450 3600
	1    0    0    -1  
$EndComp
Text GLabel 6050 4900 2    50   Input ~ 0
dac_cs
Text GLabel 6050 5000 2    50   Input ~ 0
dac_clk
Text GLabel 6050 5200 2    50   Input ~ 0
dac_mosi
$Sheet
S 9150 4250 800  750 
U 5FDF6408
F0 "Step LEDs" 50
F1 "step_leds.sch" 50
F2 "led_sin" I L 9150 4400 50 
F3 "led_clk" I L 9150 4550 50 
F4 "led_lat" I L 9150 4700 50 
F5 "led_gsclk" I L 9150 4850 50 
$EndSheet
Text GLabel 6050 3700 2    50   Input ~ 0
led_sin
Text GLabel 9150 4400 0    50   Input ~ 0
led_sin
Text GLabel 6050 3800 2    50   Input ~ 0
led_lat
Text GLabel 9150 4700 0    50   Input ~ 0
led_lat
Text GLabel 6050 4700 2    50   Input ~ 0
led_clk
Text GLabel 9150 4550 0    50   Input ~ 0
led_clk
Text GLabel 6050 2800 2    50   Input ~ 0
led_gsclk
Text GLabel 9150 4850 0    50   Input ~ 0
led_gsclk
$Sheet
S 9300 3100 950  550 
U 5FDBBE2F
F0 "Trigger Output" 50
F1 "trigger_output.sch" 50
F2 "trigger_out_a" I L 9300 3250 50 
F3 "trigger_out_b" I L 9300 3450 50 
$EndSheet
Text GLabel 6050 3300 2    50   Input ~ 0
jtag_tms
Text GLabel 6050 3400 2    50   Input ~ 0
jtag_clk
Text GLabel 6050 3500 2    50   Input ~ 0
jtag_tdi
Text GLabel 6050 4100 2    50   Input ~ 0
jtag_rst
Text GLabel 6050 4000 2    50   Input ~ 0
jtag_tdo
Text GLabel 4750 2000 0    50   Input ~ 0
jtag_nrst
Text GLabel 4750 3100 0    50   Input ~ 0
osc_in
Text GLabel 4750 3200 0    50   Input ~ 0
osc_out
Text GLabel 6050 2400 2    50   Input ~ 0
cv_in_a
Text GLabel 9300 3250 0    50   Input ~ 0
trigger_out_a
Text GLabel 9300 3450 0    50   Input ~ 0
trigger_out_b
Text GLabel 1700 3150 0    50   Input ~ 0
cv_in_a
Text GLabel 6050 2500 2    50   Input ~ 0
cv_in_b
Text GLabel 1700 3350 0    50   Input ~ 0
cv_in_b
Text Notes 7300 5450 0    50   ~ 0
TODO:\nJTAG connector\nOscillator\nUSART connector (header)
Text GLabel 9050 1450 0    50   Input ~ 0
trigger_in
Text GLabel 6050 2900 2    50   Input ~ 0
usart_tx
Text GLabel 6050 3000 2    50   Input ~ 0
usart_rx
Text GLabel 6050 3900 2    50   Input ~ 0
trigger_in
Text GLabel 6050 3100 2    50   Input ~ 0
trigger_out_a
Text GLabel 6050 3200 2    50   Input ~ 0
trigger_out_b
Text GLabel 6050 4800 2    50   Input ~ 0
jack_detect
Text GLabel 1700 3550 0    50   Input ~ 0
jack_detect
Text GLabel 9050 1650 0    50   Input ~ 0
jack_detect
$EndSCHEMATC
