/**
 * Rajbir Deol
 * 0918139
 */ 
#include <stdlib.h>
#include <stdio.h>

#include "linkedList.h"
#include "stack.h"

int main(){
    Stack * aStack = create();

    //Test functions with valid and NULL stack
    push(aStack, -5, 5, '#');
    push(NULL, -5,5, '#');
    printf("pushed: c:# -5,5 with valid and invalid stacks\n");

    printf("Stack: ");
    printList(aStack->top);

    if(peek(NULL) == '`'){
        printf("Peek returns character of top element: %c\n", peek(aStack));
    }
    
    pop(NULL);
    printf("Pop element\n");
    pop(aStack);

    printf("Stack: ");
    printList(aStack->top);

    destroy(NULL);
    destroy(aStack);
    printf("Destroying valid and invalid stacks\n");

    printf("Test: individual function, with valid and NULL values\nTest: PASSED\n\n");

    // Simple stack with 10 elements, test basic usage of each function
    Stack * iStack = create();
    int array[9] = {1,2,3,4,5,6,7,8,9};
    char arrayCh[9] = {'a','b','c','d','e','f','g','h','i'};

    printf("initialized stack using create, populate stack using push\n");
    for(int i=0; i<9; i++){
        push(iStack, array[i], array[i+2], arrayCh[i]);
    }

    printf("Stack: ");
    printList(iStack->top);
    printf("Peek @ element: %c\nPop element\n", peek(iStack));
    pop(iStack);

    printf("Stack: ");
    printList(iStack->top);
    destroy(iStack);
    printf("successfully freed stack\n");
    printf("Test: functions using a basic stack\nTest: PASSED\n\n");

    /** 
     * Starting stack has 17 elements, 3 extra are added and 7 are removed
     * Elements in this stack are more complex
     */
    Stack * iAmStack = create();
    int newArr[17] = {-23,567,275478,3,6,1980843564,-1234567890,-84,67,32,-37854,-78,69,402,14,-21,69};
    int charArr[17] = {'q','s','g','i','8','$','^','*','E','j','>','d','B','+','$','9','0'};
    
    printf("initialized stack using create, populate stack using push\n");
    for(int i=0; i<17; i++){
        push(iAmStack, newArr[i], i,charArr[i]);
    }

    printf("Initialized Stack: \n");
    printList(iAmStack->top);
    printf("Peek @ element: %c\n", peek(iAmStack));

    // Adds 3 elements to stack in this order 9, 24, -425 
    printf("Adding 3 elements with '&' character\n");
    push(iAmStack, 0, 17, '&');
    push(iAmStack, 24, 18, '&');
    push(iAmStack, -425, 19, '&');

    printf("Stack w/ 3 elements added: \n");
    printList(iAmStack->top);

    // Pops 7 elements from stack
    printf("\nRemoving 7 elements from stack, using pop and peek(to look at char): \n");
    for(int i=0; i<7; i++){
        printf("Pop element: %c\n", peek(iAmStack));
        pop(iAmStack);
    }
    printf("Stack w/ 7 elements removed: \n");
    printList(iAmStack->top);
    
    destroy(iAmStack);
    printf("successfully freed stack\n");
    printf("Test: functions using a complex stack\nTest: PASSED\n\n");

	return 0;
}
