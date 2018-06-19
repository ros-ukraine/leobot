EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:MCU_Board
LIBS:MCU_Board-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L STM32F4DISCOVERY J1
U 1 1 5AFBC468
P 2500 3850
F 0 "J1" H 1900 5170 50  0000 L BNN
F 1 "STM32F4DISCOVERY" H 1899 2448 50  0000 L BNN
F 2 "STM32F4DISCOVERY:STMICROELECTRONICS_STM32F4DISCOVERY" H 2500 3850 50  0001 L BNN
F 3 "None" H 2500 3850 50  0001 L BNN
F 4 "Unavailable" H 2500 3850 50  0001 L BNN "Field4"
F 5 "STM32F4DISCOVERY" H 2500 3850 50  0001 L BNN "Field5"
F 6 "Development kit: ARM ST; pin strips, pin header; No.of" H 2500 3850 50  0001 L BNN "Field6"
F 7 "STMicroelectronics" H 2500 3850 50  0001 L BNN "Field7"
F 8 "None" H 2500 3850 50  0001 L BNN "Field8"
	1    2500 3850
	1    0    0    -1  
$EndComp
$Comp
L STM32F4DISCOVERY J1
U 2 1 5AFBC4D8
P 6450 3750
F 0 "J1" H 5850 5070 50  0000 L BNN
F 1 "STM32F4DISCOVERY" H 5849 2348 50  0000 L BNN
F 2 "STM32F4DISCOVERY:STMICROELECTRONICS_STM32F4DISCOVERY" H 6450 3750 50  0001 L BNN
F 3 "None" H 6450 3750 50  0001 L BNN
F 4 "Unavailable" H 6450 3750 50  0001 L BNN "Field4"
F 5 "STM32F4DISCOVERY" H 6450 3750 50  0001 L BNN "Field5"
F 6 "Development kit: ARM ST; pin strips, pin header; No.of" H 6450 3750 50  0001 L BNN "Field6"
F 7 "STMicroelectronics" H 6450 3750 50  0001 L BNN "Field7"
F 8 "None" H 6450 3750 50  0001 L BNN "Field8"
	2    6450 3750
	1    0    0    -1  
$EndComp
Text Label 9450 3600 0    60   ~ 0
MU3_DRV_PMW
Text Label 9450 3700 0    60   ~ 0
MU3_DRV_DIR
Text Label 9450 3800 0    60   ~ 0
MU3_DRV_ENB
$Comp
L Conn_01x09 J5
U 1 1 5B00128F
P 10400 3900
F 0 "J5" H 10400 4400 50  0000 C CNN
F 1 "Conn_01x09" H 10400 3400 50  0000 C CNN
F 2 "" H 10400 3900 50  0001 C CNN
F 3 "" H 10400 3900 50  0001 C CNN
	1    10400 3900
	1    0    0    -1  
$EndComp
Text Label 9450 3500 0    60   ~ 0
MU3_DRV_VCC
Text Label 9450 3900 0    60   ~ 0
MU3_DRV_GND
Text Label 9450 4000 0    60   ~ 0
MU3_HAL_GND
Text Label 9450 4100 0    60   ~ 0
ENCODER_VCC
Text Label 9450 4200 0    60   ~ 0
MU3_HAL_SEN_A
Text Label 9450 4300 0    60   ~ 0
MU3_HAL_SEN_B
Wire Wire Line
	10200 3500 9350 3500
Wire Wire Line
	9350 3600 10200 3600
Wire Wire Line
	10200 3700 9350 3700
Wire Wire Line
	9350 3800 10200 3800
Wire Wire Line
	10200 3900 9350 3900
Wire Wire Line
	9350 4000 10200 4000
Wire Wire Line
	10200 4100 9350 4100
Wire Wire Line
	9350 4200 10200 4200
Wire Wire Line
	10200 4300 9350 4300
Wire Wire Line
	6550 900  7250 900 
Wire Wire Line
	6550 1000 7250 1000
Text Label 6550 900  0    60   ~ 0
MCU_USART2_TX
Text Label 6550 1000 0    60   ~ 0
MCU_USART2_RX
$Comp
L GNDS #PWR01
U 1 1 5B001EDA
P 7150 1200
F 0 "#PWR01" H 7150 950 50  0001 C CNN
F 1 "GNDS" H 7150 1050 50  0000 C CNN
F 2 "" H 7150 1200 50  0001 C CNN
F 3 "" H 7150 1200 50  0001 C CNN
	1    7150 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 1100 7150 1100
Wire Wire Line
	7150 1100 7150 1200
Text Label 900  3250 0    60   ~ 0
MCU_USART2_RX
Text Label 3350 3250 0    60   ~ 0
MCU_USART2_TX
Wire Wire Line
	1700 3250 850  3250
