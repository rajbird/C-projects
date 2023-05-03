/**
 *Rajbir Deol
 *0918139
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

Node * createNode(int xCoor, int yCoor, char type){
    Node * n;
    n = malloc(sizeof(Node));
    if(n == NULL){
        printf("Malloc failed\n");
        free(n);
        return NULL;
    }
    
    n->c = type;
    n->x = xCoor;
    n->y = yCoor;
    n->next = NULL;

    return n;
}

void destroyList(Node * toDie){
	Node* temp;
	Node* head = toDie;
	while ((temp = head) != NULL) { 
	    free(temp);
	    head = head->next;
	}
}

Node * addToFront(Node * theList, Node * toBeAdded){
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

Node * getFirst(Node * theList){
    if(theList != NULL){
        return theList;
    }

    return NULL;
}

Node * removeFront(Node * theList){
    if(theList != NULL){
        return theList->next;
    }

    return NULL;
}

int listLength(Node* theList){
    int len = 0;
    Node* temp;
    temp = theList;

    if(theList == NULL){
        return len;
    }

    while(temp != NULL){
        len++;
        temp = temp->next;
    }
    return len;
}

void printList(Node * theList){
    Node* temp;
    temp = theList;
    int count = 0;
    if(theList != NULL){
        while(temp != NULL){
            printf("%c: %d,%d;  ", temp->c, temp->x, temp->y);
            if(count == 7){
                printf("\n");
                count = 0;
            }
            temp = temp->next;
            count++;
        }
        printf("\n");
    }
}
