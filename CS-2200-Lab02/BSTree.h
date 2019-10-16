//--------------------------------------------------------------------
//
//  Laboratory 9                                    BSTree.h
//
//  Class declarations for the linked implementation of the Binary
//  Search Tree ADT -- including the recursive helpers of the
//  public member functions
//
//--------------------------------------------------------------------

#pragma once

#include <stdexcept>
#include <iostream>


using namespace std;

class TestData
{
public:

	void setKey(int newKey)
	{
		keyField = newKey;
	}   // Set the key

	int getKey() const
	{
		return keyField;
	}     // Returns the key

private:

	int keyField;  // Key for the data item
};

template < typename DataType, class KeyType >	    // DataType : tree data item
class BSTree                                     // KeyType : key field
{
  public:
	  // Constructor
	  BSTree();                         // Default constructor
	  BSTree(const BSTree&);   // Copy constructor
	  const BSTree& operator= (const BSTree);  // Overloaded assignment operator

	  // Destructor
	  ~BSTree();

	  // Binary search tree manipulation operations
	  void insert(const DataType& newDataItem);  // Insert data item
	  bool retrieve(const KeyType& searchKey, DataType& searchDataItem) const;
	  // Retrieve data item
	  bool remove(const KeyType& deleteKey);            // Remove data item
	  void writeKeys() const;                      // Output keys
	  void clear();                                // Clear tree

	  // Binary search tree status operations
	  bool isEmpty() const;                        // Tree is empty

	  // Output the tree structure -- used in testing/debugging
	  void showStructure() const;

	  // In-lab operations
	  int getHeight() const;           // Height of tree
	  int getCount() const;			  // Number of nodes in tree
	  //void writeLessThan(const int& searchKey) const; // Output keys < searchKey

protected:

	class BSTreeNode                  // Inner class: facilitator for the BSTree class
	{
	public:

	  // Constructor
      BSTreeNode ( const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr );

      // Data members
      DataType dataItem;         // Binary search tree data item
      BSTreeNode *left,			 // Pointer to the left child
                 *right;		 // Pointer to the right child
	};

	// Recursive helpers for the public member functions -- insert
	// prototypes of these functions here.
	void showHelper(BSTreeNode* p, int level) const;
	void copyHelper(BSTreeNode* node);   // Copy constructor
	void deleteHelper(BSTreeNode* node);   // delete operator
	void printHelper(BSTreeNode* node) const;   // Printing tree
	void removeHelper(BSTreeNode*& node, KeyType deleteKey) const;   // Removing a node

	// Data member
	BSTreeNode* root;   // Pointer to the root node
};