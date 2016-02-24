#CC := arm-eabi-gcc
CC := arm-linux-gnueabi-gcc
obj-m	:= ar0134.o



KDIR	:= /home/ippuu/linux

PWD	:= $(shell pwd)

default:
#	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	make -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.ko
	rm -rf *.mod.*
	rm -rf .*.cmd
	rm -rf *.o
	rm -rf *.order
	rm -rf *.symvers
	clear
