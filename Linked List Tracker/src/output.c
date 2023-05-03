#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"
#include "output.h"

void atEnd(Food* theList){
	Food* temp;
	temp = theList;
	int total = 0;
	
	if(temp->next == NULL){
		total = temp->calories;
	}
	else{
		while(temp->next != NULL){
			total += temp->calories;
			temp = temp->next;
		}
		if(temp->next == NULL){
			total += temp->calories;
		}
	}
		
	
	printf("%d\n", total);
	printf("%.2f\n", caloriesAvg("vegfruit", theList) );
	printf("%.2f\n", caloriesAvg("meat", theList) );
	printf("%.2f\n", caloriesAvg("dairy", theList) );
	printf("%.2f\n", caloriesAvg("grain", theList) ); 
	printf("%.2f\n", caloriesAvg("fat", theList) );
	printf("%d\n", listLength(theList) ); 
	printList(theList);
	destroyList(theList);
}

float caloriesAvg(const char* foodType, Food* theList){
	Food* temp;
	temp = theList;
	float sum = 0, count = 0;

	while(temp->next != NULL){
		if(strstr(temp->foodGroup, foodType)){
			count++;
			sum += temp->calories;
		}
		temp = temp->next;
	}
	if(temp->next == NULL && (strstr(temp->foodGroup, foodType))){
		count++;
		sum += temp->calories;
	}
		

	if(count == 0){
		return 0;
	}

	return sum/count;
}

int listLength(Food* theList){
	Food* temp;
	temp = theList;
	int len = 0;

	while(temp->next != NULL){
		len++;
		temp = temp->next;
	}
	if(temp->next == NULL){
		len++;
	}
	return len;
}