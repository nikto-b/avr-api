MAINFILENAME=main
#MCU=atmega2560
MCU=atmega328p
OPTIMIZE=-Os
CFLAGS=-c $(OPTIMIZE) -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -fno-devirtualize -fno-use-cxa-atexit -mmcu=$(MCU) -DF_CPU=$(XTAL)
LFLAGS=$(OPTIMIZE) -Wall -Wextra -flto -fuse-linker-plugin -ffunction-sections -fdata-sections -Wl,--gc-sections -mmcu=$(MCU) -lm

all: size

main: lib
	avr-g++ $(CFLAGS) "$(MAINFILENAME).cpp" -o "$(MAINFILENAME).o"

core.a:
	avr-gcc-ar rcs core.a DigitalRegisters.o
	avr-gcc-ar rcs core.a CustomFuncs.o
	avr-gcc-ar rcs core.a StringFuncs.o
	avr-gcc-ar rcs core.a Usart.o
	avr-gcc-ar rcs core.a Timers.o
	avr-gcc-ar rcs core.a ADC.o
	#avr-gcc-ar rcs core.a FuncsInputProtector.o
	avr-gcc-ar rcs core.a WatchdogTimer.o
	avr-gcc-ar rcs core.a TWI.o
	avr-gcc-ar rcs core.a NumFuncs.o

link: main core.a lib
	avr-gcc $(LFLAGS) main.o core.a -o main.elf

objcopy: link
	avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "$(MAINFILENAME).elf" "$(MAINFILENAME).eep"
	avr-objcopy -O ihex -R .eeprom  "$(MAINFILENAME).elf" "$(MAINFILENAME).hex"

lib: _lib core.a
_lib: Usart.o Timers.o ADC.o FuncsInputProtector.o DigitalRegisters.o StringFuncs.o WatchdogTimer.o CustomFuncs.o TWI.o NumFuncs.o


Usart.o:
	avr-g++ $(CFLAGS) "USART.c" -o "Usart.o"

Timers.o:
	avr-g++ $(CFLAGS) "Timers.c" -o "Timers.o"

ADC.o:
	avr-g++ $(CFLAGS) "ADC.c" -o "ADC.o"

FuncsInputProtector.o:
	avr-g++ $(CFLAGS) "FuncsInputProtector.c" -o "FuncsInputProtector.o"

StringFuncs.o:
	avr-g++ $(CFLAGS) "stringFuncs.c" -o "StringFuncs.o"

WatchdogTimer.o:
	avr-g++ $(CFLAGS) "watchdog.c" -o "WatchdogTimer.o"

DigitalRegisters.o:
	avr-g++ $(CFLAGS) "digitalRegisters.c" -o "DigitalRegisters.o"

CustomFuncs.o:
	avr-g++ $(CFLAGS) "customFuncAddr.c" -o "CustomFuncs.o"

TWI.o:
	avr-g++ $(CFLAGS) "TWI.c" -o "TWI.o"

NumFuncs.o:
	avr-g++ $(CFLAGS) "numFuncs.cpp" -o "NumFuncs.o"

clean:
	rm -rf ./*.o ./*.d ./*.eep ./*.elf ./*.hex ./*.a

size: objcopy
	avr-size $(MAINFILENAME).elf -C --mcu=$(MCU)