Wire Wire Line
	3300 3250 4100 3250
Text Label 9450 4750 0    60   ~ 0
MU4_DRV_PMW
Text Label 9450 4850 0    60   ~ 0
MU4_DRV_DIR
Text Label 9450 4950 0    60   ~ 0
MU4_DRV_ENB
$Comp
L Conn_01x09 J6
U 1 1 5B0027E8
P 10400 5050
F 0 "J6" H 10400 5550 50  0000 C CNN
F 1 "Conn_01x09" H 10400 4550 50  0000 C CNN
F 2 "" H 10400 5050 50  0001 C CNN
F 3 "" H 10400 5050 50  0001 C CNN
	1    10400 5050
	1    0    0    -1  
$EndComp
Text Label 9450 4650 0    60   ~ 0
MU4_DRV_VCC
Text Label 9450 5050 0    60   ~ 0
MU4_DRV_GND
Text Label 9450 5150 0    60   ~ 0
MU4_HAL_GND
Text Label 9450 5250 0    60   ~ 0
ENCODER_VCC
Text Label 9450 5350 0    60   ~ 0
MU4_HAL_SEN_A
Text Label 9450 5450 0    60   ~ 0
MU4_HAL_SEN_B
Wire Wire Line
	10200 4650 9350 4650
Wire Wire Line
	9350 4750 10200 4750
Wire Wire Line
	10200 4850 9350 4850
Wire Wire Line
	9350 4950 10200 4950
Wire Wire Line
	10200 5050 9350 5050
Wire Wire Line
	9350 5150 10200 5150
Wire Wire Line
	10200 5250 9350 5250
Wire Wire Line
	9350 5350 10200 5350
Wire Wire Line
	10200 5450 9350 5450
Text Label 9450 1250 0    60   ~ 0
MU1_DRV_PMW
Text Label 9450 1350 0    60   ~ 0
MU1_DRV_DIR
Text Label 9450 1450 0    60   ~ 0
MU1_DRV_ENB
$Comp
L Conn_01x09 J3
U 1 1 5B0028D8
P 10400 1550
F 0 "J3" H 10400 2050 50  0000 C CNN
F 1 "Conn_01x09" H 10400 1050 50  0000 C CNN
F 2 "" H 10400 1550 50  0001 C CNN
F 3 "" H 10400 1550 50  0001 C CNN
	1    10400 1550
	1    0    0    -1  
$EndComp
Text Label 9450 1150 0    60   ~ 0
MU1_DRV_VCC
Text Label 9450 1550 0    60   ~ 0
MU1_DRV_GND
Text Label 9450 1650 0    60   ~ 0
MU1_HAL_GND
Text Label 9450 1750 0    60   ~ 0
ENCODER_VCC
Text Label 9450 1850 0    60   ~ 0
MU1_HAL_SEN_A
Text Label 9450 1950 0    60   ~ 0
MU1_HAL_SEN_B
Wire Wire Line
	10200 1150 9350 1150
Wire Wire Line
	9350 1250 10200 1250
Wire Wire Line
	10200 1350 9350 1350
Wire Wire Line
	9350 1450 10200 1450
Wire Wire Line
	10200 1550 9350 1550
Wire Wire Line
	9350 1650 10200 1650
Wire Wire Line
	10200 1750 9350 1750
Wire Wire Line
	9350 1850 10200 1850
Wire Wire Line
	10200 1950 9350 1950
Text Label 9450 2400 0    60   ~ 0
MU2_DRV_PMW
Text Label 9450 2500 0    60   ~ 0
MU2_DRV_DIR
Text Label 9450 2600 0    60   ~ 0
MU2_DRV_ENB
$Comp
L Conn_01x09 J4
U 1 1 5B0028F0
P 10400 2700
F 0 "J4" H 10400 3200 50  0000 C CNN
F 1 "Conn_01x09" H 10400 2200 50  0000 C CNN
F 2 "" H 10400 2700 50  0001 C CNN
F 3 "" H 10400 2700 50  0001 C CNN
	1    10400 2700
	1    0    0    -1  
$EndComp
Text Label 9450 2300 0    60   ~ 0
MU2_DRV_VCC
Text Label 9450 2700 0    60   ~ 0
MU2_DRV_GND
Text Label 9450 2800 0    60   ~ 0
MU2_HAL_GND
Text Label 9450 2900 0    60   ~ 0
ENCODER_VCC
Text Label 9450 3000 0    60   ~ 0
MU2_HAL_SEN_A
Text Label 9450 3100 0    60   ~ 0
MU2_HAL_SEN_B
Wire Wire Line
	10200 2300 9350 2300
Wire Wire Line
	9350 2400 10200 2400
Wire Wire Line
	10200 2500 9350 2500
Wire Wire Line
	9350 2600 10200 2600
