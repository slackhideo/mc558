# programa
PROG=maycon
PROGAUX=minheap

# compilador
CC=gcc

# flags para o compilador
CFLAGS=-Wall -g

all: $(PROG)

$(PROG): $(PROGAUX).o $(PROG).o
	$(CC) -o $(PROG) $(PROGAUX).o $(PROG).o 

$(PROGAUX).o: $(PROGAUX).c
	$(CC) -c $(CFLAGS) $(PROGAUX).c 

$(PROG).o: $(PROG).c
	$(CC) -c $(CFLAGS) $(PROG).c 

clean:
	rm -rf *.o *~ $(PROG)
