/**
 * Rajbir Deol
 * 0918139
 */ 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"
#include "menuProgram.h"

int main(int argc, char* argv[]){
	if (argc != 2){
		printf("Not all arguments were provided, please try again\n");
	}
	else{
		menuStart(argv[1]);
	}
	return 0;
}