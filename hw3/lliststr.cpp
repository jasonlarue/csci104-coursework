/*
PLEASE NOTE:
In homework 2, I used a helper function called getItem. However, I've edited
this file so that the cases which will be used in this homework (when pos == 0
or when size == 0 or size ==1) do not use getItem just to ensure that they
run in constant time. Please disregard any remaining functions that use getItem
as those blocks of code do not run in this implementation of the class due to
the nature of the assignment.
*/
#include "lliststr.h"
#include <string>


/**
 * Default constructor
 */
LListStr::LListStr() {
  size_ = 0;
}

/**
 * Destructor
 */
LListStr::~LListStr() {
  //free memory
  Item* currentItem = head_;
  for (int i = 0; i < (size_); i++) {
    Item* tempItem = currentItem -> next;
    delete currentItem;
    currentItem = tempItem;
  }
}

/**
 * Returns the current number of items in the list
 */
int LListStr::size() const {
  return size_;
}

/**
 * Returns true if the list is empty, false otherwise
 */
bool LListStr::empty() const {
  if (size_ == 0) {
    return true;
  } else {
    return false;
  }
}

/**
 * Inserts val so it appears at the index given as pos. If the
 * index pos is invalid, this function should return without
 * modifying the list.
 */
void LListStr::insert(int pos, const std::string &val) {
  //first check if pos isnt valid
  if (pos < 0 || pos > size_) {
    return;
  }

  Item* toBeAdded = new Item();
  toBeAdded -> val = val;

  //if this is the initial element in list
  if (size_ == 0) {
    toBeAdded -> prev = toBeAdded;
    toBeAdded -> next = toBeAdded;

    head_ = toBeAdded;
    tail_ = toBeAdded;
  }

  else if (pos == 0) {
    toBeAdded -> prev = tail_;
    toBeAdded -> next = head_;

    head_ -> prev = toBeAdded;
    tail_ -> next = toBeAdded;

    head_ = toBeAdded;
  }

  else if (pos == size_) {
    toBeAdded -> prev = getItem(pos-1);
    toBeAdded -> next = head_;

    head_ -> prev = toBeAdded;
    getItem(pos-1) -> next = toBeAdded;

    tail_ = toBeAdded;
  }

  else {
    toBeAdded -> prev = getItem(pos-1);
    toBeAdded -> next = getItem(pos);

    getItem(pos) -> prev = toBeAdded;
    getItem(pos-1) -> next = toBeAdded;
  }

  size_++;
  return;
}

/**
 * Removes the value at the index given by pos. If the
 * index pos is invalid, this function should return without
 * modifying the list.
 */
void LListStr::remove(int pos) {
  //first check if pos isnt valid
  if (pos < 0 || pos > size_) {
    return;
  }

  if (size_ == 1) {
    delete getItem(pos);
    head_ = NULL;
    tail_ = NULL;
  }

  else if (pos == 0) {
    Item* toBeDeleted = head_;
    Item* willBeNewHead = head_ -> next;
    head_ -> next -> prev = tail_;
    tail_ -> next = head_ -> next;
    delete toBeDeleted;
    head_ = willBeNewHead;
  }

  else if (pos == size_) {
    Item* toBeDeleted = getItem(pos);
    Item* willBeNewTail = getItem(pos-1);
    head_ -> prev = getItem(pos-1);
    getItem(pos-1) -> next = head_;
    delete toBeDeleted;
    tail_ = willBeNewTail;
  }

  else {
    Item* toBeDeleted = getItem(pos);
    getItem(pos+1) -> prev = getItem(pos-1);
    getItem(pos-1) -> next = getItem(pos+1);
    delete toBeDeleted;
  }

  size_--;
  return;
}

/**
 * Overwrites the old value at the index given by pos with val. If the
 * index pos is invalid, this function should return without
 * modifying the list.
 */
void LListStr::set(int pos, const std::string &val) {
  //first check if pos isnt valid
  if (pos < 0 || pos > size_) {
    return;
  }

  if (pos == 0) {
    head_ -> val = val;
  }

  getItem(pos) -> val = val;

  return;
}

/**
 * Returns the value at the index given by pos.  If the index pos is invalid,
 * then you should return the empty string.
 */
std::string LListStr::get(int pos) const {
  //first check if pos isnt valid
  if (pos < 0 || pos > size_) {
    return "";
  }

  if (pos == 0) {
    return head_ -> val;
  }

  return getItem(pos) -> val;
}


LListStr::Item* LListStr::getItem (int pos) const {
  if (pos < 0 || pos >= size_) {
    return NULL;
  }

  Item* currentItem = head_;
  for (int i = 0; i < pos; i++) {
    currentItem = currentItem -> next;
  }
  return currentItem;
}
