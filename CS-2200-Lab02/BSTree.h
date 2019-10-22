//--------------------------------------------------------------------
// Laboratory 9    										BSTree.h
/*!-------------------------------------------------------------------
	\file 
    \brief Header file for BSTree

	Class declarations for the linked implementation of the Binary
    Search Tree ADT -- including the recursive helpers of the
    public member functions
*/
//--------------------------------------------------------------------

#pragma once

#include <stdexcept>
#include <iostream>
#include <fstream>		// Taking information from a file
#include <vector>		// Vector array in database.cpp
#include <string>		// For names
#include <algorithm>    // std::max

using namespace std;

/*! 
	\brief Main structure of binary search tree
	
	This class is responsible for the skeleton of the binary search tree
	with functions specific to modifty or reading the tree using linked lists.
	
	@param DataType : Tree data item.
	
	@param KeyType : Key for search tree.
*/
template < typename DataType, class KeyType >		
class BSTree										
{
public:
	/// Defualt constructor. Assigns root to nullptr.
	BSTree();     
	
	///  Copy constructor
	/*! 
		Passes a refrence to assign the copy to obj.
		@param obj : A refrence to another BSTree.
	*/ 
	BSTree(const BSTree&);  
	
	/// Overloaded assignment operator
	/*! 
		Forces the compiler to make a copy of object by passing a copy
		and then assigning the copy to the current object.
		@param rObj : The right object to assign to the current object.
	*/ 
	const BSTree& operator= (const BSTree);  

	/// Destructor which deletes the entire tree
	/*! 
		This function calls deleteHelper.
		
		After this it deletes root.
	*/ 
	~BSTree();


	// Binary search tree manipulation operations
	
	/// Insert data item with a given key
	/*! 
		First tests whether the tree is empty or not.
		
		If the tree is empty assign the node to root.
		
		Else traverse the tree to find the correct position.
		Go right if the node is bigger than the current node or 
		left if the node is smaller until it has reached a leaf position. 
		
		If the key already exists, then we just update the dataItem.
		
		@param newDataItem : A refrence to a DataType that gets assigned to the new node.
		newDataItem already has a key assigned to it.
	*/ 
	void insert(const DataType& newDataItem); 
	
	///  Retrieve data item and assign the result to the refrence passed
	/*! 
		First test the root if its null in main. If so we stop.
		
		Else traverse the tree to find the correct node.
		Go right if the node is bigger than the current node or 
		left if the node is smaller until we either:
		
		Find the exact key and return true
		
		OR
		
		Hit null, meaning that we did not find it, returning false.
		
		@param searchKey : The key to search for.
		@param searchDataItem : The reference object passed
		which is accessable to main.
	*/ 
	bool retrieve(const KeyType& searchKey, DataType& searchDataItem) const;
	
	/// Removing a node
	/*! 
		First tests to see if the node exists. 
		
		If so we call the removeHelper and return true
		
		Else, simply return false
		
		@param deleteKey : The key of the node to delete.
	*/ 
	bool remove(const KeyType& deleteKey);     
	
	/// Output all keys in ascending order
	/*! 
		Calls he printHelper function
	*/
	void writeKeys() const;       
	
	/// Clear the entire tree and it's nodes
	/*! 
		Calls the deleteHelper
		
		Assigns the root to null
	*/ 
	void clear();                                

	// Binary search tree status operations
	/// Tests to see if tree points to null
	bool isEmpty() const;                        

	/// Output the tree structure -- used in testing/debugging
	/*! 
		Tests to see if root is null
		
		Calls the showHelper function
	*/ 
	void showStructure() const;


	// In-lab operations
	
	
	/// Height of tree
	/*! 
		Calls he getHeightHelper function
	*/
	int getHeight() const;   
	
	/// Number of nodes in tree
	/*! 
		Tests to see if root is null
		
		Calls the getCountHelper function and passes 
		sum as a parameter. 
		
		Then returns sum.
		@param sum : The number of nodes in the tree.
	*/ 
	int getCount() const;			

protected:


	/*! 
		\brief Inner class, facilitator for the BSTree class.
		
		BSTreeNode are the individual nodes that the class contians.
		
		Each object has a genertic DataType which can contain a 
		refrence to a database for faster searches. 
		
		@param nodeDataItem : Tree data item.
		@param leftPtr : Pointer to the left node.
		@param rightPtr : Pointer to the right node
	*/
	class BSTreeNode                  
	{
	public:

