//--------------------------------------------------------------------
// Laboratory 9    										BSTree.cpp
/*!-------------------------------------------------------------------
	\file 
    \brief Implementations for the tree diagram

	Creates the individual implementations from BSTree.h.
	
	Since we are using a template to build our binary search tree,
	we have to make sure that we manually include all implementations
	files since c++ does not do that automatically. This is different 
	from normal classes because c++ does that by itself.
*/
//--------------------------------------------------------------------

#include "BSTree.h"

using namespace std;

///Initial blank tree
template<typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTree() {
	this->root = nullptr;
}

//Copy constructor DEEP COPY
template<typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTree(const BSTree<DataType, KeyType>& obj) {
	if (obj.isEmpty()) {
		cout << "Copying empty tree." << endl;
		this->root = obj.root;
	}
	else {
		//Create a first node
		copyHelper(obj.root);
	}
}

//Assignment opperator, similar to copy
template<typename DataType, class KeyType>
const BSTree<DataType, KeyType>& BSTree<DataType, KeyType>::operator=(const BSTree<DataType, KeyType> rObj)
{
	// Pass by value to generate a copy.
	*this = rObj;             // Swap the state of this and the
							  // copy we created in `other`
	return *this;
}

//Destructor for the bstree
template<typename DataType, class KeyType>
BSTree<DataType, KeyType>::~BSTree()
{
	deleteHelper(this->root);
	delete root;
}

//Insert a node
template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::insert(const DataType& newDataItem)
{
	BSTreeNode* node = new BSTreeNode(newDataItem, nullptr, nullptr);
	BSTreeNode* temp = root;

	if (this->root == nullptr) { //Empty Tree
		this->root = node;
	}
	else {
		while (temp != nullptr) {
			//Right side of the tree
			if (newDataItem.getKey() > temp->dataItem.getKey()) {
				if (temp->right == nullptr) {
					temp->right = node;
					break;
				}
				else
					temp = temp->right;
			}
			//Left side of the tree
			else if (newDataItem.getKey() < temp->dataItem.getKey())
				if (temp->left == nullptr) {
					temp->left = node;
					break;
				}
				else
					temp = temp->left;
			//Update the node
			else {
				temp = node;
				cout << "Updated node" << endl;
				break;
			}
		}
	}
}

//Retrieve a node 
template<typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& searchDataItem) const
{
	BSTreeNode* temp = root;
	while (temp != nullptr) {
		if (searchKey == temp->dataItem.getKey()) {
			searchDataItem.setKey(temp->dataItem.getRecNum(), searchKey);
			return true;
		}
		else {
			if (searchKey > temp->dataItem.getKey()) {
				if (temp->right == nullptr) {
					return false;
				}
				else
					temp = temp->right;
			}
			else
				if (temp->left == nullptr) {
					return false;
				}
				else
					temp = temp->left;
		}
	}
	return false;
}

//Deleting a node
template<typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::remove(const KeyType& deleteKey)
{
	DataType temp;
	//First search key if in node
	if (retrieve(deleteKey, temp)) {
		removeHelper(root, deleteKey);
		return true;
	}
	else
		return false;
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeKeys() const
{
	printHelper(this->root);
}

//Same thing as the destructor
template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::clear()
{
	deleteHelper(this->root);
	root = nullptr;
}

template<typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::isEmpty() const
{
	return root == nullptr ? true : false;
}

//Exercise #2
//Getting the height
template<typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getHeight() const
{
	return getHeightHelper(this->root);
}

//Exercise #2
//A cleaner interface for getCount using recursion
template<typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getCount() const
{
	int sum = 0;
	getCountHelper(this->root, sum);
	return sum;
}

template<typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode(const DataType& nodeDataItem, BSTreeNode* leftPtr, BSTreeNode* rightPtr)
{
	left = leftPtr;
	right = rightPtr;
	dataItem.setKey(nodeDataItem.getRecNum(), nodeDataItem.getKey());
}

//Pre order traversal, creating a tree from scratch
template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::copyHelper(BSTreeNode* node)
{
	DataType temp;
	if (node != nullptr)
	{
		temp.setKey(node->dataItem.getRecNum(), node->dataItem.getKey());
		insert(temp);
		copyHelper(node->left);
		copyHelper(node->right);
	}
}

//Post order traversal
template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::deleteHelper(BSTreeNode* node)
{
	if (node == NULL)
		return;

	//Call all left childs
	deleteHelper(node->left);

	//Now modify right nodes
	deleteHelper(node->right);

	//Current all rigth and left nodes delete current node
	delete node;
}

//In order traversal to print all nodes
template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::printHelper(BSTreeNode* node) const
{
	if (node == nullptr)
		return;

	//Call all left childs
	printHelper(node->left);

	//Current all left nodes modifty current node
	cout << node->dataItem.getKey() << " ";

	//Now modify right nodes
	printHelper(node->right);
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::removeHelper(BSTreeNode*& root, KeyType deleteKey) const
{
	BSTreeNode* temp = root;
	int min = 0;

	if (root == nullptr) {
		cout << "Error?" << endl;
	}
	else if (deleteKey > root->dataItem.getKey()) {
		removeHelper(root->right, deleteKey);
	}
	else if (deleteKey < root->dataItem.getKey()) {
		removeHelper(root->left, deleteKey);
	}//We found it
	else {
		//Three cases 1.) No children
		if (root->left == nullptr && root->right == nullptr) {
			root = nullptr;
			delete root;
		}// If there is one child
		else if (root->right == nullptr) {
			temp = root;
			root = root->left;
			delete temp;
		}
		else if (root->left == nullptr) {
			temp = root;
			root = root->right;
			delete temp;
		}//Has two children
		else {
			//Need to find the minimum in right branch
			temp = temp->right;
			while (temp->left != nullptr) {
				temp = temp->left;
			}
			min = temp->dataItem.getKey();
			root->dataItem.setKey(temp->dataItem.getRecNum(), min);
			removeHelper(root->right, min);
		}
	}
}

template<typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getHeightHelper(BSTreeNode * node) const
{
	if (node == nullptr)
		return 0;
	else {
		max(getHeightHelper(node->left), getHeightHelper(node->right)) + 1;
	}
}

template<typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getCountHelper(BSTreeNode* node, int &sum) const {
	if (node == nullptr)
		return 0;

	//Call all left childs
	getCountHelper(node->left, sum);

	//Now modify right nodes
	getCountHelper(node->right, sum);

	//Current all left nodes modifty current node
	return sum++;
}