#ifndef rtBST
#define rtBST

#include <vector>
#include <iostream>
#include "bst.h"

using std::vector;

template <typename Key, typename Value>
class rotateBST: public BinarySearchTree<Key, Value> {
public:
  //given another BST, checks that the set of keys in both trees are identical.
  //This should run in O(n) time, where n is the number of nodes in the tree.
  bool sameKeys(const rotateBST& t2) const;

  //given another BST t2, if t2 contains the same keys as the one for this,
  //transform the BST t2 into the one for this using only rotations. If the BST
  //t2 does not have the same keys as this, this function should do nothing and
  //neither BST should be modified.
  void transform(rotateBST& t2) const;
protected:
  // perform a left rotation at the parameter node. If r has no right child,
  //this function should do nothing. This should run in constant time.
  void leftRotate(Node<Key, Value>* r);

  //perform a right rotation at the parameter node. If r has no left child,
  //this function should do nothing. This should run in constant time.
  void rightRotate(Node<Key, Value>* r);
private:
  void sameKeysHelper(Node<Key, Value>* node, vector<Key> &treeKeys) const;
  void transformHelper(Node<Key, Value>* node, rotateBST &t2) const;
  void fixHeight(Node<Key, Value>* node) const;
};

template <typename Key, typename Value>
bool rotateBST<Key,Value>::sameKeys(const rotateBST& t2) const {
  vector<Key> tree1Keys;
  vector<Key> tree2Keys;
  Node<Key, Value>* tree1Root = this -> mRoot;
  Node<Key, Value>* tree2Root = t2.mRoot;

  sameKeysHelper(tree1Root, tree1Keys);
  sameKeysHelper(tree2Root, tree2Keys);

  if (tree1Keys.size() != tree2Keys.size()) {

    return false;
  }
  for (size_t i = 0; i < tree1Keys.size(); i++) {
    if (tree1Keys[i] != tree2Keys[i]) {
      return false;
    }
  }
  return true;
}

//adds all keys in tree to set
template <typename Key, typename Value>
void rotateBST<Key,Value>::sameKeysHelper(Node<Key, Value>* node, vector<Key>
                                                        &treeKeys) const {
  if (node == NULL) {
    return;
  }

  sameKeysHelper(node->getLeft(),treeKeys);
  treeKeys.push_back(node->getKey());
  sameKeysHelper(node->getRight(),treeKeys);
  return;
}

template <typename Key, typename Value>
void rotateBST<Key,Value>::transform(rotateBST& t2) const {
  //if t2 doesnt have the same keys as us, do nothing
  if (!sameKeys(t2)) {
    return;
  }
  //if either tree is empty, do nothing
  if (this -> mRoot == NULL || t2.mRoot == NULL) {
    return;
  }

  //rotate a node of t2 (starting with the root) so that it has no left child,
  //do this for all nodes in t2 so that t2 ends up being a linked list
  Node<Key, Value>* rotatingNode = t2.mRoot;
  while (true) {
    while (rotatingNode -> getLeft() != NULL) {
      t2.rightRotate(rotatingNode);
      rotatingNode = rotatingNode -> getParent();
    }
    if (rotatingNode -> getRight() == NULL) {
      break;
    } else {
      rotatingNode = rotatingNode -> getRight();
    }
  }

  //now, rotate the root of t2 to the left until it matches the root of this
  //note that what t2.mRoot is pointing to changes everytime we rotate
  while (this -> mRoot -> getKey() != t2.mRoot -> getKey()) {
    t2.leftRotate(t2.mRoot);
  }

  //finally, to get t2 to look like this tree we call our recursive helper,
  //which will also fix our heights in t2 for us

  if (t2.mRoot->getLeft() != NULL) {
    transformHelper(t2.mRoot->getLeft(), t2);
  }
  if (t2.mRoot->getRight() != NULL) {
    transformHelper(t2.mRoot->getRight(), t2);
  }

  fixHeight(t2.mRoot);
}

