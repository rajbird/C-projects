/**
 *Rajbir Deol
 *0918139
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fileStruct.h"

File * createEntry(char * name){
	File* f = malloc(sizeof(File));
	
	if(f == NULL){
		printf("Malloc failed\n");
		free(f);
		return NULL;
	}

	f->name = malloc(sizeof(char) * strlen(name)+1);

	if(f->name == NULL){
		printf("Malloc failed\n");
		destroyFile(f);
		return NULL;
	}

	if( strlen(name) < 50){
	    strcpy(f->name, name);
	    return f;
	}

	return NULL;
}

int compareFile(void * data, void * path){
    int compare = strcmp(((File *)data)->name, ((File *)path)->name);
    if(compare > 0){
        return 1;
    }
    else if(compare < 0){
        return -1;
    }
    else{
    	return 0;
    }
}

void destroyFile(void * toDie){
	if(toDie != NULL){
	    free((PTR toDie)->name);
	    free((PTR toDie));
	}
}

void printFile(void * data){
	if(data != NULL && ((File *) data)->name != NULL){
	    printf("%s\n", ((File *) data)->name);
	}
}