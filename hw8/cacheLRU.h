#ifndef cLRU
#define cLRU

#include "splayTree.h"
#include <stdexcept>

template <typename Key, typename Value>
class cacheLRU: public SplayTree<Key, Value> {
public:
  cacheLRU(int capacity);
  ~cacheLRU();
  void put(const std::pair<const Key, Value>& keyValuePair);
  std::pair<const Key, Value> get(const Key& key);
private: 
  int _capacity = 0;
  int _capacity_used = 0;
};

/**
*A constructor that takes as an argument the capacity of the cache. You may
*assume that the capacity given is always an integer greater than or equal to 1.
*/
template <typename Key, typename Value>
cacheLRU<Key,Value>::cacheLRU(int capacity) {
  _capacity = capacity;
}

/**
*Destructor
*/
template <typename Key, typename Value>
cacheLRU<Key,Value>::~cacheLRU() {

}

/**
*This function will insert the keyValuePair into the cache. If the cache has
*reached its capacity, then one of the least recently used elements (LRU)
*should be removed from the cache. For a splay tree implementation, this would
*normally be any leaf node. However, we are asking that you remove the leaf
*with the minimum value key. This operation should work in amortized O(log n)
*time where n is the number of elements in the cache.
*/
template <typename Key, typename Value>
void cacheLRU<Key,Value>::put(const std::pair<const Key, Value>& keyValuePair) {
  //if there is no capacity left and if this element isn't already in the tree,
  //then remove the smallest leaf before inserting

  Node<Key,Value>* foundNode =
            BinarySearchTree<Key,Value>::internalFind(keyValuePair.first);

  if (_capacity <= _capacity_used && foundNode == NULL) {
    SplayTree<Key, Value>::deleteMinLeaf();
    _capacity_used--;
  }

  SplayTree<Key, Value>::insert(keyValuePair);
  //only increment _capacity_used if the key wasn't in the tree
  if (foundNode == NULL) {
    _capacity_used++;
  }
}

/**
*This function will first find a node with the specified key in the tree and
*return the key/value pair. If the key is not found, throw a logic_error
*exception. This operation should work in amortized O(log n) time where n is
*the number of elements in the cache. If the element with the key is the most
*recently used, this operation will take O(1) time.
*/
template <typename Key, typename Value>
std::pair<const Key, Value> cacheLRU<Key,Value>::get(const Key& key) {
  Node<Key,Value>* foundNode = BinarySearchTree<Key,Value>::internalFind(key);
  //if we didnt find the key, throw logic_error exception
  if (foundNode == NULL) {
    throw std::logic_error("Key not found");
  }
  //access the keyValuePair, then return it
  return foundNode -> getItem();
}

#endif
