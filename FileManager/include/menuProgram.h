/**
 * Rajbir Deol
 * 0918139
*/
#ifndef __RDEOL_MENU_PROGRAM__
#define __RDEOL_MENU_PROGRAM__

#include "binTree.h"
#include "fileStruct.h"
#include "dirStore.h"


/*************
 * OPERATIONS
 *************/
/**
 * Pre-conditions: Pass in valid directory path
 * Post-conditions: none
 */
void menu(char * dirPath);

/**
 * Pre-conditions: Name of file/directory to search, pointer to BinTree, and 
 * 1 to print out search results and 0 not to.
 * Post-conditions: Mallocs memory for interger pointer contining number of
 * search results. Caller has to free pointer.
 */
int * search(char * data, Tree * tree, int print);

/**
 * Pre-conditions: Valid pointer to tree node
 * Post-conditions: Prompts user for file information, deletes file from 
 * directory and from BinTree.
 */
void deleteFile(Tree * tree);

/**
 * Pre-conditions: Valid pointer to tree node
 * Post-conditions: Prompts user for file information, renames file in
 * directory and in BinTree.
 */
void renameFile(Tree * tree);

/**
 * Pre-conditions: Valid pointer to tree node
 * Post-conditions: Prompts user for file information, moves file in 
 * directory and in BinTree.
 */
void moveFile(Tree * tree);


/**********
 * HELPERS
 **********/

/**
 * Pre-conditions: Name of file/directory to search, pointer to BinTreeNode, 1 
 * to print out search results and 0 not to and pointer to store number of 
 * search results.
 * Post-conditions: Recursively searches tree for data
 */
void searchTree(char * data, TreeNode * root, int print, int * dups);

/**
 * Pre-conditions: Valid pointers to strings. The str pointer contains the string
 * in which the orig substring is to be replaced with rep string.
 * Post-conditions: Mallocs memory for string, caller has to free memory
 */
char * replaceStr(char * str, char * orig, char * rep);

/**
 * Pre-conditions: Name of file/directory to search, pointer to BinTreeNode, 1 
 * to print out search results and 0 not to and 1 to check if directory and
 * 0 otherwise.
 * Post-conditions: Recursively searches tree for data, stores result in path
 */
void searchPath(char * data, TreeNode * root, char * path, int dir);
#endif