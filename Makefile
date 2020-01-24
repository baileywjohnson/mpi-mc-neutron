CFLAGS = -g -Wall -Wstrict-prototypes
PROGS = nt-serial nt-parallel
LDFLAGS = -lm
CC = gcc
MCC = mpicc

all: $(PROGS)

nt-serial: nt-serial.o functions.o
	$(MCC) $(LDFLAGS) -o nt-serial nt-serial.o functions.o

nt-parallel: nt-parallel.o functions.o
	$(MCC) $(LDFLAGS) -o nt-parallel nt-parallel.o functions.o

nt-serial.o: nt-serial.c
	$(MCC) $(CFLAGS) -c nt-serial.c

nt-parallel.o: nt-parallel.c
	$(MCC) $(CFLAGS) -c nt-parallel.c

functions.o: functions.c functions.h
	$(MCC) $(CFLAGS) -c functions.c

clean:
	rm -f $(PROGS) *.o core* 
