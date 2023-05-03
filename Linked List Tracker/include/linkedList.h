#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

/**
 * struct and functions that work directly on the struct
 * The struct functions and definition could be in their
 * own .c and .h files (and sometimes should be).
 * For the purposes of this assignment, leave the struct
 * definition here
 */


/**
 * Food_List Struct
 */
struct Food{
 char * name;
 char * foodGroup;
 int calories;
 char type;
 struct Food * next;
};

typedef struct Food Food;


/*******************
 * Struct Functions
 *******************/

/**
 * createRecord
 * Allocates memory for a food struct, and initalizes it's members to the
 * supplied parameters.
 * ->next is set to NULL.
 * The value for name and group are copied into new memory, the passed in
 * strings should be destroyed
 * Returned record should be destroyed with destroyRecord()
 * @param  name     String (<50 length)
 * @param  group    String (<50 length)
 * @param  calories int (>0)
 * @param  theType  char (h for healthy, or j for junk)
 * @return          Food* to malloc'd memory
 *                  NULL on failure
 */
Food * createRecord(char * name, char * group, int calories, char theType);


/**
 * printRecord
 * Returns allocated memory containing a string filled with Food data in the
 * following format:
 * Name (Food Group):calories[type]
 * Note: The string should not contain a newline.
 * The string memory is allocated in this function and must be freed by the
 * caller.
 * @param  toPrint Food* (not NULL)
 * @return         char* to malloc'd memory
 *                 NULL on failure
 */
char * printRecord(Food * toPrint);


/**
 * destroyRecord
 * Frees memory associated with a Food* record
 * Note: This function also frees the internal variables
 * @param toDie Address to memory that should be freed (not NULL)
 */
void destroyRecord(Food * toDie);


/*****************
 * List Functions
 *****************/
 /**
  * Notes:
  * - NULL represents an empty list, and should be handled gracefully
  */

/**
 * addToFront
 * Takes a pointer to the list, and a created Food* record
 * Adds record to the front of the list
 * In the event theList is NULL, it's assumed that the list is empty
 * and toBeAdded becomes a new list with one element
 * Returns the head of the list after the operation is performed
 * @param  theList   Food* representing the head of the list
 * @param  toBeAdded Food* to add to the front of the list
 * @return           Food* new head of the list
 */
Food * addToFront(Food * theList, Food * toBeAdded);


/**
 * addToBack
 * Takes a pointer to the head of the list, and a created Food* record
 * Adds record to the tail of the list
 * In the event theList is NULL, it's assumed that the list is empty
 * and toBeAdded becomes a new list with one element
 * Returns the head of the list after the operation is performed
 * @param  theList   Food* representing the head of the list
 * @param  toBeAdded Food* to add to the front of the list
 * @return           Food* new head of the list
 */
Food * addToBack(Food * theList, Food * toBeAdded);


/**
 * removeFromBack
 * Takes a pointer to the head of the list. Removes the front
 * item from the list. Does not free the memory for
 * the item removed. You will need to have previously gotten it
 * with getFirstItem, so that you can free it after removal.
 * @param  theList Food* representing the head of the list
 * @return         Food* new head of the list
 */
Food * removeFromFront(Food * theList);


/**
 * removeFromBack
 * Takes a pointer to the head of the list. Removes the last
 * item from the list. Does not free the memory for
 * the item removed. You will need to have previously gotten it
 * with getLastItem, so that you can free it after removal.
 * @param  theList Food* representing the head of the list
 * @return         Food* new head of the list
 */
Food * removeFromBack(Food * theList);


/**
 * getLastItem
 * Takes a pointer to the head of the list. Returns the last item in the list.
 * Does not remove the item from the list. Do not destroy the record until
 * it is removed from the list.
 * @param  theList Food* representing the head of the list
 * @return         Food* last item in the list.
 */
Food * getLastItem(Food * theList);


/**
 * getFirstItem
 * Takes a pointer to the head of the list. Returns the first item in the list.
 * Does not remove the item from the list. Do not destroy the record until
 * it is removed from the list.
 * @param  theList Food* representing the head of the list
 * @return         Food* first item in the list.
 */
Food * getFirstItem(Food * theList);


/**
 * isEmpty
 * Takes a pointer to a list, and checks if it's empty
 * @param  theList Food* representing the head of the list
 * @return         1 if list is empty
 *                 0 if list has elements
 */
int isEmpty(Food * theList);


/**
 * printList
 * Takes a pointer to the head of the list. Prints each element to stdout,
 * following the format specified for printRecord seperated by newlines.
 * @param theList Food* representing head of the list
 */
void printList(Food * theList);


/**
 * Takes a pointer to the list and frees the memory for each struct in the list.
 * @param theList Food* representing head of the list
 */
void destroyList(Food * theList);

#endif
