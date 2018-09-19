#ifndef rotateBST_H
#define rotateBST_H

#include "bst.h"
#include <set>

using std::set;

template<typename Key, typename Value>
class rotateBST: public BinarySearchTree<Key, Value>
{
    public:
        rotateBST();
        ~rotateBST();
        bool sameKeys(const rotateBST& t2) const;
        void transform(rotateBST& t2) const;
    protected:
        void leftRotate(Node<Key, Value>* r);
        void rightRotate(Node<Key, Value>* r);


    private:
        void sameKeysRecursiveHelper(set<Key> & keySet, Node<Key, Value>* root) const;
        void transformRecursiveHelper(rotateBST & t2, Node<Key, Value>* node) const;
        void transformRecursiveHelperFix(rotateBST & t2, Node<Key, Value>* node) const;
        void updateHeights(Node<Key, Value>* node);
        int max(const int a, const int b);
        bool isRightChild(Node<Key, Value>* node) const;
        bool isLeftChild(Node<Key, Value>* node) const;
        // bool operator==(rotateBST<Key, Value> & rhs) const;
        // bool equalsRecHelper(Node<Key, Value>* leftNode, Node<Key, Value>* rightNode) const;
};

template<typename Key, typename Value>
rotateBST<Key, Value>::rotateBST() : BinarySearchTree<Key, Value>()
{

}


template<typename Key, typename Value>
rotateBST<Key, Value>::~rotateBST()
{

}


/**
* Given another BST, returns true if the set of keys in each tree is identical
*/
template<typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST& t2) const
{
    set<Key> thisKeys;
    set<Key> thatKeys;

    sameKeysRecursiveHelper(thisKeys, this->mRoot);
    sameKeysRecursiveHelper(thatKeys, t2.mRoot);

    if (thisKeys == thatKeys)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
* Given another BST, if their keys are identical, transforms the other BST
* into a copy of this one using only rotations
*/
template<typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST& t2) const
{
    // if t2 does not have the same keys as this, do nothing
    if (!sameKeys(t2))
    {
        return;
    }

    //turns tree into a linked list
    transformRecursiveHelper(t2, t2.mRoot);

    // performs left rotations on the root node of t2
    // until the root of t2 is the same as the root of this.
    while(t2.mRoot->getKey() != this->mRoot->getKey())
    {
        t2.leftRotate(t2.mRoot);
    }

    transformRecursiveHelperFix(t2, t2.mRoot->getLeft());
    transformRecursiveHelperFix(t2, t2.mRoot->getRight());

    //update heights of tree
    t2.updateHeights(t2.mRoot);


}

/**
* Performs a left rotation at the given node
*/
template<typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* r)
{
    if (r->getRight() == NULL)
    {
        return;
    }

    Node<Key, Value>* newParent = r->getRight();

    if (r == this->mRoot)
    {
        this->mRoot = newParent;
    }
    else // set the newParent as the child of r's parent
    {
        if (isLeftChild(r))
        {
            r->getParent()->setLeft(newParent);
            newParent->setParent(r->getParent());
        }
        else // is right child
        {
            r->getParent()->setRight(newParent);
            newParent->setParent(r->getParent());
        }
    }

    if (newParent->getLeft() != NULL)
    {
        r->setRight(newParent->getLeft());
        newParent->getLeft()->setParent(r);
    }
    else
    {
        r->setRight(NULL);
    }

    newParent->setLeft(r);
    r->setParent(newParent);
}

/**
* Performs a right rotation at the given node.
*/
template<typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* r)
{
    // if invalid tree for a rotation
    if (r->getLeft() == NULL)
    {
        return;
    }


    Node<Key, Value>* newParent = r->getLeft();

    // change the root pointer if necessary
    if (r == this->mRoot)
    {
        this->mRoot = newParent;
    }
    else // set the newParent as the child of r's parent
    {
        if (isLeftChild(r))
        {
            r->getParent()->setLeft(newParent);
            newParent->setParent(r->getParent());
        }
        else // is right child
        {
            r->getParent()->setRight(newParent);
            newParent->setParent(r->getParent());
        }
    }

    // rotating v: move u's right subtree to v's left subtree
    if (newParent->getRight() != NULL)
    {
        r->setLeft(newParent->getRight());
        newParent->getRight()->setParent(r);
    }
    else
    {
        r->setLeft(NULL);
    }

    // make v the right subtree of u
    newParent->setRight(r);
    r->setParent(newParent);
}

