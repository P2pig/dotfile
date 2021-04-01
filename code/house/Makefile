#Makefile
#device.c gpio25.c gpio2.c gpio5.c gpio6.c LDV7.c main.c socket.c

CC=gcc
CFLAGS=-lwiringPi -pthread

prog:
	$(CC) device.c gpio25.c gpio2.c gpio5.c gpio6.c LDV7.c main.c socket.c $(CFLAGS)
clean:
	rm a.out

