obj-m += mm_alloc.o

PWD := $(CURDIR)

all:
	make -C /lib/modules/$(shell uname -r)/build	M=$(PWD)

clean:
	make -C /lib/modules/$(shell uname -r)/build	M=$(PWD)	clean
