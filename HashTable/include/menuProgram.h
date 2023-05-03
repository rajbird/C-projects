/**
 * Rajbir Deol
 * 0918139
*/
#ifndef __RDEOL_MENUPROGRAM__
#define __RDEOL_MENUPROGRAM__
#include "hash.h"

/**
 * Pre-conditions: Pass in valid file name
 * Post-conditions: none
 */
void menuStart(char * file);

/**
 * Pre-conditions: Pass in valid file name
 * Post-conditions: returns pointer to list wth stored file
 */
Node * dataStore(char * dataFile);

/**
 * Pre-conditions: Pass in pointer to list
 * Post-conditions: returns pointer to hash table with stored list
 */
HTable * loadFile( Node * theList);

/**
 * Pre-conditions: Pass in pointer to hash table and list
 * Post-conditions: Stores new entry in linked list and hash table
 */
void newEntry(HTable * map, Node * theList);

/**
 * Pre-conditions: Pass in pointer to hash table and list
 * Post-conditions: Finds number and prints name associated with number
 */
void checkNum(Node * theList, HTable * map);
#endif