/**
* Helper function for sameKeys that fills the parameter set with all
* of the keys in the given tree
*/
template<typename Key, typename Value>
void rotateBST<Key, Value>::sameKeysRecursiveHelper(set<Key> & keySet, Node<Key, Value>* root) const
{
    if (root->getLeft() != NULL)
    {
        sameKeysRecursiveHelper(keySet, root->getLeft());
    }
    if (root->getRight() != NULL)
    {
        sameKeysRecursiveHelper(keySet, root->getRight());
    }

    keySet.insert(root->getKey());
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::transformRecursiveHelper(rotateBST & t2, Node<Key, Value>* node) const
{
    //parameter node is the root of t2

    //Rotate the root to the right until the root has no left children
    Node<Key, Value>* currentNode = node;
    while (currentNode->getLeft() != NULL)
    {
        t2.rightRotate(currentNode);
        currentNode = currentNode->getParent();
    }

    //recursively call on right node
    if (currentNode->getRight() != NULL)
    {
        transformRecursiveHelper(t2, currentNode->getRight());
    }

}

template<typename Key, typename Value>
void rotateBST<Key, Value>::transformRecursiveHelperFix(rotateBST & t2, Node<Key, Value>* node) const
{
    Node<Key, Value>* thisParent = this->internalFind(node->getParent()->getKey());

    // if this is a mismatch, fix it
    if (isLeftChild(node) && (thisParent->getLeft()->getKey() != node->getKey()))
    {
        while (thisParent->getLeft()->getKey() != node->getKey())
        {
            t2.rightRotate(node);
            node = node->getParent();
        }
    }
    else if (isRightChild(node) && (thisParent->getRight()->getKey() != node->getKey()))
    {
        while (thisParent->getRight()->getKey() != node->getKey())
        {
            t2.leftRotate(node);
            node = node->getParent();
        }
    }

    // recurse on left and right children
    if (node->getLeft() != NULL)
    {
        transformRecursiveHelperFix(t2, node->getLeft());
    }
    if (node->getRight() != NULL)
    {
        transformRecursiveHelperFix(t2, node->getRight());
    }

}


template<typename Key, typename Value>
void rotateBST<Key, Value>::updateHeights(Node<Key, Value>* node)
{
    // Base case
    // if leaf node, set height = 1
    if (node->getLeft() == NULL && node->getRight() == NULL)
    {
        node->setHeight(1);
        return;
    }

    if (node->getLeft() != NULL)
    {
        updateHeights(node->getLeft());
    }
    if (node->getRight() != NULL)
    {
        updateHeights(node->getRight());
    }

    // set height
    if (node->getLeft() != NULL && node->getRight() != NULL)
    {
        node->setHeight(max(node->getLeft()->getHeight(), node->getRight()->getHeight())+1);
    }
    else if (node->getLeft() != NULL)
    {
        node->setHeight(node->getLeft()->getHeight()+1);
    }
    else // has only right child
    {
        node->setHeight(node->getRight()->getHeight()+1);
    }
}

template<typename Key, typename Value>
int rotateBST<Key, Value>::max(const int a, const int b)
{
    if (a >= b) return a;
    else return b;
}

template<typename Key, typename Value>
bool rotateBST<Key, Value>::isLeftChild(Node<Key, Value>* node) const
{
    if (node->getParent()->getLeft() == node)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename Key, typename Value>
bool rotateBST<Key, Value>::isRightChild(Node<Key, Value>* node) const
{
    if (node->getParent()->getRight() == node)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// /**
//  * Returns true if two BSTs have the same keys and structure
//  * */
// template<typename Key, typename Value>
// bool rotateBST<Key, Value>::operator==(rotateBST<Key, Value> & rhs) const
// {
//  if (!sameKeys(rhs)) return false;

//  Node<Key, Value>* leftNode = this->mRoot, rightNode = rhs.mRoot;

//  if (leftNode == NULL && rightNode == NULL) return true;

//  if (leftNode != NULL && rightNode != NULL && leftNode->getKey() == rightNode->getKey())
//  {
//      return equalsRecHelper(leftNode, rightNode);
//  }
//  else return false;

// }

// template<typename Key, typename Value>
// bool rotateBST<Key, Value>::equalsRecHelper(Node<Key, Value>* leftNode, Node<Key, Value>* rightNode) const
// {
//  // check equality
//  if (leftNode->getKey() != rightNode->getKey())
//  {
//      return false;
//  }

//  bool left_equals = false, right_equals = false;

//  // recurse
//  if (leftNode->getLeft() != NULL && rightNode->getLeft() != NULL)
//  {
//      left_equals = equalsRecHelper(leftNode->getLeft(), rightNode->getLeft());
//  }
//  else if (leftNode->getLeft() == NULL && rightNode->getLeft() == NULL) return true;
//  else return false;

//  if (leftNode->getRight() != NULL && rightNode->getRight() != NULL)
//  {
//      right_equals = equalsRecHelper(leftNode->getRight(), rightNode->getRight());
//  }
//  else if (leftNode->getRight() == NULL && rightNode->getRight() == NULL) return true;
//  else return false;

//  if (left_equals && right_equals) return true;
//  else return false;

// }

#endif
