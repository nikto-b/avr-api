#!/bin/bash

MCUNAME=atmega2560
# MCUNAME=atmega328p
#PROGRAMMER=wiring
PROGRAMMER=arduino
FILENAME=main
#USBPORT=/dev/ttyACM0
USBPORT=$(ls /dev/tty*)

if [[ $(echo $USBPORT | rg ACM) != "" ]]; then
#echo "A"
USBPORT=$(ls /dev/tty* | rg ACM);
else
        if [[ $(echo $USBPORT | rg USB) != "" ]]; then
                #echo "B"
                USBPORT=$(ls /dev/tty* | rg USB);
	else        
		echo "No ARDUINO found!"
		exit
	fi
fi
BAUDRATE=115200

picocom $USBPORT -b $BAUDRATE
