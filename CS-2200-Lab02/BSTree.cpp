#pragma once
#include <stdexcept>
#include <iostream>
#include "BSTree.h"

using namespace std;

template<typename DataType, class KeyType>
inline BSTree<DataType, KeyType>::BSTree()
{
}

template<typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTree(const BSTree<DataType, KeyType>& other)
{
}

template<typename DataType, class KeyType>
BSTree& BSTree<DataType, KeyType>::operator=(const BSTree<DataType, KeyType>& other)
{
	BSTree <DataType, KeyType> temp;
	// TODO: insert return statement here
	return temp;
}

template<typename DataType, class KeyType>
BSTree<DataType, KeyType>::~BSTree()
{
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::insert(const DataType& newDataItem)
{
}

template<typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& searchDataItem) const
{
	return false;
}

template<typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::remove(const KeyType& deleteKey)
{
	return false;
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeKeys() const
{
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::clear()
{
}

template<typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::isEmpty() const
{
	return false;
}

template<typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getHeight() const
{
	return false;
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeLessThan(const KeyType& searchKey) const
{
}

template<typename DataType, class KeyType>
int BSTree<DataType, KeyType>::getCount() const
{
	return false;
}

