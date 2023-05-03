/**
 * Rajbir Deol
 * 0918139
 */
#ifndef __RDEOL_LINKEDLIST__
#define __RDEOL_LINKEDLIST__

struct listNode{
	int x;
	int y;
	char c;
	struct listNode * next;
};

typedef struct listNode Node;

/**
 * Pre-conditions: Pass a valid interger value
 * Post-conditions: Stores values in node and returns it
 */
Node * createNode(int xCoor, int yCoor, char type);

/**
 * Pre-conditions: Pass in pointer to head of the list
 * Post-conditions: none
 */
void destroyList(Node * toDie);

/**
 * Pre-conditions: Pass in pointer to head of list, and pointer to node to be added
 * Post-conditions: Returns new head of list
 */
Node * addToFront(Node * theList, Node * toBeAdded);

/**
 * Pre-conditions: Pass in pointer to head of list
 * Post-conditions: Return first node in list
 */
Node * getFirst(Node * theList);

/**
 * Pre-conditions: Pass in pointer to head of list
 * Post-conditions: Return pointer to head of list
 */
Node * removeFront(Node * theList);

/**
 * Pre-conditions: Pass in pointer to head of list
 * Post-conditions: none
 */
void printList(Node * theList);

/**
 * Pre-conditions: Pass in pointer to head of list
 * Post-conditions: Return number of nodes in list
 */
int listLength(Node* theList);

#endif