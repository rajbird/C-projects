/**
 * Rajbir Deol
 * 0918139
*/
#ifndef __RDEOL_BIN_TREE__
#define __RDEOL_BIN_TREE__

struct BinTreeNode{
    void * data;
    struct BinTreeNode * left;
    struct BinTreeNode * right;
};

typedef struct BinTreeNode TreeNode;
typedef void * TreeData;
typedef int bool;
enum {false, true};

typedef struct BinTree{
	int (*compare) (TreeData data1, TreeData data2);
	void (*destroy) (TreeData);
    TreeNode * root;
}Tree;

//Binary Tree = BT

/*********************
 * WRAPPER FUNCTIONS *
 *********************/

/**
 * Pre-conditions: Valid compare and destroy function pointers are passed in
 * Post-conditions: Creates a Binary Tree(BT)
 */
Tree * createBinTree(int (*comparePtr) (TreeData data1, TreeData data2), void (*destroyPtr) (TreeData));

/**
 * Pre-conditions: Pointer to root of the BT and destroy function ptr 
 * Post-conditions: Recursively frees BT node
 * NOTE: Actually Binary Tree struct is not freed, binary tree should be freed
 * after calling this function. Like so, 
 *                                       destroyBinTree(tree, &destroy);
 *                                       free(tree);
 */
 void destroyBinTree(TreeNode * toDie, void (*destroyPtr) (TreeData));

/**
 * Pre-conditions: Valid ptr to BT and ptr to data
 * Post-conditions: Adds data to Binary Tree, no duplicates
 */
 void addToTree(Tree * theTree, void * data);

/**
 * Pre-conditions: Valid ptr to BT and ptr to data
 * Post-conditions: Rearranges  BT
 */
 void removeFromTree(Tree * theTree, void * data);


/********************
 * HELPER FUNCTIONS *
 ********************/

/**
 * Pre-conditions: Valid data ptr
 * Post-conditions: Creates tree node with data
 */
 TreeNode * createTreeNode(TreeData data);

/**
 * Pre-conditions: Valid ptr to treeNode, data, and compare function 
 * Post-conditions: Inserts data, balancing by using the compare function and returns root node
 */
 TreeNode * insertTreeNode(TreeNode * root, TreeData data, int (*comparePtr) (TreeData data1, TreeData data2));

/**
 * Pre-conditions: Valid ptr to treeNode, data, and compare function 
 * Post-conditions: Removes data, returns root node
 */
 TreeNode * deleteTreeNode(TreeNode * root, TreeData data, int (*comparePtr) (TreeData data1, TreeData data2), void (*destroyPtr) (TreeData));

/**
 * Pre-conditions: Valid ptr to tree node
 * Post-conditions: Returns true if tree node has two children, otherwise returns false
 */
 bool hasTwoChildren(TreeNode * root);

/**
 * Pre-conditions: Valid ptr to tree node
 * Post-conditions: Returns minimum value in tree
 */
 TreeNode * findMinimum(TreeNode * root);

/**
 * Pre-conditions: Valid ptr to tree node
 * Post-conditions: Returns height of tree node
 */
 int height(TreeNode * theTree);


/******************* 
 * PRINT FUNCTIONS *
 *******************/

/**
 * Pre-conditions: Valid ptr to tree node and print function
 * Post-conditions: Prints tree using In Order traversal
 */
 void printInOrder(TreeNode * root, void (* printNode) (TreeData data));

/**
 * Pre-conditions: Valid ptr to tree node and print function
 * Post-conditions: Prints tree using Level Order traversal
 */
 void printLevelOrder(TreeNode* root, void (* printNode) (TreeData data));

/**
 * Pre-conditions: Valid ptr to tree node and print function, also the level to be printed
 * Post-conditions: Prints indivdual level of tree
 */
 void printLevel(TreeNode * root, int level, void (* printNode) (TreeData data));
#endif