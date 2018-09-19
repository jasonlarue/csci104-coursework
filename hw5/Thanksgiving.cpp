#include <vector>
#include <utility>
#include <functional>
#include <iostream>
#include "Thanksgiving.h"
#include "qsort.h"

using namespace std;

vector<pair<int,int> > assignPlates(vector<int> turkeys, vector<int> potatoes) {
  vector<pair<int,int> > result;
  cout << "hello" << endl;
  //if inputs arent same size, return empty vector
  if (turkeys.size() != potatoes.size()) {
    //THROW LENGTH MISMATCH
    return result;
  }

  QuickSort (turkeys,less<int>());
  QuickSort (potatoes,less<int>());

  int sumOfCalories = potatoes[0] + turkeys[turkeys.size()-1];

  for (size_t i = 0; i < turkeys.size(); i++) {
    cout << "hi" << endl;
    //this ensures all sums of calories will be the same
    if (potatoes[i] + turkeys[turkeys.size()-i-1] != sumOfCalories) {
      vector<pair<int,int> > empty;
      return empty;
    }
    pair<int,int> newPair;
    newPair.first = potatoes[i];
    newPair.second = turkeys[turkeys.size()-i-1];
    result.push_back(newPair);

  }

  return result;
}
