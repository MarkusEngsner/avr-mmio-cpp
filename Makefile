SHELL = /bin/sh

OBJS = led.o
CFLAGS = -mmcu=atmega328p -Os -g -std=c++11
CC = avr-g++

#led.o: led.cpp
#	avr-g++ -g -Os -mmcu=atmega328p -c led.cpp -std=c++11 -o led.o

led.o: led.cpp
	avr-g++ -g -Os -mmcu=atmega328p -c led.cpp -std=c++11 -o led.o
	avr-g++ -mmcu=atmega328p led.o -o led
	avr-objcopy -O ihex -R .eeprom led led.hex


transfer: led.cpp
	avr-g++ -g -Os -mmcu=atmega328p -c led.cpp -std=c++11 -o led.o
	avr-g++ -mmcu=atmega328p led.o -o led
	avr-objcopy -O ihex -R .eeprom led led.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:led.hex

clean:
	rm led.o led led.hex