CFLAGS = -g -Wall -Wstrict-prototypes
PROGS = nt-serial nt-parallel
LDFLAGS = -lm
CC = gcc
MCC = mpicc

all: $(PROGS)

nt-serial: nt-serial.o
	$(MCC) $(LDFLAGS) -o nt-serial nt-serial.o

nt-parallel: nt-parallel.o
	$(MCC) $(LDFLAGS) -o nt-parallel nt-parallel.o

nt-serial.o: nt-serial.c
	$(MCC) $(CFLAGS) -c nt-serial.c

nt-parallel.o: nt-parallel.c
	$(MCC) $(CFLAGS) -c nt-parallel.c
	
clean:
	rm -f $(PROGS) *.o core* 
