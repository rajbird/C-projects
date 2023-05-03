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

SOURCE = $(SRCDIR)linkedList.c $(SRCDIR)A1main.c  $(SRCDIR)stack.c $(SRCDIR)mazeSolver.c

#The list of object files is below.  The object file names here must match the file names of your source code 
# except with .o instead of .c.   Make changes as appropriate


OBJS    = $(BINDIR)linkedList.o $(BINDIR)A1main.o $(BINDIR)stack.o $(BINDIR)mazeSolver.o


#The names of the binary programs that will be produced.  
#
PROGNAME = $(BINDIR)A1runnable


default : link testMain

link: linkedList stack mazeSolver A1main 
	$(CC) $(LIBDIRS) $(LDFLAGS) -o $(PROGNAME) $(OBJS) $(LIBS)

testMain: stack linkedList
	$(CC) $(CFLAGS) $(SRCDIR)testMain.c $(INCLUDES) -o $(BINDIR)test $(BINDIR)linkedList.o $(BINDIR)stack.o

linkedList:
	$(CC) $(CFLAGS) -c $(SRCDIR)linkedList.c $(INCLUDES) -o $(BINDIR)linkedList.o

stack:
	$(CC) $(CFLAGS) -c $(SRCDIR)stack.c $(INCLUDES) -o $(BINDIR)stack.o

mazeSolver:
	$(CC) $(CFLAGS) -c $(SRCDIR)mazeSolver.c $(INCLUDES) -o $(BINDIR)mazeSolver.o

A1main:
	$(CC) $(CFLAGS) -c $(SRCDIR)A1main.c $(INCLUDES) -o $(BINDIR)A1main.o

clean:
	@ rm -f *.o
