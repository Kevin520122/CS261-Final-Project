/***********************************************************
* Author: Garrett R. Scott
* Email: 
* Date Created: 
* Filename: bst.c
*
* Solution description: Implementation of a Binary Search Tree 
* that can store any arbitrary struct in its nodes.
************************************************************/
 

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "bst.h"
#include "structs.h"

/* ************************************************************************
	BST Functions
************************************************************************ */

/**************************************************************
* Entry: None
*
* Exit: Pointer to dynamically allocated tree returned.
* 		count set to 0 and root set to NULL.
*
* Purpose: Allocates and initializes the BST
*
***************************************************************/
struct BSTree* newBSTree()
{
	struct BSTree* tree= (struct BSTree*)malloc(sizeof(struct BSTree)); 
	assert(tree != NULL);

	tree->count = 0;
	tree->root = NULL;
	return tree;
}
/**************************************************************
* Entry: Current node to be freed.
*
* Exit: Recursively frees nodes on left and right until no more
*
* Purpose: Helper function to delete all nodes in the tree
*
***************************************************************/
void _freeNodes(struct Node *current)
{
	if (current != NULL) {
		_freeNodes(current->left);
		_freeNodes(current->right);
		free(((struct items*)current->value));
		free(current);
	}
}
/**************************************************************
* Entry: Needs binary search tree myTree.
*
* Exit: Calls recursive helper and deallocates tree
*
* Purpose: Deallocate nodes in BST and deallocate the BST structure
*
***************************************************************/
void deleteBSTree(BSTree* myTree)
{
	assert(myTree != NULL);
	_freeNodes(myTree->root);
	myTree->root = NULL;
	myTree->count = 0;
	free(myTree);
}

/**************************************************************
* Entry: Needs binary search tree myTree.
*
* Exit: Returns integer if tree is empty
*
* Purpose: Returns "1" if the  BST is empty or "0" if not 
*
***************************************************************/
int isEmptyBSTree(BSTree* myTree)
{
	assert(myTree != NULL);
	return myTree->count == 0;
}

/**************************************************************
* Entry: Needs binary search tree myTree.
*
* Exit: Returns # of nodes
*
* Purpose: Returns the size of the BST
*
***************************************************************/
int sizeBBSTree(BSTree* myTree)
{
	assert(myTree != NULL);
	return myTree->count;
}
/**************************************************************
* Entry: Needs current node and value to insert.
*
* Exit: Recursively allocates new node
*
* Purpose: Recursive helper function to add nodes
*
***************************************************************/
struct Node* _addNode(struct Node* current, TYPE value)
{
	if(current == NULL)
	{
		struct Node* newNode = (struct Node *)malloc(sizeof(struct Node));
		assert(newNode != NULL);
		//newNode->value = (struct item*)value; Error here 
		//Should use the heap
		newNode->value = (struct items*)malloc(sizeof(struct items));
		((struct items*)newNode->value)->name = ((struct items*)value)->name;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
	if (compare(value, current->value) == 1) 
		current->right = _addNode(current->right, value);
	else
		current->left = _addNode(current->left, value);

	return current;
}
/**************************************************************
* Entry: Needs binary search tree myTree and value to insert.
*
* Exit: New node allocated and count increasec
*
* Purpose: Adds an element into the BST
*
***************************************************************/
void addBSTree(BSTree* myTree, TYPE value)
{
	assert(myTree != NULL);
	myTree->root = _addNode(myTree->root, value);
	myTree->count++;
}
/**************************************************************
* Entry: Needs binary search tree myTree and value to find.
*
* Exit: Returns integer if value is found
*
* Purpose: Returns "1" if the BST contains the specified element or "0" if not
*
***************************************************************/
int containsBSTree(BSTree* myTree, TYPE value)
{
	assert(myTree != NULL);
	struct Node *current = myTree->root;    
	while (current != NULL) { 
		if(compare(value, current->value) == 0)
            return 1; 
        else if (compare(value, current->value) == 1) 
            current = current->right; 
        else
            current = current->left; 
    } 
    return 0;
}
/**************************************************************
* Entry: Needs binary search tree myTree
*
* Exit: Returns leftmost value in BST
*
* Purpose: Returns the minimum value in the BST 
*
***************************************************************/
TYPE minBSTree(BSTree* myTree)
{
	struct Node* leftMost = myTree->root;
	while (leftMost->left != NULL)
		leftMost = leftMost->left;
	return leftMost->value;
}
/**************************************************************
* Entry: Needs binary search tree myTree
*
* Exit: Returns rightmost value in BST
*
* Purpose: Returns the maximum value in the BST 
*
***************************************************************/
TYPE maxBSTree(BSTree* myTree)
{
	struct Node* rightMost = myTree->root;
	while (rightMost->right != NULL)
		rightMost = rightMost->right;
	return rightMost->value;
}
/**************************************************************
* Entry: Needs node of subtree
*
* Exit: Returns leftmost value in BST
*
* Purpose: Returns the leftmost value in the BST 
*
***************************************************************/
char* _leftMostChild(struct Node * current) {
	while (current->left != NULL)
		current = current->left;
	return ((struct items*)current->value)->name;
}
/**************************************************************
* Entry: Needs node of subtree
*
* Exit: Deallocates leftmost value in BST
*
* Purpose: Removes the leftmost value in the BST 
*
***************************************************************/
struct Node* _removeLeftmostChild (struct Node *current) 
{
	if (current == NULL) { return NULL; }
	if (current->left != NULL)
	{
		current->left = _removeLeftmostChild(current->left);
		return current;
	}
	else {
		struct Node* tmp = current->right;
		free(current->value);
		current->value = NULL;
		free(current);
		current = NULL;
		return tmp;
	}
}
/**************************************************************
* Entry: Needs node of subtree and value
*
* Exit: Deallocates node in BST
*
* Purpose: Recursive helper function to remove nodes
*
***************************************************************/
struct Node* _removeNode(struct Node* current, TYPE value)
{
	if(current == NULL)
		return current;
	if(compare(value, current->value) == 0)
	{
		if(current->right == NULL)
		{
			struct Node* tmp = current->left;
			free(current->value);
			current->value = NULL;
			free(current);
			current = NULL;
			return tmp;	
		}
		((struct items*)current->value)->name = _leftMostChild(current->right);
		current->right = _removeLeftmostChild(current->right);
	}
	else if (compare(value, current->value) == 1) 
		current->right = _removeNode(current->right, value); 
	else
		current->left = _removeNode(current->left, value); 

	return current;
}
/**************************************************************
* Entry: Needs tree and value
*
* Exit: Deallocates node in BST
*
* Purpose: Remove the specific element from the BST
*
***************************************************************/
void removeBSTree(BSTree *tree, TYPE value)
{
	assert(tree != NULL);
	tree->root = _removeNode(tree->root, value);
	tree->count--;
}
/**************************************************************
* Entry: Needs subtree node
*
* Exit: Prints node value
*
* Purpose: Recursive helper function to print nodes
*
***************************************************************/
void _printNode(struct Node *current) {
	if (current == NULL) return;
	_printNode(current->left);	 
	print_type(current->value);
	_printNode(current->right);
}
/**************************************************************
* Entry: Needs binary search tree
*
* Exit: Prints node value
*
* Purpose: Prints the values in the BST.
*
***************************************************************/
void printBSTree(BSTree* myTree)
{
	assert(myTree != NULL);
	if (myTree->count == 0) { return; }
	_printNode(myTree->root);	 
}