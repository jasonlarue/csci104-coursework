#include "lliststr.h"
#include <iostream>
#include <string>

using namespace std;

void compareInt (int value, int expected, int testNumber) {
  if (value == expected) {
    cout << "Success! Test " << testNumber << " passed." << endl;
  } else {
    cout << "Error! Test " << testNumber << " failed. Expected: "
    << expected << ", found: " << value << "." << endl;
  }
}

void compareString (string value, string expected, int testNumber) {
  if (value == expected) {
    cout << "Success! Test " << testNumber << " passed." << endl;
  } else {
    cout << "Error! Test " << testNumber << " failed. Expected: "
    << expected << ", found: " << value << "." << endl;
  }
}

int main() {
  LListStr* testList = new LListStr();

  //checking if list is empty
  compareInt(testList -> empty(), true, 1);
  compareInt(testList -> size(), 0, 2);

  //begin by populating the list
  testList -> insert(0,"Hello");
  testList -> insert(0,"Hi");
  testList -> insert(2,"Hey");
  testList -> insert(1,"Yo");

  //check to make sure the values were added correctly
  compareInt(testList -> empty(), false, 3);
  compareInt(testList -> size(), 4, 4);
  compareString(testList -> get(0), "Hi", 5);
  compareString(testList -> get(1), "Yo", 6);
  compareString(testList -> get(2), "Hello", 7);
  compareString(testList -> get(3), "Hey", 8);

  //verify that set function works
  testList -> set(1,"Hola");
  compareString(testList -> get(1),"Hola", 9);

  //verify that remove function works
  testList -> remove(1);
  compareInt(testList -> size(), 3,10);
  compareString(testList -> get(1),"Hello",11);

  //verify that member functions handle invalid pos input correctly
  testList -> insert(5,"Nope");
  compareInt(testList -> size(), 3,12);
  testList -> set(5,"Nah");
  compareString(testList -> get(5), "", 13);
  testList -> remove(5);
  compareInt(testList -> size(), 3,14);

  //add one more item so all cases of remove() can be tested
  testList -> insert(1,"Hiya");

  //finally, remove all elements and verify that list is empty
  testList -> remove(2);
  testList -> remove(3);
  testList -> remove(0);
  testList -> remove(0);
  compareInt(testList -> empty(), true, 15);
  compareInt(testList -> size(), 0, 16);

  delete testList;
  
  return 0;
}
