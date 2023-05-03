/**
 *Rajbir Deol
 *0918139
 */
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h> 

#include "dirStore.h"

void parseDirectory(char * directory, Tree * root){
    DIR           *d;
    struct dirent *dir;
    d = opendir(directory);
    if(d){
    	while ((dir = readdir(d)) != NULL){
            char * path = pathName(directory, dir->d_name);
            int check = checkIfDir(path, dir->d_name);
            if(check == 0){
            	File * add = createEntry(path);
            	addToTree(root, add);
            }
            else if(check == 1){
            	File * add = createEntry(path);
            	addToTree(root, add);
            	parseDirectory(path, root);
            }
            free(path);
        }
        closedir(d);
    }
}

int checkIfDir(char * path, char * newDir){
    if (strcmp(newDir, "..") == 0 || strcmp(newDir, ".") == 0){
        return 2;
    }
 
    DIR* dir = opendir(path);
	if(dir){
	    closedir(dir);
	    return 1;
	}
    return 0;
}

char * pathName(char * currDir, char * newDir){
	int currLen, newLen;
    currLen = strlen(currDir);
    newLen = strlen(newDir);

    char * temp = malloc(sizeof(char) * (currLen + newLen + 2));
    if(temp == NULL){
        printf("malloc failed\n");
        return NULL;
    }

    strcpy(temp,currDir);
    strncat(temp,"/",1);
    strncat(temp,newDir,newLen);

    return temp;
}