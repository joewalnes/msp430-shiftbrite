.PHONY: all clean install

CC = msp430-gcc
CXX = msp430-g++
CFLAGS = -Os -Wall -g -mmcu=msp430x2012 -I../../..
CXXFLAGS = $(CFLAGS)
PROG=main

OBJS=$(PROG).o ../../../shiftbrite.o

all: $(PROG).elf $(PROG).lst
	msp430-size $(PROG).elf

$(PROG).elf: $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG).elf $(OBJS)

%.lst: %.elf
	msp430-objdump -DS $< >$@

clean:
	rm -fr *.elf *.lst *.o

install: $(PROG).elf
	mspdebug rf2500 "prog $(PROG).elf"
