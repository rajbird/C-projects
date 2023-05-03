/**
 *Rajbir Deol
 *0918139
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

Node * createNode(void * data, void * value){
    Node * n = malloc(sizeof(Node));
    if(n == NULL){
        free(n);
        return NULL;
    }
    
    n->data = data;
    n->value = value;
    n->next = NULL;
    return n;
}

int insert(Node * toAdd, Node * temp){
    if(temp->next == NULL || (strcmp( DATA toAdd->data, DATA temp->next->data)) <= 0){
        toAdd->next = temp->next;
        temp->next = toAdd;
        return 0;
    }
    else{
        return insert(toAdd, temp->next);
    }

}

Node * addNode(Node * toAdd, Node * head){
    if(head == NULL && toAdd != NULL){
        return toAdd;
    }
    else if(toAdd == NULL){
        return head;
    }
    else if((strcmp( DATA toAdd->data, DATA head->data)) <= 0){
        toAdd->next = head;
        return toAdd; 
    }
    else if((insert(toAdd, head)) == 0){
        return head;
    }
    else{
        return toAdd;
    }
}

void printList(Node * theList){
    Node* temp;
    temp = theList;
    if(theList != NULL){
        while(temp != NULL){
            printf("%s, %lld\n", DATA temp->data, VAL temp->value));
            temp = temp->next;
        }
    }
}

int listLength(Node* theList){
    int len = 0;
    Node* temp = theList;

    if(theList == NULL){
        return len;
    }

    while(temp != NULL){
        len++;
        temp = temp->next;
    }
    return len;
}

void destroyList(Node * toDie){
	Node* temp;
	Node* head = toDie;
	while ((temp = head) != NULL) { 
        free(temp->data);
        free(temp->value);
        free(temp);
	    head = head->next;
	}
}