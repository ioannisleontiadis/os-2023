obj-m += hello_world.o

PWD := $(CURDIR)

all:
	make -C /lib/modules/`uname -r`/build  M=$(PWD)

clean:
	make -C /lib/modules/`uname -r`/build M=$(PWD) clean
