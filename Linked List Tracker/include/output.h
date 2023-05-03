#ifndef __RDEOL_OUTPUT__
#define __RDEOL_OUTPUT__

/**
 * atEnd
 * Prints information to screen at end, by counting total caloriies
 * and calling functions to help do other things need to quit program
 * IN: Pointer to the head of linked list
 * OUT: void
 */
void atEnd(Food* theList);

/**
 * caloriesAvg
 * Calculates the group average
 * IN: A const char for the foodGroup name A stringPointer to the 
 * head of linked list
 * OUT: Average calories of food group
 */
float caloriesAvg(const char* foodType, Food* theList);

/**
 * listLength
 * Calculate the length of the list
 * IN: Pointer to the head of linked list
 * OUT: int value that represtent list length
 */
int listLength(Food* theList);

#endif