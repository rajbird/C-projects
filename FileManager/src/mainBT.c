/**
 *Rajbir Deol
 *0918139
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "binTree.h"

#define DATA (*(int*)

int compare(void * dataX, void * dataY);
void destroy(void * data);
void printNode(void * data);

int main(){
	printf("NOTE: Destroy function has nothing to destroy, so prints '?' instead\n");
	srand(time(NULL));
	printf("-------------------->1st Test<--------------------\n");
    int arr[9] = {45,12,31,76,49,98,80,56};
    Tree * tree = createBinTree(&compare, &destroy);
    printf("Initialized Tree\n");
    
    printf("Set-up tree in order: 1 2 3 4 5\n");
    for(int i=0;i<9;i++){
    	addToTree(tree, &arr[i]);
    }
    
    printf("SUCCESS\nPrint InOrder: \n");
    printInOrder(tree->root, &printNode);
    printf("\nLevel Order\n");
    printLevelOrder(tree->root, &printNode);

    printf("Removing 2 from tree, new in order should be: 1 3 5 4\n");
    removeFromTree(tree, &arr[1]);
    printInOrder(tree->root, &printNode);
    printf("\nLevel Order\n");
    printLevelOrder(tree->root, &printNode);

    destroyBinTree(tree->root, tree->destroy);
    free(tree);
    printf("Destroy Tree: SUCCESS\n");

    printf("\n-------------------->2nd Test<--------------------\n\n");

    tree = NULL;
    int array[15];
    tree = createBinTree(&compare, &destroy);
    printf("Initialized 2nd Tree\n");
    
    printf("Set-up tree with 15 nodes\nData: ");
    int r;
    for(int i=0;i<15;i++){
        r = rand() % 200;
        printf("%d ", r);
        array[i] = r;
    	addToTree(tree, &array[i]);
    }
    printf("SUCCESS\nPrint InOrder: \n");
    printInOrder(tree->root, &printNode);
    printf("\nLevel Order\n");
    printLevelOrder(tree->root, &printNode);

    printf("\nRemoving %d and %d from tree\n", array[7], array[3]);
    removeFromTree(tree, &array[7]);
    removeFromTree(tree, &array[3]);
    printf("SUCCESS\nPrint InOrder: \n");
    printInOrder(tree->root, &printNode);
    printf("\nLevel Order\n");
    printLevelOrder(tree->root, &printNode);

    destroyBinTree(tree->root, tree->destroy);
    free(tree);
    printf("Destroy Tree: SUCCESS\n");

    printf("\n-------------------->3rd Test<--------------------\n\n");
    tree = NULL;
    tree = createBinTree(&compare, &destroy);

    addToTree(NULL, NULL);
    addToTree(tree, NULL);
    addToTree(NULL, &array[3]);
    printInOrder(tree->root, &printNode);
    printf("Test addToTree with NULL: SUCCESS\n");
    printf("Test printInOrder with NULL: SUCCESS\n");

    removeFromTree(NULL, NULL);
    removeFromTree(tree, NULL);
    removeFromTree(NULL, &array[3]);
    printLevelOrder(tree->root, &printNode);
    printf("Test removeFromTree with NULL: SUCCESS\n");
    printf("Test printLevelOrder with NULL: SUCCESS\n");

    destroyBinTree(NULL, &destroy);
    printf("Test destroyBinTree with NULL: SUCCESS\n");
    free(tree);
}

int compare(void * dataX, void * dataY){
    if( DATA dataX) > DATA dataY)){
    	return 1;
    }
    else if( DATA dataX) < DATA dataY)){
    	return -1;
    }
    return 0;
}

void destroy(void * data){
	printf("?");
}

void printNode(void * data){
	if(data != NULL){
		printf("%d ", (*(int*)data));
	}
    
}