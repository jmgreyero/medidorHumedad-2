EESchema Schematic File Version 2  date 04/03/13 19:02:49
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
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
LIBS:medidorConductividadCapacitivo-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "4 mar 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 4600 1950 0    60   ~ 0
C1 debe tener pocas fugas -> cerámico o tantalio
Wire Wire Line
	2800 6750 2800 6650
Wire Wire Line
	2800 6650 3150 6650
Wire Wire Line
	5200 4400 5200 2250
Wire Wire Line
	5200 2250 6350 2250
Wire Wire Line
	4850 3600 4850 3800
Wire Wire Line
	4850 3800 3550 3800
Wire Wire Line
	4350 2800 4350 3000
Connection ~ 3900 6000
Wire Wire Line
	3900 5850 3900 6000
Connection ~ 3900 5200
Wire Wire Line
	3550 5200 3900 5200
Wire Wire Line
	3900 4500 3900 4400
Wire Wire Line
	3900 4400 3550 4400
Wire Wire Line
	6550 2400 6550 2100
Wire Wire Line
	6550 2100 3550 2100
Wire Wire Line
	6350 2250 6350 2400
Wire Wire Line
	4350 3000 3550 3000
Connection ~ 3950 2100
Wire Wire Line
	3950 2100 3950 1400
Wire Wire Line
	3950 1400 3550 1400
Wire Notes Line
	6400 2850 6400 4600
Wire Notes Line
	6500 2850 6500 4600
Connection ~ 4350 2100
Connection ~ 4850 2100
Connection ~ 3500 6000
Wire Wire Line
	3900 5000 3900 5350
Wire Wire Line
	4350 2100 4350 2300
Wire Wire Line
	4850 2100 4850 3200
Wire Wire Line
	3900 6000 3500 6000
Wire Wire Line
	5200 4800 5200 6650
Wire Wire Line
	5200 6650 3500 6650
$Comp
L C C2
U 1 1 51330A67
P 5200 4600
F 0 "C2" H 5250 4700 50  0000 L CNN
F 1 "470n poliester" H 5250 4500 50  0000 L CNN
	1    5200 4600
	-1   0    0    1   
$EndComp
$Comp
L CONNECTOR P8
U 1 1 5133087C
P 3500 6650
F 0 "P8" H 3850 6750 70  0000 C CNN
F 1 "GND" H 3850 6550 70  0000 C CNN
	1    3500 6650
	-1   0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 513216B8
P 3900 4750
F 0 "R?" V 3980 4750 50  0000 C CNN
F 1 "1K" V 3900 4750 50  0000 C CNN
	1    3900 4750
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 513216AC
P 3900 5600
F 0 "R?" V 3980 5600 50  0000 C CNN
F 1 "3K3" V 3900 5600 50  0000 C CNN
	1    3900 5600
	1    0    0    -1  
$EndComp
$Comp
L CONNECTOR P5
U 1 1 51321686
P 3550 4400
F 0 "P5" H 3900 4500 70  0000 C CNN
F 1 "V_1 (PIN-3)" H 3900 4300 70  0000 C CNN
	1    3550 4400
	-1   0    0    -1  
$EndComp
$Comp
L CONNECTOR P6
U 1 1 5132167B
P 3550 5200
F 0 "P6" H 3900 5300 70  0000 C CNN
F 1 "AIN0 (PIN-6)" H 3900 5100 70  0000 C CNN
	1    3550 5200
	-1   0    0    -1  
$EndComp
$Comp
L CONNECTOR P7
U 1 1 51321055
P 3500 6000
F 0 "P7" H 3850 6100 70  0000 C CNN
F 1 "V_0 (PIN-2)" H 3850 5900 70  0000 C CNN
	1    3500 6000
	-1   0    0    -1  
$EndComp
$Comp
L CONNECTOR P4
U 1 1 51320FE6
P 3550 3800
F 0 "P4" H 3900 3900 70  0000 C CNN
F 1 "G_C (PIN-4)" H 3900 3700 70  0000 C CNN
	1    3550 3800
	-1   0    0    -1  
$EndComp
$Comp
L CONNECTOR P3
U 1 1 51320FD8
P 3550 3000
F 0 "P3" H 3900 3100 70  0000 C CNN
F 1 "G_R (PIN-5)" H 3900 2900 70  0000 C CNN
	1    3550 3000
	-1   0    0    -1  
$EndComp
$Comp
L CONNECTOR P2
U 1 1 51320FC7
P 3550 2100
F 0 "P2" H 3900 2200 70  0000 C CNN
F 1 "AIN1 (PIN-7)" H 3900 2000 70  0000 C CNN
	1    3550 2100
	-1   0    0    -1  
$EndComp
$Comp
L CONNECTOR P1
U 1 1 51320FB3
P 3550 1400
F 0 "P1" H 3900 1500 70  0000 C CNN
F 1 "V_C (PIN-8)" H 3900 1300 70  0000 C CNN
	1    3550 1400
	-1   0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 51320942
P 4850 3400
F 0 "C1" H 4900 3500 50  0000 L CNN
F 1 "2u2" H 4900 3300 50  0000 L CNN
	1    4850 3400
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR?
U 1 1 5132091E
P 2800 6750
F 0 "#PWR?" H 2800 6750 30  0001 C CNN
F 1 "GND" H 2800 6680 30  0001 C CNN
	1    2800 6750
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P1
U 1 1 5130F380
P 6450 2750
F 0 "P1" V 6400 2750 40  0000 C CNN
F 1 "SONDA" V 6500 2750 40  0000 C CNN
	1    6450 2750
	0    1    1    0   
$EndComp
Text Notes 6250 5000 0    60   ~ 0
LA SONDA ESTÁ FORMADA POR DOS VARILLAS AISLADAS
Text Notes 6550 4500 0    60   ~ 0
SONDA
Text Notes 10450 7550 2    60   ~ 0
Detector conductividad capacitivo para Arduino
$Comp
L R R1
U 1 1 5126101D
P 4350 2550
F 0 "R1" V 4430 2550 50  0000 C CNN
F 1 "3K3" V 4350 2550 50  0000 C CNN
	1    4350 2550
	1    0    0    -1  
$EndComp
$EndSCHEMATC
