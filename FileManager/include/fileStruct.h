/**
 * Rajbir Deol
 * 0918139
*/
#ifndef __RDEOL_FILE_STRUCT__
#define __RDEOL_FILE_STRUCT__

#include "binTree.h"

typedef struct FileInfo{
    char * name;
}File;

#define PTR (File *)

/*
 * Pre Conditions: Takes in values to store in struct
 * Post Conditions: Returns struct with filled out data
 */
File * createEntry(char * name);

/*
 * Pre Conditions: Takes in two structs to compare files
 * Post Conditions: Returns 1, -1, and 0 depending on which file in alphabetically first
 */
int compareFile(void * data, void * path);

/*
 * Pre Conditions: Takes pointer to file struct to free memory
 * Post Conditions: Struct and data in struct are freed
 */
void destroyFile(void * toDie);

/*
 * Pre Conditions: Takes in pointer to file struct to print
 * Post Conditions: none
 */
void printFile(void * data);
#endif