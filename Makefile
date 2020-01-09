MAINFILENAME=main
#MCU=atmega2560
MCU=atmega328p
OPTIMIZE=-Os
XTAL=16000000
CFLAGS=-c $(OPTIMIZE) -IInclude -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -fno-devirtualize -fno-use-cxa-atexit -mmcu=$(MCU) -DF_CPU=$(XTAL)
LFLAGS=$(OPTIMIZE) -Wall -Wextra -flto -fuse-linker-plugin -ffunction-sections -fdata-sections -Wl,--gc-sections -mmcu=$(MCU) -lm

all: size

Build/main: lib
	avr-g++ $(CFLAGS) "Src/$(MAINFILENAME).cpp" -o "Build/$(MAINFILENAME).o"

Build/core.a:
	avr-gcc-ar rcs Build/core.a Build/DigitalRegisters.o
	avr-gcc-ar rcs Build/core.a Build/CustomFuncs.o
	avr-gcc-ar rcs Build/core.a Build/StringFuncs.o
	avr-gcc-ar rcs Build/core.a Build/Usart.o
	avr-gcc-ar rcs Build/core.a Build/Timers.o
	avr-gcc-ar rcs Build/core.a Build/ADC.o
	#avr-gcc-ar rcs Build/core.a Build/FuncsInputProtector.o
	avr-gcc-ar rcs Build/core.a Build/WatchdogTimer.o
	avr-gcc-ar rcs Build/core.a Build/TWI.o
	avr-gcc-ar rcs Build/core.a Build/NumFuncs.o

link: Build/main Build/core.a lib
	avr-gcc $(LFLAGS) Build/main.o Build/core.a -o Build/main.elf

objcopy: link
	avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "Build/$(MAINFILENAME).elf" "Build/$(MAINFILENAME).eep"
	avr-objcopy -O ihex -R .eeprom  "Build/$(MAINFILENAME).elf" "Build/$(MAINFILENAME).hex"

lib: _lib Build/core.a
_lib: Build/Usart.o Build/Timers.o Build/ADC.o Build/FuncsInputProtector.o Build/DigitalRegisters.o Build/StringFuncs.o Build/WatchdogTimer.o Build/CustomFuncs.o Build/TWI.o Build/NumFuncs.o


Build/Usart.o:
	avr-g++ $(CFLAGS) "Src/USART.cpp" -o "Build/Usart.o"

Build/Timers.o:
	avr-g++ $(CFLAGS) "Src/Timers.cpp" -o "Build/Timers.o"

Build/ADC.o:
	avr-g++ $(CFLAGS) "Src/ADC.cpp" -o "Build/ADC.o"

Build/FuncsInputProtector.o:
	avr-g++ $(CFLAGS) "Src/FuncsInputProtector.cpp" -o "Build/FuncsInputProtector.o"

Build/StringFuncs.o:
	avr-g++ $(CFLAGS) "Src/stringFuncs.cpp" -o "Build/StringFuncs.o"

Build/WatchdogTimer.o:
	avr-g++ $(CFLAGS) "Src/watchdog.cpp" -o "Build/WatchdogTimer.o"

Build/DigitalRegisters.o:
	avr-g++ $(CFLAGS) "Src/digitalRegisters.cpp" -o "Build/DigitalRegisters.o"

Build/CustomFuncs.o:
	avr-g++ $(CFLAGS) "Src/customFuncAddr.cpp" -o "Build/CustomFuncs.o"

Build/TWI.o:
	avr-g++ $(CFLAGS) "Src/TWI.cpp" -o "Build/TWI.o"

Build/NumFuncs.o:
	avr-g++ $(CFLAGS) "Src/numFuncs.cpp" -o "Build/NumFuncs.o"

clean:
	rm -rf Build/*

size: objcopy
	avr-size Build/$(MAINFILENAME).elf -C --mcu=$(MCU)


