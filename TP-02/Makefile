.PHONY: all 
#.SECONDARY:

ifneq ($(KERNELRELEASE),)

  obj-m := helloWorld.o helloWorldParam.o

else
	
  #KERNELDIR ?= /lib/modules/$(shell uname -r)/build
  KERNELDIR ?=~/Cave/linux
  PWD := $(shell pwd)

all :
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	make -C $(KERNELDIR) M=$(PWD) clean

cleanall:clean
	rm -f *~

endif

