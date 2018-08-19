MAINFILENAME=main
MCU=atmega2560
CFLAGS=-c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -fno-devirtualize -fno-use-cxa-atexit -mmcu=$(MCU) -DF_CPU=$(XTAL) 


all: main
	
main: Usart.o Timers.o ADC.o 
	avr-g++ $(CFLAGS) "$(MAINFILENAME).cpp" -o "$(MAINFILENAME).o"
	avr-gcc -Wall -Wextra -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=$(MCU)  -o "$(MAINFILENAME).elf" "$(MAINFILENAME).o" -lm
	avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "$(MAINFILENAME).elf" "$(MAINFILENAME).eep"
	avr-objcopy -O ihex -R .eeprom  "$(MAINFILENAME).elf" "$(MAINFILENAME).hex"

lib: Usart.o Timers.o ADC.o 

Usart.o:
	avr-g++ $(CFLAGS) "USART.c" -o "USART.o"

Timers.o:
	avr-g++ $(CFLAGS) -DF_CPU=$(XTAL) "Timers.c" -o "Timers.o"

ADC.o:
	avr-g++ $(CFLAGS) "ADC.c" -o "ADC.o"

stringFuncs.o:
	avr-g++ $(CFLAGS) "stringFuncs.c" -o "stringFuncs.o"

clean: 
	rm -rf ./*.o ./*.d ./*.eep ./*.elf ./*.hex

size:
	avr-size -B $(MAINFILENAME).hex
