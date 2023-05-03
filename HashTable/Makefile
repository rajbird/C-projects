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

SOURCE = $(SRCDIR)linkedList.c $(SRCDIR)A2main.c  $(SRCDIR)menuProgram.c $(SRCDIR)hash.c

#The list of object files is below.  The object file names here must match the file names of your source code 
# except with .o instead of .c.   Make changes as appropriate


OBJS    = $(BINDIR)linkedList.o $(BINDIR)A2main.o $(BINDIR)menuProgram.o $(BINDIR)hash.o 


#The names of the binary programs that will be produced.  
#
PROGNAME = $(BINDIR)A2runnable


default : link test

link: linkedList hash menuProgram A2main
	$(CC) $(LIBDIRS) $(LDFLAGS) -o $(PROGNAME) $(OBJS) $(LIBS)

linkedList:
	$(CC) $(CFLAGS) -c $(SRCDIR)linkedList.c $(INCLUDES) -o $(BINDIR)linkedList.o

hash:
	$(CC) $(CFLAGS) -c $(SRCDIR)hash.c $(INCLUDES) -o $(BINDIR)hash.o

menuProgram:
	$(CC) $(CFLAGS) -c $(SRCDIR)menuProgram.c $(INCLUDES) -o $(BINDIR)menuProgram.o

A2main:
	$(CC) $(CFLAGS) -c $(SRCDIR)A2main.c $(INCLUDES) -o $(BINDIR)A2main.o

test: hash
	$(CC) $(CFLAGS) $(SRCDIR)testMain.c $(INCLUDES) -o $(BINDIR)test $(BINDIR)hash.o

clean:
	@ rm -f *.o
