EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 6
Title "frank.counts"
Date "2020-05-04"
Rev "2"
Comp "tbd"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	6150 2700 6350 2700
Wire Wire Line
	6150 2400 7150 2400
Wire Wire Line
	6150 2500 6750 2500
Wire Wire Line
	6350 2700 6350 3950
Wire Wire Line
	6350 3950 7800 3950
Wire Wire Line
	6750 2500 6750 3800
Wire Wire Line
	6750 3800 7800 3800
Wire Wire Line
	7150 2400 7150 3650
Wire Wire Line
	7150 3650 7800 3650
$Sheet
S 9050 1350 1100 650 
U 5ED4085B
F0 "Trigger Input" 50
F1 "trigger_input.sch" 50
F2 "jack_detect" O L 9050 1850 50 
F3 "trigger_in_a" O L 9050 1450 50 
F4 "trigger_in_b" O L 9050 1650 50 
$EndSheet
$Sheet
S 7800 3500 550  600 
U 5ED37B53
F0 "DAC" 50
F1 "dac.sch" 50
F2 "dac_sck" I L 7800 3800 50 
F3 "dac_cs" I L 7800 3650 50 
F4 "dac_mosi" I L 7800 3950 50 
$EndSheet
$Comp
L MCU_ST_STM32F3:STM32F302RBTx U?
U 1 1 5FBA4493
P 5450 3600
F 0 "U?" H 5450 1711 50  0000 C CNN
F 1 "STM32F302RBT6" H 5450 1620 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 4850 1900 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00094064.pdf" H 5450 3600 50  0001 C CNN
	1    5450 3600
	1    0    0    -1  
$EndComp
$Sheet
S 1550 3200 1050 800 
U 5FCA3E21
F0 "CV Input" 50
F1 "cv_input.sch" 50
$EndSheet
$Sheet
S 1850 1400 900  450 
U 5FCB1CD7
F0 "Power" 50
F1 "power.sch" 50
$EndSheet
$EndSCHEMATC
