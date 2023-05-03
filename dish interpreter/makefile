#
#	Makefile for dish interpreter
#
EXE	= dish
BINDIR = bin/
SRC = src/
INC = -Iinclude
OBJS = \
	$(BINDIR)dish_main.o \
	$(BINDIR)dish_run.o \
	$(BINDIR)dish_tokenize.o

CFLAGS = -g

$(EXE) : dish_main
	$(CC) $(CFLAGS) -o $(EXE) $(INC) $(OBJS)

dish_main: dish_run
	$(CC) $(CFLAGS) -c -o $(BINDIR)dish_main.o  $(INC) $(SRC)dish_main.c

dish_run: dish_tokenize
	$(CC) $(CFLAGS) -c -o $(BINDIR)dish_run.o  $(INC) $(SRC)dish_run.c

dish_tokenize:
	$(CC) $(CFLAGS) -c $(SRC)dish_tokenize.c $(INC) -o $(BINDIR)dish_tokenize.o


clean :
	- rm -f $(EXE)
	- rm -f $(BINDIR)*.o
	- rm -f tags


# ctags makes a database of source code tags for use with vim and co
tags ctags : dummy
	- ctags *.c

# a rule like this dummy rule can be use to make another rule always
# run - ctags depends on this, so therefore ctags will always be
# executed by "make ctags" as make is fooled into thinking that it
# has performed a dependency each time, and therefore re-does the work
dummy :
