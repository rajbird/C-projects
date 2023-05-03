#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>

#include "storeRoom.h"
#include "game.h"

/**
 * main
 * Main check if a data file was provided. It then parses the data file, and stores the data in 
 * room structs, by calling readinRoom. It then stores the return in a pointer to a pointer to 
 * an array of room structs. The pointer is then passed to gameLoop, which is where the user 
 * spends its time playing the game. 
 * IN: Commandline argument
 * OUT: return 0
 * ERROR: If datafile not formatted correctly their will be errors, which are fixed when 
 * the data file is fixed.
 */
int main(int argc, char* argv[]) {
	if (argc != 2){
		printf("Not all arguments were provided, please try again\n");
	} 
	else {
		Room** ptrToRm;
		ptrToRm = readinRoom(argv[1]);
		gameLoop(ptrToRm);

	}

	return 0;
	
}
