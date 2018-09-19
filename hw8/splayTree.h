#ifndef splyT
#define splyT

#include "rotateBST.h"

template <typename Key, typename Value>
class SplayTree: public rotateBST<Key, Value> {
public:
  SplayTree();
  void insert(const std::pair<const Key, Value>& keyValuePair);
  void remove(const Key& key);
  void deleteMinLeaf();
  void deleteMaxLeaf();
  typename SplayTree<Key, Value>::iterator find(const Key& key);
  typename SplayTree<Key, Value>::iterator findMin();
  typename SplayTree<Key, Value>::iterator findMax();
protected:
  void splay(Node<Key, Value> *r);
private:
  void splayHelper(Node<Key, Value> *r);
  Node<Key, Value>* modifiedSearch(const Key& key);
  Node<Key, Value>* getLargestLeaf();
  Node<Key, Value>* getSmallestLeaf();
  Node<Key, Value>* getLargestNode();
};

template <typename Key, typename Value>
SplayTree<Key,Value>::SplayTree() {

}

/**
*This function will insert a new node into the tree with the specified key
*and value. The node that has just been inserted is splayed to the root. If a
*node with this key already exists, don't insert anything, but splay the node
*to the root.
*/
template <typename Key, typename Value>
void SplayTree<Key,Value>::insert(const std::pair<const Key, Value>&
                                                                keyValuePair) {
  //look for what we want to insert
  Node<Key, Value>* foundNode = BinarySearchTree<Key, Value>::internalFind(
                                                          keyValuePair.first);
  if (foundNode == NULL) {
    //if it isnt in our tree then insert it, then run internalFind again to get
    //pointer to node we just inserted
    BinarySearchTree<Key, Value>::insert(keyValuePair);
    foundNode = BinarySearchTree<Key, Value>::internalFind(keyValuePair.first);
  }

  //now that it's inserted (or if it was present to begin with) splay the node
  splay(foundNode);
}

/**
*This function will first find a node with the specified key in the tree.
*This function should call BST remove, and then splay the parent of the deleted
*node to root. (This is different and less complicated than method given in
*Sandra's lecture, but works well given the inheritance hierarchy.) If the key
*is not already in the tree, then don't remove anything, but splay the last
*node visited to the root.
*/
template <typename Key, typename Value>
void SplayTree<Key,Value>::remove(const Key& key) {
  //this modified search returns the last accessed node if it doesnt find the
  //key we're looking for
  Node<Key,Value>* resultOfSearch = modifiedSearch(key);

  //this means tree is empty, so we do nothing
  if (resultOfSearch == NULL) {
    return;
  }

  //if we're removing the root, all we do is call remove and splay nothing
  if (resultOfSearch -> getParent() == NULL) {
    BinarySearchTree<Key, Value>::remove(key);
    return;
  }

  //this checks if we actually found the key we're looking for, so we know if
  //we should remove resultOfSearch or not
  if (resultOfSearch -> getKey() == key) {

    //next we determine the node we will splay after we remove, this depends on
    //the number of children resultOfSearch has and if it has a direct left pred
    Node<Key,Value>* nodeToSplay = NULL;

    //if resultOfSearch has two children, we need to find predecessor
    if ((resultOfSearch -> getLeft() != NULL && resultOfSearch -> getRight()
                                                                    != NULL)) {

      Node<Key, Value>* predecessor = resultOfSearch -> getLeft();
      while (predecessor -> getRight() != NULL) {
        predecessor = predecessor -> getRight();
      }

      //if predecessor is direct left child of resultOfSearch,
      //we will splay predecessor
      if (resultOfSearch -> getLeft() -> getKey() == predecessor -> getKey()) {
        nodeToSplay = predecessor;
      }
      //otherwise, we will splay predecessors parent
      else {
        nodeToSplay = predecessor -> getParent();
      }
    }

    //if resultOfSearch has one or zero children, we will splay its parent
    else {
      nodeToSplay = resultOfSearch -> getParent();
    }

    BinarySearchTree<Key, Value>::remove(key);
    splay(nodeToSplay);
    return;
  }
  //if we get here, we didn't find the node, so we just splay resultOfSearch
  splay(resultOfSearch);
}

