/**
 * Rajbir Deol
 * 0918139
 */
#ifndef __RDEOL_LINKEDLIST__
#define __RDEOL_LINKEDLIST__

#define DATA (char*)
#define VAL (*(long long *)
struct listNode{
	void * data;
	void * value;
	struct listNode * next;
};

typedef struct listNode Node;

/**
 * Pre-conditions: Pass in valid pointers to data and value
 * Post-conditions: Stores values in node and returns it
 */
Node * createNode(void * data, void * value);

/**
 * Pre-conditions: Pass in valid pointer of node to add and head of the list
 * Post-conditions: Return 0 if node inserted correctly
 */
int insert(Node * toAdd, Node * temp);

/**
 * Pre-conditions: Pass in pointer of node to add and head of the list
 * Post-conditions: Returns head of list, with new node added
 */
Node * addNode(Node * toAdd, Node * head);

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

/**
 * Pre-conditions: Pass in pointer to head of the list
 * Post-conditions: Destroys list and data stored in list
 */
void destroyList(Node * toDie);

#endif