		/// Constructor which receives a data object, and pointers to left and right nodes
		BSTreeNode(const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr);

		// Data members
	    /// Binary search tree data item
		DataType dataItem;      
		/// Pointer to the left child
		BSTreeNode *left,			 
		/// Pointer to the right child
			*right;		
	};

	// Recursive helpers for the public member functions
	
	/// ShowHelper allows to recursively display the tree
	/*!
		Recursive helper for showStructure.
		
		Outputs the keys in a binary search tree. The tree is output
		rotated counterclockwise 90 degrees from its conventional
		orientation using a "reve.rse" inorder traversal. This operation is
		intended for testing and debugging purposes only.
		
		Outputs the subtree whose root node is pointed to by p.
		@param level : number of times to tab over given the level of the tree.
		@param p : pointer to root which changes after each recursive call.
	*/
	void showHelper(BSTreeNode* p, int level) const;
	
	/// Copy constructor operator helper
	/*!
		Recursive helper for copy.
		
		Pre order traversal of the tree. We are essentially
		creating a tree from scratch.
		
		First we check if node is pointing to null.
		
		Else we set the key of the dataItem from the current node. Then we insert 
		the node and look at the nodes left and right child by recursively calling
		through copyHelper.

		@param node : pointer to root which changes after each recursive call.
	*/
	void copyHelper(BSTreeNode* node);
	
	/// Delete operator constructor helper
	/*!
		Recursive helper for delete.
		
		First we check if node is pointing to null.
		
		Then we recursively call deleteHelper with he nodes left then rigth children. 
		Finally we remove the node in a post order traversal.
		
		@param node : pointer to root which changes after each recursive call.
	*/
	void deleteHelper(BSTreeNode* node);  
	
	/// In order traversal printing of the keys
	/*!
		Recursive helper for writeKeys.
		
		First we check if node is pointing to null.

		Else print all the nodes in order traversal. This is done by recursively
		calling the printHelper function with the node's children. First going 
		throught all left children, the current node, then right children.
		@param node : pointer to root which changes after each recursive call.
	*/
	void printHelper(BSTreeNode* node) const;   
	
	/// Removing a node
	/*!
		Recursive helper for remove.
		
		First we check if node is pointing to null.
		
		Else we have to check a few other conditions to check:
		
		If the node is less than the key -> we recursively call deleteHelper 
		with the node's right child.
		
		If the node is greater than the key -> we recursively call deleteHelper 
		with the node's left child.
		
		If we found the node we have a few other conditions to check:
		
		1.) If the node is a leaf node, we can just delete it and not have to 
		worry about its children.
		
		2.) If the node has a single child, we set the child to root.
		
		3.) If the node has two children, we have to find the minimum of the 
		right branch. We set the minimum of the right branch as the value of the
		node we want to delete. Then the only thing left is to delete the right 
		branch minimum after we are done.
		@param node : pointer to root which changes after each recursive call.
		@param deleteKey : the key to the node that has to be deleted.
	*/
	void removeHelper(BSTreeNode*& node, KeyType deleteKey) const; 
	
	/// Height of a tree
	/*!
		Recursive helper for getHeight.
		
		First we check if node is pointing to null.
		
		If its null, we return 0
		
		We recursively call the getHeightHelper with the node's left and rigth children 
		and return the max of either the right or left child. 
		
		The max level is the height of the tree.		
		@param node : pointer to root which changes after each recursive call.
	*/
	int getHeightHelper(BSTreeNode* node) const;		
	
	/// Number of nodes in tree
	/*!
		Recursive helper for getCount.
		
		First we check if node is pointing to null.
		
		If its null, we return 0
		
		We recursively call the getHeightHelper with the node's left and right children 
		until we reached the root's leaves.  After we are at the leaves, we increment
		sum by one.
		
		@param sum : a refrence of the total number of nodes
		@param node : pointer to root which changes after each recursive call.
	*/
	int getCountHelper(BSTreeNode* node, int &sum) const;			 

	/// Pointer to the root node which defaults to null
	BSTreeNode* root;   
};