/**
 * Rajbir Deol
 * 0918139
*/
#ifndef __RDEOL_DIR_STORE__
#define __RDEOL_DIR_STORE__

#include "binTree.h"
#include "fileStruct.h"

/**
 * Pre-conditions: Pointer to directory path, and pointer to BinTree
 * Post-conditions: Recursiviely stores directories and subdirectories
 * into the BinTree
 */
void parseDirectory(char * dir, Tree * root);

/**
 * Pre-conditions: Pointer to current directory path and name of newDir
 * Post-conditions: Returns 2 if newDir = ".." or ".", returns 1 if
 * newDir is a directory, and returns 0 is not a directory
 */
int checkIfDir(char * path, char * newDir);

/**
 * Pre-conditions: Pointer to current and new directory path
 * Post-conditions: Returns the full path to a file or directory
 */
char * pathName(char * currDir, char * newDir);
#endif