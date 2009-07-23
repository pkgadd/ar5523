# fallback to the kernel source
KSRC ?= /lib/modules/$(shell uname -r)/build

# Each configuration option enables a list of files.
CONFIG_AR5523		?= m

#EXTRA_CFLAGS += -DDEBUG

obj-$(CONFIG_AR5523)	+= ar5523.o

all:
	$(MAKE) -C $(KSRC) SUBDIRS=$(PWD) modules

clean:
	rm -rf	*.ko *.mod.* *.o .*.o.d .*.cmd .tmp_versions Module.symvers \
		*.order ar5523-snapshot.tar.gz

distclean: clean
	rm -rf cscope.* *~

dist: distclean
	tar \
		--format=posix \
		--owner=root \
		--numeric-owner \
		--exclude-vcs \
		--exclude=debian \
		--exclude=ar5523-snapshot\\.tar\\.gz \
		-czf ar5523-snapshot.tar.gz .