template <typename Key, typename Value>
void rotateBST<Key,Value>::transformHelper
                                (Node<Key,Value>* node,rotateBST &t2) const {
  //keep in mind node is in t2

  //we use internal find to find node's parent (which is in t2) within this tree
  Node<Key,Value>* parentInThisTree = this->
                                internalFind(node->getParent()->getKey());

  //if there is an incongruency in the structure of t2 and this tree, we need to
  //fix it by rotating until the structures match up

  //before getting the key of parentInThisTree's left child, we have to
  //make sure parentInThisTree has a left child
  if (parentInThisTree->getLeft() != NULL) {
  if ((parentInThisTree->getLeft()->getKey() != node->getKey())
  && node -> getParent() -> getLeft() == node) {
    while (node -> getKey() != parentInThisTree -> getLeft() -> getKey()) {
      t2.rightRotate(node);
      node = node -> getParent();
    }
  }
}
  //before getting the key of parentInThisTree's right child, we have to
  //make sure parentInThisTree has a right child
  if (parentInThisTree -> getRight() != NULL) {
  if ((parentInThisTree->getRight()->getKey() != node->getKey())
   && node -> getParent() -> getRight() == node) {
    while (node -> getKey() != parentInThisTree -> getRight() -> getKey()) {
      t2.leftRotate(node);
      node = node -> getParent();
    }
  }
}

  //do this whole shebang again on the left and right children of node as long
  //as they exist

  if (node -> getLeft() != NULL) {
    transformHelper(node->getLeft(),t2);
  }
  if (node -> getRight () != NULL) {
    transformHelper(node->getRight(),t2);
  }
  return;
}

template <typename Key, typename Value>
void rotateBST<Key,Value>::fixHeight(Node<Key, Value>* node) const {
  if (node -> getLeft() == NULL && node -> getRight() == NULL) {
    node -> setHeight(1);
    return;
  }

  if (node->getLeft() != NULL) {
    fixHeight(node->getLeft());
  }
  if (node->getRight() != NULL) {
    fixHeight(node->getRight());
  }

  int lHeight;
  if (node -> getLeft() != NULL) {
    lHeight = node -> getLeft() -> getHeight();
  } else {
    lHeight = 0;
  }

  int rHeight;
  if (node -> getRight() != NULL) {
    rHeight = node -> getRight() -> getHeight();
  } else {
    rHeight = 0;
  }

  int max;
  if (lHeight > rHeight) {
    max = lHeight;
  } else {
    max = rHeight;
  }

  node -> setHeight(max+1);
  return;
}


template <typename Key, typename Value>
void rotateBST<Key,Value>::leftRotate(Node<Key, Value>* r) {
  if (r == NULL) {
    return;
  }
  if (r -> getRight() == NULL) {
    return;
  }

  Node<Key, Value>* willBeParent = r -> getRight();

  //this code isn't applicable if we are rotating the root so we add this if
  //statement
  if (this->mRoot != r) {
    //modify pointers so r's parent's child is willBeParent
    //figure out if r is left or right child of its parent
    if (r->getParent()->getLeft()==r) {
      r->getParent()->setLeft(willBeParent);
      willBeParent -> setParent(r->getParent());
    } else {
      r->getParent()->setRight(willBeParent);
      willBeParent -> setParent(r->getParent());
    }
  } else {
    willBeParent -> setParent(NULL);
  }

  //make willBeParent's left child the right child of r
  //as long as willBeParent has left child, otherwise right child of r is null
  if (willBeParent->getLeft() == NULL) {
    r->setRight(NULL);
  } else {
    r->setRight(willBeParent->getLeft());
    willBeParent->getLeft()->setParent(r);
  }

  //we finish by making r the left child of willBeParent
  willBeParent->setLeft(r);
  r->setParent(willBeParent);

  //if the node we are rotating is the root, the new root will be willBeParent
  //so we update mRoot
  if (this->mRoot == r) {
    this->mRoot = willBeParent;
  }
}

template <typename Key, typename Value>
void rotateBST<Key,Value>::rightRotate(Node<Key, Value>* r) {
  if (r == NULL) {
    return;
  }
  if (r -> getLeft() == NULL) {
    return;
  }

  Node<Key, Value>* willBeParent = r -> getLeft();

  //this code isn't applicable if we are rotating the root so we add this if
  //statement
  if (this->mRoot != r) {
    //modify pointers so r's parent's child is willBeParent
    //figure out if r is left or right child of its parent
    if (r->getParent()->getLeft()==r) {
      r->getParent()->setLeft(willBeParent);
      willBeParent -> setParent(r->getParent());
    } else {
      r->getParent()->setRight(willBeParent);
      willBeParent -> setParent(r->getParent());
    }
  } else {
    willBeParent -> setParent(NULL);
  }

  //make willBeParent's right child the left child of r
  //as long as willBeParent has right child, otherwise left child of r is null
  if (willBeParent->getRight() == NULL) {
    r->setLeft(NULL);
  } else {
    r->setLeft(willBeParent->getRight());
    willBeParent->getRight()->setParent(r);
  }

  //we finish by making r the right child of willBeParent
  willBeParent->setRight(r);
  r->setParent(willBeParent);

  //if the node we are rotating is the root, the new root will be willBeParent
  //so we update mRoot
  if (this->mRoot == r) {
    this->mRoot = willBeParent;
  }
}


#endif
