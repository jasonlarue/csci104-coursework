#include "lliststr.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  ifstream ifile;
  ifile.open(argv[1]);
  if (ifile.fail()) {
    cout << "File error" << endl;
    return 1;
  }

  LListStr* list = new LListStr();
  string command;

  while (ifile >> command) {
    if (command == "ADD") {
      int pos;
      string playerName;
      ifile >> pos >> playerName;
      list -> insert(pos, playerName);

    } else if (command == "ACT") {
      //first make sure there isnt only one player in the list
      if (list -> size() == 1) {
        break;
      }

      int pos, toBeAssassinated;
      ifile >> pos;

      //if pos is invalid, do nothing
      if (pos > (list -> size()-1) || pos < 0) {
        break;
      }

      //if player is at end of list, we have to manually loop around
      if (pos == (list -> size()-1)) {
        toBeAssassinated = 0;
      } else {
        toBeAssassinated = pos+1;
      }

      cout << "Assassinated: " << list -> get(toBeAssassinated) << endl;
      list -> remove(toBeAssassinated);

    } else if (command == "REPLACE") {
      int pos;
      string playerName;
      ifile >> pos >> playerName;
      list -> set(pos,playerName);
    } else {
      cout << "Command error, only use ADD ACT and REPLACE" << endl;
    }
  }

  if (list -> size() == 1) {
    cout << "Winner: " << list -> get(0) << endl;
  } else {
    cout << "Remaining players: " << list -> size() << endl;
    for (int i = 0; i < list->size(); i++) {
      cout << list -> get(i) << endl;
    }
  }

  delete list;

  return 0;
}
