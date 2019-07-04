# set this to false to disable sonars in firmware

PREFIX=../
ARCH=arch/
CC=avr-gcc
INCLUDE_DIRS=-I$(PREFIX)/src/common -I$(PREFIX)/src/arch/include -I$(PREFIX)/src/orazio_firmware
CC_OPTS=-Wall -std=gnu99 -DF_CPU=16000000UL    -O3 -funsigned-char -funsigned-bitfields  -fshort-enums -Wall -Wstrict-prototypes -mmcu=atmega2560 -D_ARDUINO_MEGA_2560_ $(INCLUDE_DIRS) 


AVRDUDE=avrdude

# com1 = serial port. Use lpt1 to connect to parallel port.
AVRDUDE_PORT = /dev/ttyACM0    # programmer connected to serial device

AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET):i
AVRDUDE_FLAGS = -p m2560 -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER) -b 115200
AVRDUDE_FLAGS += $(AVRDUDE_NO_VERIFY)
AVRDUDE_FLAGS += $(AVRDUDE_VERBOSE)
AVRDUDE_FLAGS += $(AVRDUDE_ERASE_COUNTER)
AVRDUDE_FLAGS += -D -q -V -C /usr/share/arduino/hardware/tools/avr/../avrdude.conf
AVRDUDE_FLAGS += -c wiring


OBJS=pins.o\
     eeprom.o\
     digio.o\

HEADERS=pins.h\
	eeprom.h\
	digio.h\

BINS= main_test.elf\

.phony:	clean all

all:	$(BINS)

#common objects
%.o:	$(PREFIX)/src/common/%.c 
	$(CC) $(CC_OPTS) -c  $<

#peripherials
%.o:	$(PREFIX)/src/$(ARCH)/%.c 
	$(CC) $(CC_OPTS) -c  $<

#peripherial test
%.o:	$(PREFIX)/src/micro_test/%.c 
	$(CC) $(CC_OPTS) -c  $<

#orazio server objects
%.o:	$(PREFIX)/src/orazio_firmware/%.c 
	$(CC) $(CC_OPTS) -c  $<

%.elf:	%.o $(OBJS)
	$(CC) $(CC_OPTS) -o $@ $< $(OBJS) $(LIBS)

clean:
	rm -rf $(OBJS) $(BINS) *.hex *~ *.o

%.hex:	%.elf
	avr-objcopy -O ihex -R .eeprom $< $@
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U flash:w:$@:i $(AVRDUDE_WRITE_EEPROM) 
	rm $@
