obj-m += pit.o

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	rm -rf *.order *.symvers *.ko *.mod.c *.o