Wire Wire Line
	10200 2700 9350 2700
Wire Wire Line
	9350 2800 10200 2800
Wire Wire Line
	10200 2900 9350 2900
Wire Wire Line
	9350 3000 10200 3000
Wire Wire Line
	10200 3100 9350 3100
Text Label 900  3950 0    60   ~ 0
MU1_HAL_SEN_A
Text Label 3350 3950 0    60   ~ 0
MU1_HAL_SEN_B
Wire Wire Line
	1700 3950 850  3950
Wire Wire Line
	3300 3950 4100 3950
Text Label 3350 3150 0    60   ~ 0
MU2_HAL_SEN_A
Text Label 900  3150 0    60   ~ 0
MU2_HAL_SEN_B
Wire Wire Line
	3300 3150 4100 3150
Wire Wire Line
	850  3150 1700 3150
Text Label 3350 3450 0    60   ~ 0
MU3_HAL_SEN_A
Text Label 900  3450 0    60   ~ 0
MU3_HAL_SEN_B
Wire Wire Line
	850  3450 1700 3450
Wire Wire Line
	3300 3450 4100 3450
Text Label 4750 4850 0    60   ~ 0
MU4_HAL_SEN_A
Text Label 7350 4850 0    60   ~ 0
MU4_HAL_SEN_B
Wire Wire Line
	1700 4850 850  4850
$Comp
L GNDS #PWR02
U 1 1 5B004101
P 1650 5150
F 0 "#PWR02" H 1650 4900 50  0001 C CNN
F 1 "GNDS" H 1650 5000 50  0000 C CNN
F 2 "" H 1650 5150 50  0001 C CNN
F 3 "" H 1650 5150 50  0001 C CNN
	1    1650 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 5050 1650 5050
Wire Wire Line
	1650 5050 1650 5150
$Comp
L GNDS #PWR03
U 1 1 5B0041E8
P 3400 5150
F 0 "#PWR03" H 3400 4900 50  0001 C CNN
F 1 "GNDS" H 3400 5000 50  0000 C CNN
F 2 "" H 3400 5150 50  0001 C CNN
F 3 "" H 3400 5150 50  0001 C CNN
	1    3400 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 5050 3400 5050
Wire Wire Line
	3400 5050 3400 5150
$Comp
L GNDS #PWR04
U 1 1 5B004347
P 5550 5000
F 0 "#PWR04" H 5550 4750 50  0001 C CNN
F 1 "GNDS" H 5550 4850 50  0000 C CNN
F 2 "" H 5550 5000 50  0001 C CNN
F 3 "" H 5550 5000 50  0001 C CNN
	1    5550 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 4950 5550 4950
Wire Wire Line
	5550 4950 5550 5000
$Comp
L GNDS #PWR06
U 1 1 5B00470C
P 7350 5000
F 0 "#PWR06" H 7350 4750 50  0001 C CNN
F 1 "GNDS" H 7350 4850 50  0000 C CNN
F 2 "" H 7350 5000 50  0001 C CNN
F 3 "" H 7350 5000 50  0001 C CNN
	1    7350 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 5000 7350 4950
Wire Wire Line
	7350 4950 7250 4950
Wire Wire Line
	8100 4850 7250 4850
Wire Wire Line
	5650 4850 4700 4850
Wire Wire Line
	3300 4750 3800 4750
Wire Wire Line
	3300 4850 3800 4850
Wire Wire Line
	1700 4950 850  4950
Wire Wire Line
	4950 3650 5650 3650
Wire Wire Line
	7250 3650 7900 3650
Wire Wire Line
	4950 3450 5650 3450
Wire Wire Line
	7250 3450 7900 3450
Text Label 4950 3650 0    60   ~ 0
MU1_DRV_PMW
Text Label 7300 3650 0    60   ~ 0
MU2_DRV_PMW
Text Label 4950 3450 0    60   ~ 0
MU3_DRV_PMW
Text Label 7300 3450 0    60   ~ 0
MU4_DRV_PMW
Text Label 4850 4750 0    60   ~ 0
IMU_I2C3_SCL
Text Label 7350 4750 0    60   ~ 0
IMU_I2C3_SDA
Wire Wire Line
	7250 4750 8100 4750
Wire Wire Line
	4700 4750 5650 4750
$Comp
L Conn_01x05 J?
U 1 1 5B03ADE5
P 4650 1150
F 0 "J?" H 4650 1450 50  0000 C CNN
F 1 "Conn_01x05" H 4650 850 50  0000 C CNN
F 2 "" H 4650 1150 50  0001 C CNN
F 3 "" H 4650 1150 50  0001 C CNN
	1    4650 1150
	1    0    0    -1  
