#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
* A templated class for a Node in a search tree. The getters for parent/left/
//right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees,
// Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<const Key, Value>& getItem() const;
	std::pair<const Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;
	int getHeight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);
	void setHeight(int height);

protected:
	std::pair<const Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
	int mHeight;
};

/*
-----------------------------------------
Begin implementations for the Node class.
-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>*
	 																																		parent)
: mItem(key, value)
, mParent(parent)
, mLeft(NULL)
, mRight(NULL)
, mHeight(1)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside
of a node
* are only used as references to existing nodes. The nodes pointed to by
parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
	return mItem;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
	return mItem;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
	return mItem.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
	return mItem.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
	return mParent;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
	return mLeft;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
	return mRight;
}

/**
* A const getter for the height.
*/
template<typename Key, typename Value>
int Node<Key, Value>::getHeight() const
{
	return mHeight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
	mParent = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
	mLeft = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
	mRight = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
	mItem.second = value;
}

/**
* A setter for the height of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setHeight(int height)
{
	mHeight = height;
}

/*
---------------------------------------
End implementations for the Node class.
---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	int height();
	bool isBalanced();
	virtual void insert(const std::pair<const Key, Value>& keyValuePair);
	virtual void remove(const Key& key);
	void clear();
	void print() const;

public:
	/**
	* An internal iterator class for traversing the contents of the BST.
	*/
	class iterator
	{
	public:
		iterator(Node<Key,Value>* ptr);
		iterator();

		std::pair<const Key, Value>& operator*();
		std::pair<const Key, Value>* operator->();

		bool operator==(const iterator& rhs) const;
		bool operator!=(const iterator& rhs) const;
		iterator& operator=(const iterator& rhs);

		iterator& operator++();

	protected:
		Node<Key, Value>* mCurrent;
	};

public:
	iterator begin();
	iterator end();
	iterator find(const Key& key) const;

protected:
	Node<Key, Value>* internalFind(const Key& key) const;
	Node<Key, Value>* getSmallestNode() const;
	void printRoot (Node<Key, Value>* root) const;

protected:
	Node<Key, Value>* mRoot;

private:
	//helper for insert function, starts with node and
	//works its way up predacessors, fixing heights along the way
	void fixHeight(Node<Key, Value>* justInserted);
	//returns how many children a given node has
	int getNumChildren(Node<Key, Value>* getChildren);
	//recursive helper for clear
	void clearHelper(Node<Key, Value>* toDelete);
	//recursive helper for isBalanced
	bool isBalancedHelper(Node<Key, Value>* node);
};

/*
---------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
: mCurrent(ptr)
{

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
: mCurrent(NULL)
{

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*()
{
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>* BinarySearchTree<Key,Value>::iterator::operator->()
{
	return &(mCurrent->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const
	 												BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const
	 									BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key,
 Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key,
 Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
	mRoot = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
	clear();
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key,
 																								Value>::begin()
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key,
 																								Value>::end()
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key,
																					Value>::find(const Key& key) const
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An method to return the height of the BST.
*/
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height()
{
	if (mRoot != NULL) {
		return mRoot -> getHeight();
	}
	return 0;
}


