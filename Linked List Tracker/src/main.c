#include <stdlib.h>
#include <stdio.h>

#include "linkedList.h"
#include "dataFile.h"
#include "output.h"

/**
 * main
 * Checks if command line argument was provided, if so calls 
 * functions to store data, and print ending stuff
 * IN: command line arguments
 * OUT: 0
 */
int main(int argc, char* argv[]){
	if (argc != 2){
		printf("Not all arguments were provided, please try again\n");
	}
	else{
		Food* ptr;
		ptr = dataStore(argv[1]);
		atEnd(ptr);
	}

	return 0;
}



