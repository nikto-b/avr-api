MAINFILENAME=avr-api
MCU=atmega328p
XTAL=16000000L
USBPORT=/dev/ttyUSB0
PROGRAMMER=arduino
BAUDRATE=115200
CFLAGS=-c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -fno-devirtualize -fno-use-cxa-atexit -mmcu=$(MCU) -DF_CPU=$(XTAL) 


all: main
	
main: Usart.o Timers.o ADC.oudo
	avr-g++ $(CFLAGS) "$(MAINFILENAME).cpp" -o "$(MAINFILENAME).o"
	avr-gcc -Wall -Wextra -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=$(MCU)  -o "$(MAINFILENAME).elf" "$(MAINFILENAME).o" -lm
	avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "$(MAINFILENAME).elf" "$(MAINFILENAME).eep"
	avr-objcopy -O ihex -R .eeprom  "$(MAINFILENAME).elf" "$(MAINFILENAME).hex"

Usart.o:
	avr-g++ $(CFLAGS) "USART.cpp" -o "USART.o"

Timers.o:
	avr-g++ $(CFLAGS) -DF_CPU=$(XTAL) "Timers.cpp" -o "Timers.o"

ADC.o:
	avr-g++ $(CFLAGS) "ADC.cpp" -o "ADC.o"

clean: 
	rm -rf ./*.o ./*.d ./*.eep ./*.elf

remove: clean
	rm -rf ./*.hex

run:
	avrdude -C/etc/avrdude.conf -v -p$(MCU) -P$(USBPORT) -c$(PROGRAMMER) -b$(BAUDRATE) -D -U flash:w:./$(FILENAME).hex:i

size:
	avr-size -B $(MAINFILENAME).hex
