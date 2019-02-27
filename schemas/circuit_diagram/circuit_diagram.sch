EESchema Schematic File Version 4
LIBS:circuit_diagram-cache
EELAYER 26 0
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
L ESP8266:NodeMCU1.0(ESP-12E) U?
U 1 1 5C75CE7F
P 3000 3300
F 0 "U?" H 3000 4387 60  0000 C CNN
F 1 "NodeMCU1.0(ESP-12E)" H 3000 4281 60  0000 C CNN
F 2 "" H 2400 2450 60  0000 C CNN
F 3 "" H 2400 2450 60  0000 C CNN
	1    3000 3300
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_DC M?
U 1 1 5C75CFAC
P 6950 3850
F 0 "M?" H 7108 3846 50  0000 L CNN
F 1 "Motor_DC" H 7108 3755 50  0000 L CNN
F 2 "" H 6950 3760 50  0001 C CNN
F 3 "~" H 6950 3760 50  0001 C CNN
	1    6950 3850
	1    0    0    -1  
$EndComp
$Comp
L pkl_misc:74HC165 U?
U 1 1 5C75D110
P 5000 850
F 0 "U?" H 5000 1747 60  0000 C CNN
F 1 "74HC165" H 5000 1641 60  0000 C CNN
F 2 "" H 7190 -370 60  0001 C CNN
F 3 "" H 7190 -370 60  0001 C CNN
	1    5000 850 
	1    0    0    -1  
$EndComp
$Comp
L Isolator:SFH617A-1 U?
U 1 1 5C75D441
P 9600 1800
F 0 "U?" H 9600 2125 50  0000 C CNN
F 1 "SFH617A-1" H 9600 2034 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 9400 1600 50  0001 L CIN
F 3 "http://www.vishay.com/docs/83740/sfh617a.pdf" H 9600 1800 50  0001 L CNN
	1    9600 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 1350 4300 1350
Wire Wire Line
	4400 1250 4200 1250
$Comp
L Driver_Motor:TB6612FNG U?
U 1 1 5C763434
P 5200 6500
F 0 "U?" H 5200 7678 50  0000 C CNN
F 1 "TB6612FNG" H 5200 7587 50  0000 C CNN
F 2 "Package_SO:SSOP-24_5.3x8.2mm_P0.65mm" H 5650 7100 50  0001 C CNN
F 3 "https://toshiba.semicon-storage.com/us/product/linear/motordriver/detail.TB6612FNG.html" H 5650 7100 50  0001 C CNN
	1    5200 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 250  4400 250 
Wire Wire Line
	3800 2600 4100 2600
Wire Wire Line
	4200 1250 4200 2700
Wire Wire Line
	4300 1350 4300 2700
Wire Wire Line
	4100 250  4100 2600
Wire Wire Line
	4200 2700 4200 3000
Wire Wire Line
	3800 3000 4200 3000
Wire Wire Line
	3800 2700 4300 2700
Wire Wire Line
	4600 6600 4500 6600
Wire Wire Line
	4500 2800 4500 6600
Wire Wire Line
	4400 1450 4400 3800
Wire Wire Line
	4300 3800 4400 3800
Wire Wire Line
	4300 6700 4600 6700
Wire Wire Line
	3800 3800 4300 3800
Wire Wire Line
	3800 2900 4300 2900
Wire Wire Line
	4300 2900 4300 6700
Wire Wire Line
	3800 2800 4500 2800
Wire Wire Line
	4600 3900 4600 3750
$Comp
L Driver_Motor:TB6612FNG U?
U 1 1 5C760F96
P 5200 4300
F 0 "U?" H 5200 5478 50  0000 C CNN
F 1 "TB6612FNG" H 5200 5387 50  0000 C CNN
F 2 "Package_SO:SSOP-24_5.3x8.2mm_P0.65mm" H 5650 4900 50  0001 C CNN
F 3 "https://toshiba.semicon-storage.com/us/product/linear/motordriver/detail.TB6612FNG.html" H 5650 4900 50  0001 C CNN
	1    5200 4300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C77295E
P 4600 3750
F 0 "#PWR?" H 4600 3500 50  0001 C CNN
F 1 "GND" V 4605 3622 50  0000 R CNN
F 2 "" H 4600 3750 50  0001 C CNN
F 3 "" H 4600 3750 50  0001 C CNN
	1    4600 3750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4600 4100 4200 4100
Wire Wire Line
	4200 4100 4200 3300
Wire Wire Line
	4200 3300 3800 3300
Wire Wire Line
	4600 4200 4100 4200