/**
* An method to checks if the BST is balanced. This method returns true
if and only if the BST is balanced.
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced()
{
	if (mRoot == NULL) {
		return true;
	} else {
		return isBalancedHelper(mRoot);
	}
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalancedHelper(Node<Key, Value>* node) {

	int lHeight;
	bool isLeftBal = true;
	if (node -> getLeft() != NULL) {
		lHeight = node -> getLeft() -> getHeight();
		isLeftBal = isBalancedHelper(node -> getLeft());
	} else {
		lHeight = 0;
	}

	int rHeight;
	bool isRightBal = true;
	if (node -> getRight() != NULL) {
		rHeight = node -> getRight() -> getHeight();
		isRightBal = isBalancedHelper(node -> getRight());
	} else {
		rHeight = 0;
	}

	if (lHeight-rHeight == -1 || lHeight-rHeight == 0 || lHeight-rHeight == 1) {
		if (isLeftBal && isRightBal) {
			return true;
		}
	}

	return false;
}


/**
* An insert method to insert into a Binary Search Tree. The tree will not
remain balanced when
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key,
																												Value>& keyValuePair)
{
	if (mRoot == NULL) {
		mRoot = new Node<Key, Value>(keyValuePair.first,keyValuePair.second,NULL);
		mRoot -> setHeight(1);
		return;
	}

	Node<Key, Value>* currentNode = mRoot;
	while (currentNode != NULL) {
		if (currentNode -> getKey() == keyValuePair.first) {
			//key is already in tree, do nothing
			return;
		} else if (currentNode -> getKey() > keyValuePair.first) {
			if (currentNode -> getLeft() == NULL) {
				currentNode -> setLeft(new Node<Key, Value>(keyValuePair.first,keyValuePair.second,currentNode));
				fixHeight(currentNode -> getLeft());
				return;
			} else {
				currentNode = currentNode -> getLeft();
			}
		} else if (currentNode -> getKey() < keyValuePair.first) {
			if (currentNode -> getRight() == NULL) {
				currentNode -> setRight(new Node<Key, Value>(keyValuePair.first,keyValuePair.second,currentNode));
				fixHeight(currentNode -> getRight());
				return;
			} else {
				currentNode = currentNode -> getRight();
			}
		}
	}
}

/**
* An remove method to remove a specific key from a Binary Search Tree.
The tree may not remain balanced after
* removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	//first we check that the key is actually in the graph, if not we do nothing
	Node<Key, Value>* nodeToRemove = internalFind(key);
	if (nodeToRemove == NULL) {
		return;
	}

	if (mRoot -> getKey() == key) {
		//root needs to be removed, this is a special case and we must handle it

		//if root is only node in graph, our job is easy
		if (getNumChildren(mRoot) == 0) {
			delete mRoot;
			mRoot = NULL;
		}

		//if root has one child, that child gets promoted and becomes root
		else if (getNumChildren(mRoot) == 1) {
			Node<Key, Value>* nodeToRemoveChild;
			if (mRoot->getLeft()!= NULL) {
				nodeToRemoveChild = mRoot->getLeft();
			} else {
				nodeToRemoveChild = mRoot->getRight();
			}

			nodeToRemoveChild -> setParent(NULL);
			delete mRoot;
			mRoot = nodeToRemoveChild;
			//the height of the root is the only thing that needs fixing in this
			//case, so we do this before were done
			fixHeight(mRoot);
		}
		//if root has two children, weve got a lot to do
		else if (getNumChildren(mRoot) == 2) {
			//first, find predecessor of root
			Node<Key, Value>* predecessor = mRoot -> getLeft();
			while (predecessor -> getRight() != NULL) {
				predecessor = predecessor -> getRight();
			}

			Node<Key, Value>* predecessorParent = predecessor -> getParent();

			//start by making predecessors parent child be null
			//(only if predecessor isnt left child of root)
			if (mRoot->getLeft() != predecessor) {
				//we know it will be rightChild because of nature of predacessors
				predecessor -> getParent() -> setRight(NULL);
			}

			//in fact, if predecessor is left child of root, we have a special case
			//that we must deal with by promoting predecessor and attaching
			//mRoots right child to it
			if (mRoot->getLeft() == predecessor) {
				predecessor -> setParent(NULL);
				predecessor -> setRight(mRoot->getRight());
				mRoot -> getRight() -> setParent(predecessor);
				delete mRoot;
				mRoot = predecessor;

				//the height of the root is the only thing that needs fixing in this
				//case, so we do this before returning
				fixHeight(mRoot);
				return;
			}

			//now, if predecessor has a left child (only possible for it to have left
			//child), we make it the rightChild of predacessors parent
			if (predecessor -> getLeft() != NULL) {
				predecessor -> getParent() -> setRight(predecessor->getLeft());
				predecessor->getLeft()->setParent(predecessor -> getParent());
			}

			//now reassign pointers so predecessor replaces mRoot
			predecessor -> setParent(NULL);
			predecessor -> setLeft(mRoot->getLeft());
			mRoot->getLeft() -> setParent(predecessor);
			predecessor -> setRight(mRoot->getRight());
			mRoot -> getRight() -> setParent(predecessor);

			delete mRoot;
			mRoot = predecessor;

			fixHeight(predecessorParent);
		}
		return;
	}
	//if weve made it down here that means were not removing the node
	//keep in mind that nodeToRemove still contains what we want to remove

	//we will save nodeToRemoveParent for height fixing reasons later on
	Node<Key, Value>* nodeToRemoveParent = nodeToRemove -> getParent();

	//break down the remove cases based on the number of children nodeToRemove has
	//node has 0 children (leaf)
	if (getNumChildren(nodeToRemove) == 0) {
		//we figure out if nodeToRemove is a left or right child and adjust its
		//parent accordingly
		if (nodeToRemove -> getParent() -> getLeft() == nodeToRemove) {
			nodeToRemove -> getParent() -> setLeft(NULL);
		} else if (nodeToRemove -> getParent() -> getRight() == nodeToRemove) {
			nodeToRemove -> getParent() -> setRight(NULL);
		}

		delete nodeToRemove;
		//finally, we call update height on the parent of nodeToRemove and then
		//delete nodeToRemove
		fixHeight(nodeToRemoveParent);


	}
	//node has one child
	else if (getNumChildren(nodeToRemove) == 1) {
		Node<Key, Value>* nodeToRemoveChild;
		if (nodeToRemove->getLeft()!= NULL) {
			nodeToRemoveChild = nodeToRemove->getLeft();
		} else {
			nodeToRemoveChild = nodeToRemove->getRight();
		}
		//we figure out if nodeToRemove is a left or right child and adjust its
		//parent accordingly
		if (nodeToRemove -> getParent() -> getLeft() == nodeToRemove) {
			nodeToRemoveChild -> setParent(nodeToRemove -> getParent());
			nodeToRemove -> getParent() -> setLeft(nodeToRemoveChild);
		} else if (nodeToRemove -> getParent() -> getRight() == nodeToRemove) {
			nodeToRemoveChild -> setParent(nodeToRemove -> getParent());
			nodeToRemove -> getParent() -> setRight(nodeToRemoveChild);
		}
		delete nodeToRemove;

		//update height and delete nodeToRemove
		fixHeight(nodeToRemoveParent);
	}
	//node has two children
	else if (getNumChildren(nodeToRemove) == 2) {
		//first, find predecessor
		Node<Key, Value>* predecessor = nodeToRemove -> getLeft();

		while (predecessor -> getRight() != NULL) {
			predecessor = predecessor -> getRight();
		}

		Node<Key, Value>* predecessorParent = predecessor -> getParent();

		//if predecessor is the left child of nodeToRemove, we have a special case
		if (nodeToRemove -> getLeft() == predecessor) {

			if (nodeToRemove -> getParent() -> getLeft() == nodeToRemove) {
				nodeToRemove->getParent()->setLeft(predecessor);
			} else if (nodeToRemove -> getParent() -> getRight() == nodeToRemove) {
				nodeToRemove->getParent()->setRight(predecessor);
			}
			predecessor -> setParent(nodeToRemove->getParent());
			predecessor -> setRight(nodeToRemove->getRight());
			nodeToRemove -> getRight() -> setParent(predecessor);

			delete nodeToRemove;

			//the height of the root is the only thing that needs fixing in this
			//case, so we do this before returning
			fixHeight(predecessor);
			return;
		}

		//now, if predecessor has a left child (only possible for it to have left
		//child), we make it the rightChild of predacessors parent
		if (predecessor -> getLeft() != NULL) {
			predecessor -> getParent() -> setRight(predecessor->getLeft());
			predecessor->getLeft()->setParent(predecessor -> getParent());
		} else {
			predecessor -> getParent() -> setRight(NULL);
		}

		//now reassign pointers so predecessor replaces nodeToRemove

		//if nodeToRemove was a left child, predecessor will be a left child
		if (nodeToRemove->getParent()->getLeft()==nodeToRemove) {
			nodeToRemove->getParent()->setLeft(predecessor);
		} else {
			nodeToRemove->getParent()->setRight(predecessor);
		}

		predecessor -> setParent(nodeToRemove->getParent());
		predecessor -> setLeft(nodeToRemove->getLeft());
		nodeToRemove->getLeft() -> setParent(predecessor);
		predecessor -> setRight(nodeToRemove->getRight());
		nodeToRemove -> getRight() -> setParent(predecessor);

		delete nodeToRemove;

		fixHeight(predecessorParent);
	}
	return;
}

/**
* A method to remove all contents of the tree and reset the values in the tree
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	//start our recursive helper on the root
	clearHelper(mRoot);
	mRoot = NULL;
	return;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	Node<Key, Value>* currentNode = mRoot;
	while (currentNode -> getLeft() != NULL) {
		currentNode = currentNode -> getLeft();
	}
	return currentNode;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key,
 																Value>::internalFind(const Key& key) const
{
	Node<Key, Value>* currentNode = mRoot;
	while (currentNode != NULL) {
		if (currentNode -> getKey() == key) {
			return currentNode;
		}
		else if (currentNode -> getKey() < key) {
			currentNode = currentNode -> getRight();
		}
		else if (currentNode -> getKey() > key) {
			currentNode = currentNode -> getLeft();
		}
	}
	return NULL;
}

/**
* Helper function to print the tree's contents
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::printRoot (Node<Key, Value>* root) const
{
	if (root != NULL)
	{
		std::cout << "[";
		printRoot (root->getLeft());
		std::cout << " (" << root->getKey() << ", " << root->getValue() << ") ";
		printRoot (root->getRight());
		std::cout << "]";
	}
}

//starts with startNode and works its way up predacessors, fixing heights
//along the way
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::fixHeight(Node<Key, Value>* startNode) {
	Node<Key, Value>* currentNode = startNode;

	if (currentNode == NULL) {
		return;
	}

	while (true) {
		int lHeight;
		if (currentNode -> getLeft() != NULL) {
			lHeight = currentNode -> getLeft() -> getHeight();
		} else {
			lHeight = 0;
		}

		int rHeight;
		if (currentNode -> getRight() != NULL) {
			rHeight = currentNode -> getRight() -> getHeight();
		} else {
			rHeight = 0;
		}

		int max;
		if (lHeight > rHeight) {
			max = lHeight;
		} else {
			max = rHeight;
		}

		currentNode -> setHeight(max+1);
		//this while loop keeps running until currentNode is mRoot
		if (currentNode -> getParent() != NULL) {
			currentNode = currentNode -> getParent();
		} else break;
	}
}

//helper function that returns number of children for given node
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::getNumChildren(Node<Key, Value>* getChildren){
	if (getChildren->getLeft() == NULL && getChildren->getRight() == NULL) {
		return 0;
	} else if((getChildren->getLeft()!=NULL && getChildren->getRight()==NULL)||
	(getChildren->getLeft() == NULL && getChildren->getRight() != NULL)) {
		return 1;
	} else if (getChildren->getLeft() != NULL && getChildren->getRight() != NULL){
		return 2;
	} else {
		return -1;
	}
}

//recursive helper for clear
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* toDelete) {
	//if toDelete is NULL, simply do nothing as calling delete would be invalid
	if (toDelete == NULL) {
		return;
	}
	//post order traversal
	clearHelper(toDelete -> getLeft());
	clearHelper(toDelete -> getRight());
	//after we have traversed left and right children, delete toDelete
	delete toDelete;
	return;
}
/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