/**
*This function deletes the leaf with minimum key value, exactly as if you had
*called the remove function.
*/
template <typename Key, typename Value>
void SplayTree<Key,Value>::deleteMinLeaf() {
  Node<Key,Value>* smallest = getSmallestLeaf();
  //if tree isnt empty
  if (smallest != NULL) {
    remove(smallest->getKey());
  }
}

/**
*This function deletes the leaf with maximum key value, exactly as if you had
*called the remove function.
*/
template <typename Key, typename Value>
void SplayTree<Key,Value>::deleteMaxLeaf() {
  Node<Key,Value>* largest = getLargestLeaf();
  //if tree isnt empty
  if (largest != NULL) {
    remove(largest->getKey());
  }
}

/**
*This function should splay the node with the specified key to the root, and
*return an iterator to that item. If the key is not found, splay the last
*visited node to the root, and return the end iterator.
*/
template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::find(const
                                                                    Key& key) {
  Node<Key,Value>* resultOfSearch = modifiedSearch(key);
  //if tree is empty
  if (resultOfSearch == NULL) {
    return NULL;
  }
  //check if we actually found key we were looking for
  if (resultOfSearch -> getKey() == key) {
    splay(resultOfSearch);
    return typename BinarySearchTree<Key, Value>::iterator::iterator(
                                                                resultOfSearch);
  }

  //if we got here, we didnt find the key, so we splay the last accessed node
  //and return the end iterator
  splay(resultOfSearch);
  return BinarySearchTree<Key, Value>::end();
}

/**
*This function finds the node with the minimum key value and splays it to the
*root. Returns an iterator to the item with the minimum value key.
*/
template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMin() {
  //if tree is empty, return null
  if (BinarySearchTree<Key, Value>::mRoot == NULL) {
    return NULL;
  }
  //we have a helper function from the bst class to find the smallest node
  Node<Key,Value>* smallest = BinarySearchTree<Key, Value>::getSmallestNode();
  splay(smallest);
  return typename BinarySearchTree<Key, Value>::iterator::iterator(smallest);
}

/**
*This function finds the node with the maximum key value and splays it to the
*root. Returns an iterator to the item with the maximum value key.
*/
template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMax() {
  //if tree is empty, return null
  if (BinarySearchTree<Key, Value>::mRoot == NULL) {
    return NULL;
  }
  //we made a helper function within splayTree to getLargestNode
  Node<Key,Value>* largest = getLargestNode();
  splay(largest);
  return typename BinarySearchTree<Key, Value>::iterator::iterator(largest);
}

/**
*This function splays a given node to the root of the splayTree.
*/
template <typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node<Key, Value> *r) {
  //this should never happen, but just in case we put this here
  if (r == NULL) {
    return;
  }

  splayHelper(r);
}

