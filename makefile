CC = gcc
CFLAGS = -Wall -g

disassemble: disassemble.o process.o read.o
	$(CC) $(CFLAGS) -o dissassemble disassemble.o process.o read.o

process.o: processOpts2.c processOpts2.h
	$(CC) $(CFLAGS) -c processOpts.c

disassemble.o: disAssemble.c processOpts2.h
	$(CC) $(CFLAGS) -c disAssemble.c
	
read.o: readMipsFile.c processOpts2.h functCodes.h opCodes.h structs.h
	$(CC) $(CFLAGS) -c readMipsFile.c

clean:
	/bin/rm *.o