#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "storeRoom.h"
#include "loadRooms.h"

Room** readinRoom(char* dataFile){
	Room** room;
	char line[150];
	int rmCount = -1;

	FILE* ifp;
	ifp = fopen(dataFile, "r");

	if (ifp == NULL){
		printf("File: %s does not exist, exit and try again\n", dataFile);
	}

	room = malloc(sizeof(Room*) * 6);
	if (room == NULL){
		printf("Malloc failed; program will self destruct in 3\n 2\n 1\n\n");
	}

	while (fgets(line, 150, ifp) != NULL){
		int len;
		len = strlen(line);
		rmCount++;
		if(rmCount < 6){
			room[rmCount] = storeElements(len, line, rmCount);
		}
		else {
			printf("There are more than 6 room in data file, I only stored first 6\n");
		}
		
		
	}
	fclose(ifp);
	toScreen(room);
	return room;
}

Room* storeElements(int len, char line[len], int rmNum){
	Room* rm;
	char elements[] = ("hzagGwWmMep");
	char valuables[] = ("wWgGe");
	int numItems = 0;
	int numDoors = 0;

	rm = malloc(sizeof(Room));
	if (rm == NULL){
		printf("Malloc failed; program will self destruct in 3\n 2\n 1\n\n");
	}

	char dimn[2] = {' ',' '};
	if (line[2] == 'X'){
		dimn[0] = line[0];
		dimn[1] = line[1];
		rm->rowLen = atoi (dimn);

		dimn[0] = line[3];
		dimn[1] = line[4];
		rm->colLen = atoi (dimn);

	}
	else if (line[1] == 'X'){
		rm->rowLen = atoi (&line[0]);
		dimn[0] = line[2];
		dimn[1] = line[3];
		rm->colLen = atoi (dimn);
	}
	else {
		printf("\nThe first element in the file is not the dimensions\nWhy you do that man\n\n");
	}

	int monstas = 0;
	for(int i = 0; i<len; i++){
		if (numItems < 10){
			char num[2] = {' ',' '};
			if (line[i] =='d'){
				numDoors++;
				rm->item[numItems].type = (line[i]);
				if(line[i+1] == 'n'){
					rm->item[numItems].value = 4;
				    rm->item[numItems].row = 0;
				    if(line[i+3] == ' '){
				    	num[1] = line[i+2];
				    	rm->item[numItems].col = atoi (num);
				    	i += 2;
				    }
				    else {
				    	num[0] = line[i+2];
				    	num[1] = line[i+3];
				    	rm->item[numItems].col = atoi (num);
				    	i += 3;
				    }
				} 
				else if(line[i+1] == 'e'){
					rm->item[numItems].value = 1;
					rm->item[numItems].col = rm->colLen + 1;
					if(line[i+3] == ' '){
				    	num[1] = line[i+2];
				    	rm->item[numItems].row = atoi (num);
				    	i += 2;
				    }
				    else {
				    	num[0] = line[i+2];
				    	num[1] = line[i+3];
				    	rm->item[numItems].row = atoi (num);
				    	i += 3;
				    }
				} 
				else if(line[i+1] == 's'){
					rm->item[numItems].value = 3;
					rm->item[numItems].row = rm->rowLen + 1;
					if(line[i+3] == ' '){
				    	num[1] = line[i+2];
				    	rm->item[numItems].col = atoi (num);
				    	i += 2;
				    }
				    else {
				    	num[0] = line[i+2];
				    	num[1] = line[i+3];
				    	rm->item[numItems].col = atoi (num);
				    	i += 3;
				    }
				} 
				else if(line[i+1] == 'w'){
					rm->item[numItems].value = 2;
					rm->item[numItems].col = 0;					
					if(line[i+3] == ' '){
				    	num[1] = line[i+2];
				    	rm->item[numItems].row = atoi (num);
				    	i += 2;
				    }
				    else {
				    	num[0] = line[i+2];
				    	num[1] = line[i+3];
				    	rm->item[numItems].row = atoi (num);
				    	i += 3;
				    }
				} 
				numItems++;
			} 
			else if(strchr(elements, line[i])) {
				if(strchr(valuables, line[i])) {
					rm->item[numItems].type = line[i];
					srand(time(NULL));
					if (line[i] == 'g'){
						rm->item[numItems].value = rand() % 50;
					}
					else if (line[i] == 'G'){
						rm->item[numItems].value = rand() % 200 + 50;
					}
					else if (line[i] == 'w'){
						rm->item[numItems].value = rand() % 9 + 1;
					}
					else if (line[i] == 'W'){
						rm->item[numItems].value = rand() % 15 + 10;
					}
					else{
						rm->item[numItems].value = rand() % 20;
					}
				}
				else if(strchr ("mM", line[i])){
					rm->item[numItems].type = line[i];
					monstas++;
				}
				else{
					rm->item[numItems].type = line[i];
				}
				
				if (line[i+2] == ','){
					rm->item[numItems].row = atoi (&line[i+1]);
					num[0] = line[i+3];
					num[1] = line[i+4];
					rm->item[numItems].col = atoi (num);
					i += 3;
				}
				else{
					num[0] = line[i+1];
					num[1] = line[i+2];
					rm->item[numItems].row = atoi (num);

					num[0] = line[i+4];
					num[1] = line[i+5];
					rm->item[numItems].col = atoi (num);
					i += 4;

				}
				numItems++;
			}
		}
		else {
			printf("No no no, there are more than 10 elements in room: %d\nI only stored the first 10\n", rmNum + 1);
			i = len;
		}
	}

	rm->door = numDoors;
	rm->mon = monstas;
	return rm;
}


