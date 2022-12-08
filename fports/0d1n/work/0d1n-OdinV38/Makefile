CC?=cc
CFLAGS=-W -Wall -Wextra -O2 -fstack-protector-all 
DFLAGS=-D_FORTIFY_SOURCE=2 -I /usr/local/include -I src/headers
LDFLAGS=-Wl,-z,relro,-z,now,-L,/usr/local/lib,-lcurl,-lpthread 
DIR=src/
DIROUT=bin/
DIR_HEADERS=src/headers/

+all: $(DIR)0d1n.c 
	$(CC) $(CFLAGS) $(DFLAGS) -c $(DIR)*.c 
	$(CC)  -o 0d1n *.o  $(LDFLAGS)

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
