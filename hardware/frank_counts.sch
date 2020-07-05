EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 3
Title "frank.counts"
Date "2020-05-04"
Rev "2"
Comp "tbd"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_ST_STM32F3:STM32F303VCTx U?
U 1 1 5ED4887B
P 6150 3750
F 0 "U?" H 6150 861 50  0000 C CNN
F 1 "STM32F303VCTx" H 6150 770 50  0000 C CNN
F 2 "Package_QFP:LQFP-100_14x14mm_P0.5mm" H 5550 1150 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00058181.pdf" H 6150 3750 50  0001 C CNN
	1    6150 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 1450 6950 1450
Wire Wire Line
	8150 1650 6950 1650
Wire Wire Line
	6950 2050 7150 2050
Wire Wire Line
	6950 1750 7950 1750
Wire Wire Line
	6950 1850 7550 1850
Text Label 7250 1450 0    50   ~ 0
TRIGGER_IN
Text Label 7050 1650 0    50   ~ 0
TRIGGER_JACK_DETECT
Wire Wire Line
	7150 2050 7150 3300
Wire Wire Line
	7150 3300 8600 3300
Wire Wire Line
	7550 1850 7550 3150
Wire Wire Line
	7550 3150 8600 3150
Wire Wire Line
	7950 1750 7950 3000
Wire Wire Line
	7950 3000 8600 3000
Text Label 7950 2400 1    50   ~ 0
DAC_CS
Text Label 7550 2550 1    50   ~ 0
DAC_SCK
Text Label 7150 2800 1    50   ~ 0
DAC_DATA
$Sheet
S 8150 1350 950  400 
U 5ED4085B
F0 "Trigger Input" 50
F1 "trigger_input.sch" 50
F2 "JACK_DETECT" O L 8150 1650 50 
F3 "TRIGGER_IN" O L 8150 1450 50 
$EndSheet
$Sheet
S 8600 2850 550  600 
U 5ED37B53
F0 "DAC" 50
F1 "dac.sch" 50
F2 "SCK" I L 8600 3150 50 
F3 "MOSI" I L 8600 3300 50 
F4 "CS" I L 8600 3000 50 
$EndSheet
$EndSCHEMATC
