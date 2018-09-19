#include <iostream>

using namespace std;


struct Node {
  int value;
  Node* next;
};

Node* fullsort (Node* in);
void checkSort (Node* in);

Node* fullsort (Node* in) {

  //check if we have an empty list
  if (in == NULL) {
    return NULL;
  }

  //check if we're at the end of our list, this is the base case
  if (in -> next == NULL) {
    return in;
  }

  //if current value is less than or equal to next value, no swap needed,
  //simply call fullsort again with n-1 size list
  if (in -> value <= in -> next -> value) {
    fullsort(in -> next);
  }
  //this means current value is greater than next value, swap values before
  //recursive call
  else {
    int temp = in -> next -> value;
    in -> next -> value = in -> value;
    in -> value = temp;
    fullsort(in);
  }

  checkSort(in);

  return in;
}

//this function checks if our list is sorted, if it isn't it calls fullsort
//again
void checkSort (Node* in) {
  //if this is last element in list, return (base case)
  if (in -> next == NULL) {
    return;
  }

  if (in -> value <= in -> next -> value) {
    checkSort(in -> next);
  }

  else {
    fullsort(in);
  }
}
