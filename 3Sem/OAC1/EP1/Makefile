CC = gcc
# CFLAGS = -Wall -std=c99
CFLAGS = -std=c99
FILENAME = example

all: build run

build: EP1

EP1: EP1.c driverEP1.c
	$(CC) $(CFLAGS) -o EP1 EP1.c driverEP1.c

run: EP1
	./EP1 ${FILENAME}.mem ${FILENAME}.out

exem2: build EP1
	./EP1 movRegAcc.mem ${FILENAME}.out

clean:
	rm -f EP1
