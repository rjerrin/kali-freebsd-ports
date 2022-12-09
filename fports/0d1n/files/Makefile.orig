CC=gcc
CFLAGS=-W -Wall -Wextra -Wformat-security -Wno-maybe-uninitialized -O2
HARDENING=-fstack-protector-all -pie -fPIE
DIR=src/
DIROUT=bin/
DIR_HEADERS=src/headers/
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LDFLAGS=-Wl,-lcurl, -lpthread
else
	LDFLAGS=-Wl,-z,relro,-z,now -lcurl -lpthread
endif



0d1n: $(DIR)0d1n.c 
	$(CC) $(CFLAGS) $(HARDENING) -c $(DIR)*.c -I$(DIR_HEADERS)
	$(CC) $(HARDENING)  -o $(DIROUT)0d1n *.o  $(LDFLAGS)

clean:
	rm -f *.o 0d1n

PREFIX=/usr/local
install:
	make
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install -m 0755 bin/0d1n $(DESTDIR)$(PREFIX)/bin
	mkdir /opt/0d1n
	mkdir /opt/0d1n/view/
	mkdir /opt/0d1n/view/response_sources
	mkdir /opt/0d1n/payloads
	cp -rf templates /opt/0d1n/
	cp -rf tables /opt/0d1n/view/
	cp -rf payloads /opt/0d1n/
	chmod 0755 -R /opt/0d1n
	chown ${USER} -R /opt/0d1n
	chown ${USER} $(DESTDIR)$(PREFIX)/bin/0d1n

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/0d1n
	rm -rf /opt/0d1n
	rm -f *.o 0d1n
