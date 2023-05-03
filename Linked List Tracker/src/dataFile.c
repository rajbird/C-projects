#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"
#include "dataFile.h"

Food* dataStore(char* dataFile){
	FILE* dfp;
	dfp = fopen(dataFile, "r");
	if(dfp == NULL){
		printf("Data file couldn't be opened\n");
	}

	Food* head = NULL;
	char line[115];
	while (fgets(line, 115, dfp) != NULL){
		int len;
		len = strlen(line);
		if(line[len - 1] == '\n' && len > 1){
			Food* add; 
			add = dataParse(len, line);
			if(add->type == 'j'){
				head = addToBack(head, add);
			}
			else if(add->type == 'h'){
				head = addToFront(head, add);
			}
			else{
				printf("Type: %c isn't healthy(h) or junk(j)\n", add->type);
			}

		}
	}
	fclose(dfp);
	return head;

}

Food* dataParse(int len, char line[len]){
	char* name, * group, * token;

	name = malloc(sizeof(char) * 50);
	group = malloc(sizeof(char) * 50);
	if(name == NULL || group == NULL){
		printf("Mallco failed\n");
	}
	
	token = strtok(line, ",");

	int calor, count = 0;
	char type;
	while(token != NULL){
		if(count == 0){
			strcpy(name, token);
		}
		else if(count == 1){
			strcpy(group, token);
		}
		else if(count == 2){
			calor = atoi (token);
			if(calor < 0){
				printf("Calories is less than 0\n");
			}
		}
		else{
			type = token[0];
		}
    	count++;
      	token = strtok(NULL, ",");
	}

	Food* new;
	new = createRecord(name, group, calor, type);
	free(name);
	free(group);

	return new;
}