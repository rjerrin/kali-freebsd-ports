CC?=gcc
CFLAGS+=-W -Wall -Wextra  -fstack-protector-all
DFLAGS=-D_FORTIFY_SOURCE=2 -I /usr/local/include -I src/headers
LDFLAGS=-Wl,-z,relro,-z,now,-L,/usr/local/lib,-lcurl,-lpthread
DIR=src/
DIROUT=bin/
DIR_HEADERS=src/headers/


all:   $(DIR)0d1n.c 
	$(CC) $(CFLAGS) $(DFLAGS) -c $(DIR)*.c 
	$(CC)  -o 0d1n *.o  $(LDFLAGS)


