# Makefile for interruptDemo

#sources = $(wildcard keypad16_a[0-4].c)
sources = int.c 

obj-m += $(sources:.c=.o)

mods =  $(sources:.c=.ko)

LKM_DIR=/lib/modules/$(shell uname -r)/build

all: $(mods)

%.ko: %.c
	make -C ${LKM_DIR} M=$(PWD) modules

clean:
	make -C ${LKM_DIR} M=$(PWD) clean


