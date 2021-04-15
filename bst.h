// Binary search tree (BST) interface.

#ifndef BST_H
#define BST_H 1

# ifndef TYPE
# define TYPE	void*
# endif

/* ************************************************************************
	Compare and print function prototypes
************************************************************************ */

int compare(TYPE left, TYPE right);			// Compares two TYPE values and returns -1 if left < right, 0 if Left = right and 1 if left is > then right.
											// Define this in your compare.c file

void print_type(TYPE curval);				// Prints TYPE values, define this in your compare.c file

struct Node
{
	TYPE         value;
	struct Node* left;
	struct Node* right;
};

typedef struct BSTree
{
	struct Node* root;
	int          count;
} BSTree;


/* ************************************************************************
	BST Interface
************************************************************************ */

BSTree* newBSTree();						// Allocates and initializes the BST
void deleteBSTree(BSTree* myTree);				// Deallocate nodes in BST and deallocate the BST structure
int isEmptyBSTree(BSTree* myTree);				// Returns "1" if the BST is empty or "0" if not 
int sizeBBSTree(BSTree* myTree);				// Returns the size of the BST
void addBSTree(BSTree* myTree, TYPE value);		// Adds an element into the BST
int containsBSTree(BSTree* myTree, TYPE value);	// Returns "1" if the BST contains the specified element or "0" if not
TYPE minBSTree(BSTree* myTree);					// Returns the minimum value in the BST 
TYPE maxBSTree(BSTree* myTree);					// Returns the maximum value in the BST  
void removeBSTree(BSTree *tree, TYPE value);	// Remove the specific element from the BST
void printBSTree(BSTree* myTree);				// Prints the values in the BST. Define this in your compare.c file


# endif
