#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedList.h"

Food * createRecord(char * name, char * group, int calories, char theType){
	Food* f = malloc(sizeof(Food));
	
	if(f == NULL){
		printf("Malloc failed\n");
		free(f);
		return NULL;
	}

	f->name = malloc(sizeof(char) * 51);
	f->foodGroup = malloc(sizeof(char) * 51);

	if(f->name == NULL || f->foodGroup == NULL){
		printf("Malloc failed\n");
		destroyRecord(f);
		return NULL;
	}

	if( strlen(name) < 50 && strlen(group) < 50  && calories > 0 && (theType == 'j' || theType == 'h')){
		strcpy(f->name, name);
		strcpy(f->foodGroup, group);

		f->calories = calories;
		f->type = theType;
		f->next = NULL;
		return f;
	}

	destroyRecord(f);
	return NULL;
}

char * printRecord(Food * toPrint){
	char* foodData = malloc(sizeof(char) * 120);
	if(foodData == NULL){
		printf("malloc failed\n");
		return NULL;
	}
	sprintf(foodData, "%s (%s):%d[%c]", toPrint->name, toPrint->foodGroup, toPrint->calories, toPrint->type);
	return foodData;
}


void destroyRecord(Food * toDie){
	free(toDie->name);
	free(toDie->foodGroup);
	free(toDie);
}



 /**
  * Notes:
  * - NULL represents an empty list, and should be handled gracefully
  */

Food * addToFront(Food * theList, Food * toBeAdded){
	if(theList != NULL && toBeAdded != NULL){
		toBeAdded->next = theList;
		return toBeAdded;
	}
	else if(toBeAdded == NULL){
		return theList;
	}
	else{
		return toBeAdded;
	}
}

Food * addToBack(Food * theList, Food * toBeAdded){
	Food* temp;
	temp = theList;
	if(theList != NULL && toBeAdded != NULL){
		if(theList->next == NULL){
			theList->next = toBeAdded;
		}
		else{
			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = toBeAdded;
		}
		return theList;
	}
	else if(toBeAdded == NULL){
		return theList;
	}
	else{
		return toBeAdded;
	}
		
}

Food * removeFromFront(Food * theList){
	if(theList != NULL){
		return theList->next;

	}
	return NULL;
}


Food * removeFromBack(Food * theList){
	Food* temp;
	temp = theList;
	if(theList != NULL){
		Food* prev;
		while(temp->next != NULL){
			prev = temp;
			temp = temp->next;
		}
		if(temp->next == NULL){
			prev->next = NULL;	
		}
		return theList;
	}
	return NULL;
		
}

Food * getLastItem(Food * theList){
	Food* temp;
	temp = theList;
	if(theList != NULL){
		while(temp->next != NULL){
			temp = temp->next;
		}
		if(temp->next == NULL){
			return temp;	
		}
	}
	return NULL;
		
}

Food * getFirstItem(Food * theList){
	if(theList != NULL){
		return theList;
	}
	return NULL;
	
}

int isEmpty(Food * theList){
	if(theList != NULL){
		return 0;
	}

	return 1;
}


void printList(Food * theList){
	Food* temp;
	temp = theList;
	if(theList != NULL){
		while(temp->next != NULL){
			printf("%s (%s):%d[%c]\n", temp->name, temp->foodGroup, temp->calories, temp->type);
			temp = temp->next;
		}
		if(temp->next == NULL){
			printf("%s (%s):%d[%c]\n", temp->name, temp->foodGroup, temp->calories, temp->type);
		}
	}
}


void destroyList(Food * theList){
	Food* temp;
	Food* head = theList;
	while ((temp = head) != NULL) { 
	    destroyRecord(temp);
	    head = head->next;
	}
}