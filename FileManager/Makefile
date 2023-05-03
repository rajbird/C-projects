CC          =	gcc
# Flags that are sent to the compiler
# Do not change these
CFLAGS      =	-Wall -std=c99 -pedantic -g
LDFLAGS     =	

#Directories where the compiler can find things
INCLUDES    = -Iinclude
LIBDIRS     = 
LIBS        = 

# add directory names here if you want to separate files by directories
BINDIR = bin/
SRCDIR = src/

#Put the names of your source code file in the lines below.  

SOURCE = $(SRCDIR)binTree.c $(SRCDIR)A3main.c $(SRCDIR)fileStruct.c $(SRCDIR)dirStore.c $(SRCDIR)menuProgram.c  

#The list of object files is below.  The object file names here must match the file names of your source code 
# except with .o instead of .c.   Make changes as appropriate


OBJS    = $(BINDIR)binTree.o $(BINDIR)A3main.o $(BINDIR)fileStruct.o $(BINDIR)dirStore.o $(BINDIR)menuProgram.o  


#The names of the binary programs that will be produced.  
#
PROGNAME = $(BINDIR)A3runnable


default : link test

link: binTree fileStruct dirStore menuProgram A3main
	$(CC) $(LIBDIRS) $(LDFLAGS) -o $(PROGNAME) $(OBJS) $(LIBS)

binTree:
	$(CC) $(CFLAGS) -c $(SRCDIR)binTree.c $(INCLUDES) -o $(BINDIR)binTree.o

fileStruct:
	$(CC) $(CFLAGS) -c $(SRCDIR)fileStruct.c $(INCLUDES) -o $(BINDIR)fileStruct.o

dirStore:
	$(CC) $(CFLAGS) -c $(SRCDIR)dirStore.c $(INCLUDES) -o $(BINDIR)dirStore.o

menuProgram: 
	$(CC) $(CFLAGS) -c $(SRCDIR)menuProgram.c $(INCLUDES) -o $(BINDIR)menuProgram.o

A3main:
	$(CC) $(CFLAGS) -c $(SRCDIR)A3main.c $(INCLUDES) -o $(BINDIR)A3main.o

test: binTree
	$(CC) $(CFLAGS) $(SRCDIR)mainBT.c $(INCLUDES) -o $(BINDIR)test $(BINDIR)binTree.o

clean:
	@ rm -f *.o

