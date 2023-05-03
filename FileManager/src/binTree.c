/**
 *Rajbir Deol
 *0918139
 */
#include <stdlib.h>
#include <stdio.h>

#include "binTree.h"


Tree * createBinTree(int (*comparePtr) (TreeData data1, TreeData data2), void (*destroyPtr) (TreeData)){
    Tree * t = malloc(sizeof(Tree));
    if(t == NULL){
        printf("Malloc failed\n");
        free(t);
    }

    t->compare = comparePtr;
    t->destroy = destroyPtr;
    t->root = NULL;
    return t;
}

void destroyBinTree(TreeNode * toDie, void (*destroyPtr) (TreeData)){
	if(toDie != NULL){
        destroyPtr(toDie->data);
        destroyBinTree(toDie->left, destroyPtr);
        destroyBinTree(toDie->right, destroyPtr);
        free(toDie);
    }
}

void addToTree(Tree * theTree, void * data){
	if(theTree != NULL && data != NULL){
		theTree->root = insertTreeNode(theTree->root, data, theTree->compare);
	}
}

void removeFromTree(Tree * theTree, void * data){
    if(theTree != NULL && data != NULL){
    	theTree->root = deleteTreeNode(theTree->root, data, theTree->compare, theTree->destroy);
    }
}

TreeNode * createTreeNode(void * data){
    TreeNode * n = malloc(sizeof(TreeNode));
    if(n == NULL){
        printf("Malloc failed\n");
        free(n);
    }

    n->left = NULL;
    n->right = NULL;
    n->data = data;
    return n;
}

TreeNode * insertTreeNode(TreeNode * root, TreeData data, int (*comparePtr) (TreeData data1, TreeData data2)){
    if(root == NULL){
        TreeNode * temp = createTreeNode(data);
        return temp;
    }
    if(comparePtr(root->data, data) < 0){
        root->right = insertTreeNode(root->right, data, comparePtr);
    }
    else if(comparePtr(root->data, data) > 0){
        root->left = insertTreeNode(root->left, data, comparePtr);
    }
    return root;
}

TreeNode * deleteTreeNode(TreeNode * root, TreeData data, int (*comparePtr) (TreeData data1, TreeData data2), void (*destroyPtr) (TreeData)){
    TreeNode * temp;
    if(root == NULL){
        return root;
    }
    else if(comparePtr(root->data, data) > 0){
        root->left = deleteTreeNode(root->left, data, comparePtr, destroyPtr);
    }
    else if(comparePtr(root->data, data) < 0){
        root->right = deleteTreeNode(root->right, data, comparePtr, destroyPtr);
    }
    else{
        if(hasTwoChildren(root) == true){
        	temp = findMinimum(root->right);
            destroyPtr(root->data);
            root->data = temp->data;
            root->right = deleteTreeNode(root->right, temp->data, comparePtr, destroyPtr);
        }
        else{
            temp = root;
            if (root->left == NULL) {
                root = root->right;
            }
            else if (root->right == NULL) {
                root = root->left;
            }
            destroyPtr(temp->data);
            free(temp);
        }
    }
    return root;
}

bool hasTwoChildren(TreeNode * root){
	if(root != NULL){
		if(root->left != NULL && root->right != NULL){
			return true;
		}
	}
	return false;
}

TreeNode * findMinimum(TreeNode * root){
    if(root != NULL){
    	if(root->left != NULL){
    	    return findMinimum(root->left);
    	}
    }
    return root;
}

void printInOrder(TreeNode * root, void (* printNode) (TreeData data)){
    if(root == NULL)
        return;
    else{
        printInOrder(root->left, printNode);
        printNode(root->data);
        printInOrder(root->right, printNode);
    }
}

int height(TreeNode * root){
    if (root == NULL){
   	    return 0;
    }
    else{
   	    int leftH = height(root->left);
   	    int rightH = height(root->right);

   	    if(leftH > rightH){
   	    	return 1 + leftH;
   	    }
        else{
        	return 1 + rightH;
        } 
    }
}

void printLevelOrder(TreeNode* root, void (* printNode) (TreeData data)){
    if(root != NULL){
        int h = height(root);
        for (int i=0; i<h; i++){
        	printf("L:%d --> ", i);
        	printLevel(root, i, printNode);
        	printf("\n");
        }	
    }
    
}

void printLevel(TreeNode * root, int level, void (* printNode) (TreeData data)){
    if (root == NULL){
    	return;
    }
    if (level == 0){
    	printNode(root->data);
    }
    else if (level > 0){
        printLevel(root->left, level-1, printNode);
        printLevel(root->right, level-1, printNode);
    }
}