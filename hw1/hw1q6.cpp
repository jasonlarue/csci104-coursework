#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <vector>

using namespace std;

void helper (ifstream* ifile) {
  string tempString;
  *ifile >> tempString;
  if (!ifile -> fail()) {
    helper(ifile);
  } else {
    return;
  }
  cout << tempString << ' ';
}

int main (int argc, char* argv[]) {
  ifstream ifile;
  ifile.open(argv[1]);
  if (ifile.fail()) {
    cout << "File read error" << endl;
    return -1;
  }

  // this is to get rid of the int at the beginning of file, we dont need it
  ifile.ignore();

  helper(&ifile);
  
  ifile.close();
  cout << endl;
  return 0;
}
