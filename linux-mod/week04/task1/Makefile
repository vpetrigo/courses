MODULE_NAME := solution
obj-m =	$(addsuffix .o,$(MODULE_NAME))
ccflags-y := -DDEBUG -std=gnu11

PWD := $(shell pwd)
KDIR := /lib/modules/`uname -r`/build

all:
	make -C $(KDIR) M=$(PWD)

clean:
	make -C $(KDIR) M=$(PWD) clean