/**
*Recursive helper for splay()
*/
template <typename Key, typename Value>
void SplayTree<Key, Value>::splayHelper(Node<Key, Value> *r) {
  //base case (r is now root)
  if (r->getParent() == NULL) {
    BinarySearchTree<Key, Value>::mRoot = r;
    return;
  }

  Node<Key, Value>* rParent = r->getParent();

  //zig (if r has no grandparent we know it is a zig case)
  if (rParent->getParent() == NULL) {
    //determine if r is left or right child, then rotate accordingly
    if (rParent -> getLeft() == r) {
      //left child, rotate parent right
      rotateBST<Key, Value>::rightRotate(rParent);
    } else {
      //right child, rotate parent left
      rotateBST<Key, Value>::leftRotate(rParent);
    }

    //zig cases only happen when r is about to become root, so now that r is
    //root no recursive call is needed
    BinarySearchTree<Key, Value>::mRoot = r;
    return;
  }

  Node<Key, Value>* rGrandParent = rParent->getParent();

  //zig zig (if rParent and r are both right or left children)
  if ((rGrandParent->getLeft() == rParent && rParent -> getLeft() == r) ||
  (rGrandParent->getRight() == rParent && rParent -> getRight() == r)) {
    //determine if zig zig is left or right, then rotate accordingly
    if (rParent -> getLeft() == r) {
      //left zig zig, rotate rGrandParent right then rParent right
      rotateBST<Key, Value>::rightRotate(rGrandParent);
      rotateBST<Key, Value>::rightRotate(rParent);
    } else {
      //right zig zig, rotate rGrandParent left then rParent left
      rotateBST<Key, Value>::leftRotate(rGrandParent);
      rotateBST<Key, Value>::leftRotate(rParent);
    }
    //there is a possibility that r is not root yet so it needs to be splayed
    //more, so we recursive call here
    splayHelper(r);
    return;
  }

  //zig zag
  if ((rGrandParent->getLeft() == rParent && rParent -> getRight() == r) ||
  (rGrandParent->getRight() == rParent && rParent -> getLeft() == r)) {
    //determine orientation of zig zag, then rotate accordingly
    if (rParent -> getLeft() == r) {
      //zig zag is right left, so rotate parent right then grandparent left
      rotateBST<Key, Value>::rightRotate(rParent);
      rotateBST<Key, Value>::leftRotate(rGrandParent);
    } else {
      //zig zag is left right, so rotate parent left then grandparent right
      rotateBST<Key, Value>::leftRotate(rParent);
      rotateBST<Key, Value>::rightRotate(rGrandParent);
    }
    //there is a possibility that r is not root yet so it needs to be splayed
    //more, so we recursive call here
    splayHelper(r);
    return;
  }
}

/**
*Searches for node with cooresponding key, if found returns pointer to node,
*if not found returns the last accessed node
*/
template <typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::modifiedSearch(const Key& key) {
  Node<Key, Value>* currentNode = BinarySearchTree<Key, Value>::mRoot;
  while (currentNode != NULL) {
    if (currentNode -> getKey() == key) {
      return currentNode;
    }
    else if (currentNode -> getKey() < key) {
      //if this conditional is satisfied, then we know that the node we're
      //looking for is not in the tree, so we return the last accessed node
      if (currentNode -> getRight() == NULL) {
        return currentNode;
      }
      currentNode = currentNode -> getRight();
    }
    else if (currentNode -> getKey() > key) {
      //if this conditional is satisfied, then we know that the node we're
      //looking for is not in the tree, so we return the last accessed node
      if (currentNode -> getLeft() == NULL) {
        return currentNode;
      }
      currentNode = currentNode -> getLeft();
    }
  }
  return NULL;
}

/**
*Returns largest leaf node
*/
template <typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::getLargestLeaf() {
  Node<Key, Value>* currentNode = BinarySearchTree<Key, Value>::mRoot;
  //if tree is empty return null
  if (currentNode == NULL) {
    return NULL;
  }
  //while currentNode isnt a leaf node
	while (!(currentNode -> getRight() == NULL && currentNode -> getLeft() ==
                                                                      NULL)){
    //if we can go right, go right, otherwise if we can go left then go left
    if (currentNode -> getRight() != NULL) {
      currentNode = currentNode -> getRight();
    } else if (currentNode -> getLeft() != NULL) {
      currentNode = currentNode -> getLeft();
    }
	}
	return currentNode;
}

/**
*Returns smallest leaf node
*/
template <typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::getSmallestLeaf() {
  Node<Key, Value>* currentNode = BinarySearchTree<Key, Value>::mRoot;
  //if tree is empty return null
  if (currentNode == NULL) {
    return NULL;
  }
  //while currentNode isnt a leaf node
	while (!(currentNode -> getRight() == NULL && currentNode -> getLeft() ==
                                                                      NULL)){
    //if we can go left, go left, otherwise if we can go right then go right
    if (currentNode -> getLeft() != NULL) {
      currentNode = currentNode -> getLeft();
    } else if (currentNode -> getRight() != NULL) {
      currentNode = currentNode -> getRight();
    }
	}
	return currentNode;
}

/**
*Returns largest node
*/
template <typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::getLargestNode() {
  Node<Key, Value>* currentNode = BinarySearchTree<Key, Value>::mRoot;
	while (currentNode -> getRight() != NULL) {
		currentNode = currentNode -> getRight();
	}
	return currentNode;
}

#endif