$EndComp
Text Label 3750 1150 0    60   ~ 0
IMU_I2C3_SCL
Text Label 3750 1250 0    60   ~ 0
IMU_I2C3_SDA
Text Label 3750 1350 0    60   ~ 0
IMU_INT
Wire Wire Line
	4450 1150 3700 1150
Wire Wire Line
	3700 1250 4450 1250
Wire Wire Line
	3700 1350 4450 1350
$Comp
L +5V #PWR?
U 1 1 5B03B7B5
P 4350 850
F 0 "#PWR?" H 4350 700 50  0001 C CNN
F 1 "+5V" H 4350 990 50  0000 C CNN
F 2 "" H 4350 850 50  0001 C CNN
F 3 "" H 4350 850 50  0001 C CNN
	1    4350 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 950  4350 950 
Wire Wire Line
	4350 950  4350 850 
$Comp
L GNDS #PWR?
U 1 1 5B03BB33
P 3500 1100
F 0 "#PWR?" H 3500 850 50  0001 C CNN
F 1 "GNDS" H 3500 950 50  0000 C CNN
F 2 "" H 3500 1100 50  0001 C CNN
F 3 "" H 3500 1100 50  0001 C CNN
	1    3500 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 1050 3500 1050
Wire Wire Line
	3500 1050 3500 1100
$Comp
L +5V #PWR?
U 1 1 5B03C100
P 7450 2650
F 0 "#PWR?" H 7450 2500 50  0001 C CNN
F 1 "+5V" H 7450 2790 50  0000 C CNN
F 2 "" H 7450 2650 50  0001 C CNN
F 3 "" H 7450 2650 50  0001 C CNN
	1    7450 2650
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR?
U 1 1 5B03C173
P 5450 2650
F 0 "#PWR?" H 5450 2500 50  0001 C CNN
F 1 "+5V" H 5450 2790 50  0000 C CNN
F 2 "" H 5450 2650 50  0001 C CNN
F 3 "" H 5450 2650 50  0001 C CNN
	1    5450 2650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5650 2550 5600 2550
Wire Wire Line
	5650 2650 5450 2650
Wire Wire Line
	7450 2650 7250 2650
$Comp
L Conn_01x04 J?
U 1 1 5B03C5E9
P 7450 900
F 0 "J?" H 7450 1100 50  0000 C CNN
F 1 "Conn_01x04" H 7450 600 50  0000 C CNN
F 2 "" H 7450 900 50  0001 C CNN
F 3 "" H 7450 900 50  0001 C CNN
	1    7450 900 
	1    0    0    -1  
$EndComp
$Comp
L +5VD #PWR?
U 1 1 5B03C6A5
P 7150 700
F 0 "#PWR?" H 7150 550 50  0001 C CNN
F 1 "+5VD" H 7150 840 50  0000 C CNN
F 2 "" H 7150 700 50  0001 C CNN
F 3 "" H 7150 700 50  0001 C CNN
	1    7150 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 800  7150 800 
Wire Wire Line
	7150 800  7150 700 
$Comp
L R R?
U 1 1 5B03CA55
P 2850 1700
F 0 "R?" V 2930 1700 50  0000 C CNN
F 1 "R" V 2850 1700 50  0000 C CNN
F 2 "" V 2780 1700 50  0001 C CNN
F 3 "" H 2850 1700 50  0001 C CNN
	1    2850 1700
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 5B03CB93
P 2850 1900
F 0 "R?" V 2930 1900 50  0000 C CNN
F 1 "0R" V 2850 1900 50  0000 C CNN
F 2 "" V 2780 1900 50  0001 C CNN
F 3 "" H 2850 1900 50  0001 C CNN
	1    2850 1900
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR?
U 1 1 5B03CC0F
P 3150 1600
F 0 "#PWR?" H 3150 1450 50  0001 C CNN
F 1 "+5V" H 3150 1740 50  0000 C CNN
F 2 "" H 3150 1600 50  0001 C CNN
F 3 "" H 3150 1600 50  0001 C CNN
	1    3150 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 1700 3150 1700
Wire Wire Line
	3150 1600 3150 1900
Wire Wire Line
	3150 1900 3000 1900
Connection ~ 3150 1700
Wire Wire Line
	2700 1700 2550 1700
Wire Wire Line
	2550 1900 2700 1900
$Comp
L +5VD #PWR?
U 1 1 5B03CF12
P 2550 1600
F 0 "#PWR?" H 2550 1450 50  0001 C CNN
F 1 "+5VD" H 2550 1740 50  0000 C CNN
F 2 "" H 2550 1600 50  0001 C CNN
F 3 "" H 2550 1600 50  0001 C CNN
	1    2550 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 1700 2550 1600
Text Label 7250 2750 0    60   ~ 0
ENCODER_VCC
Wire Wire Line
	7250 2750 7900 2750
$EndSCHEMATC
