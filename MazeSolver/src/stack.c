/**
 *Rajbir Deol
 *0918139
 */
#include <stdlib.h>
#include <stdio.h>

#include "linkedList.h"
#include "stack.h"

Stack * create(){
    Stack * s;
    s = malloc(sizeof(Stack));
    if(s == NULL){
        printf("Malloc failed\n");
        free(s);
        return NULL;
    }

    s->top = createNode(-1, -1, 'D');
    return s;
}

void destroy(Stack * theStack){
    if(theStack != NULL){
        destroyList(theStack->top);
        free(theStack);	
    }   
}

void push(Stack * theStack, int xCoor, int yCoor, char type){
    if(theStack != NULL){
    	Node * newNode;
    	newNode = createNode(xCoor, yCoor, type);
        theStack->top = addToFront(theStack->top, newNode);
    }
}

void pop(Stack * theStack){
    if(theStack != NULL){
        Node * topVal;
    	topVal = getFirst(theStack->top);
        theStack->top = removeFront(theStack->top);
        free(topVal);
    }
}

char peek(Stack * theStack){
    if(theStack != NULL){
        return theStack->top->c; 
    }
    return '`';
}