Wire Wire Line
	4100 4200 4100 3400
Wire Wire Line
	4100 3400 3800 3400
Wire Wire Line
	4000 6300 4000 3500
Wire Wire Line
	4000 3500 3800 3500
Wire Wire Line
	4600 6300 4000 6300
Wire Wire Line
	5800 3900 5800 3950
Wire Wire Line
	5800 4100 5800 4150
Wire Wire Line
	5800 4400 5800 4450
Wire Wire Line
	5800 4600 5800 4650
Wire Wire Line
	5300 3300 5400 3300
Connection ~ 5400 3300
Wire Wire Line
	5400 3300 5500 3300
Wire Wire Line
	5250 5300 5300 5300
Connection ~ 5300 5300
Wire Wire Line
	5300 5300 5400 5300
Connection ~ 5400 5300
Wire Wire Line
	5400 5300 5500 5300
Wire Wire Line
	5300 5500 5400 5500
Connection ~ 5400 5500
Wire Wire Line
	5400 5500 5500 5500
Wire Wire Line
	5800 6100 5800 6150
Wire Wire Line
	5800 6400 5800 6350
Wire Wire Line
	5800 6700 5800 6650
Wire Wire Line
	5800 6900 5800 6850
Wire Wire Line
	6950 3650 6400 3650
Wire Wire Line
	6400 3650 6400 3950
Wire Wire Line
	6400 3950 5800 3950
Connection ~ 5800 3950
Wire Wire Line
	5800 3950 5800 4000
Wire Wire Line
	6950 4150 5800 4150
Connection ~ 5800 4150
Wire Wire Line
	5800 4150 5800 4200
$Comp
L Motor:Motor_DC M?
U 1 1 5C77B5F2
P 6950 4650
F 0 "M?" H 7108 4646 50  0000 L CNN
F 1 "Motor_DC" H 7108 4555 50  0000 L CNN
F 2 "" H 6950 4560 50  0001 C CNN
F 3 "~" H 6950 4560 50  0001 C CNN
	1    6950 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 4450 5800 4450
Connection ~ 5800 4450
Wire Wire Line
	5800 4450 5800 4500
Wire Wire Line
	6950 4950 6400 4950
Wire Wire Line
	6400 4950 6400 4650
Wire Wire Line
	6400 4650 5800 4650
Connection ~ 5800 4650
Wire Wire Line
	5800 4650 5800 4700
$Comp
L Motor:Motor_DC M?
U 1 1 5C77CAE6
P 6950 6050
F 0 "M?" H 7108 6046 50  0000 L CNN
F 1 "Motor_DC" H 7108 5955 50  0000 L CNN
F 2 "" H 6950 5960 50  0001 C CNN
F 3 "~" H 6950 5960 50  0001 C CNN
	1    6950 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 5850 6400 6150
Wire Wire Line
	6400 6150 5800 6150
Wire Wire Line
	6950 6350 5800 6350
$Comp
L Motor:Motor_DC M?
U 1 1 5C77CAEF
P 6950 6850
F 0 "M?" H 7108 6846 50  0000 L CNN
F 1 "Motor_DC" H 7108 6755 50  0000 L CNN
F 2 "" H 6950 6760 50  0001 C CNN
F 3 "~" H 6950 6760 50  0001 C CNN
	1    6950 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 6650 5800 6650
Wire Wire Line
	6950 7150 6400 7150
Wire Wire Line
	6400 7150 6400 6850
Wire Wire Line
	6400 6850 5800 6850
Connection ~ 5800 6150
Wire Wire Line
	5800 6150 5800 6200
Connection ~ 5800 6350
Wire Wire Line
	5800 6350 5800 6300
Connection ~ 5800 6650
Wire Wire Line
	5800 6650 5800 6600
Connection ~ 5800 6850
Wire Wire Line
	5800 6850 5800 6800
Wire Wire Line
	6400 5850 6950 5850
$Comp
L Sensor_Pressure:MPXA6115A U?
U 1 1 5C77F3BE
P 1400 2300
F 0 "U?" H 970 2346 50  0000 R CNN
F 1 "MPXA6115A" H 970 2255 50  0000 R CNN
F 2 "" H 900 1950 50  0001 C CNN
F 3 "http://www.nxp.com/files/sensors/doc/data_sheet/MPXA6115A.pdf" H 1400 2900 50  0001 C CNN
	1    1400 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 2600 1950 2600
Wire Wire Line
	1950 2600 1950 2300
Wire Wire Line
	1950 2300 1800 2300
$EndSCHEMATC
