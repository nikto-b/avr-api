MAINFILENAME=main
MCU=atmega2560
CFLAGS=-c -O1 -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -fno-devirtualize -fno-use-cxa-atexit -mmcu=$(MCU) -DF_CPU=$(XTAL) 


all: objcopy
	
main: lib
	avr-g++ $(CFLAGS) "$(MAINFILENAME).cpp" -o "$(MAINFILENAME).o"

arc: main
	avr-gcc-ar rcs core.a digitalRegisters.o
	avr-gcc-ar rcs core.a customFuncAddr.o
	avr-gcc-ar rcs core.a stringFuncs.o
	avr-gcc-ar rcs core.a USART.o
	avr-gcc-ar rcs core.a Timers.o
	avr-gcc-ar rcs core.a ADC.o
	#avr-gcc-ar rcs core.a FuncsInputProtector.o
	avr-gcc-ar rcs core.a watchdog.o

link: arc
	avr-gcc -Wall -Wextra -Os -g -flto -fuse-linker-plugin -ffunction-sections -fdata-sections -Wl,--gc-sections -mmcu=$(MCU) main.o core.a  -o main.elf -lm

objcopy: link
	avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "$(MAINFILENAME).elf" "$(MAINFILENAME).eep"
	avr-objcopy -O ihex -R .eeprom  "$(MAINFILENAME).elf" "$(MAINFILENAME).hex"

lib: Usart.o Timers.o ADC.o FuncProtector.o DigitalRegisters.o StringFuncs.o WatchdogTimer.o CustomFuncs.o


Usart.o: 
	avr-g++ $(CFLAGS) "USART.c" -o "USART.o"

Timers.o:
	avr-g++ $(CFLAGS) "Timers.c" -o "Timers.o"

ADC.o:
	avr-g++ $(CFLAGS) "ADC.c" -o "ADC.o"

FuncProtector.o:
	avr-g++ $(CFLAGS) "FuncsInputProtector.c" -o "FuncsInputProtector.o"

StringFuncs.o:
	avr-g++ $(CFLAGS) "stringFuncs.c" -o "stringFuncs.o"

WatchdogTimer.o:
	avr-g++ $(CFLAGS) "watchdog.c" -o "watchdog.o"

DigitalRegisters.o:
	avr-g++ $(CFLAGS) "digitalRegisters.c" -o "digitalRegisters.o"

CustomFuncs.o:
	avr-g++ $(CFLAGS) "customFuncAddr.c" -o "customFuncAddr.o"


clean: 
	rm -rf ./*.o ./*.d ./*.eep ./*.elf ./*.hex ./*.a

size:
	avr-size $(MAINFILENAME).elf -A --mcu=$(MCU) -d -h
