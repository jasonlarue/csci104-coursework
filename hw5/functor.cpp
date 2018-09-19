#include "functor.h"

using namespace std;

bool NumStrComp::operator() (const std::string& lhs, const std::string& rhs) {
  int leftHandSum = 0;
  for (size_t i = 0; i < lhs.size(); i++) {
    //this is the default value if the char is invalid
    int charValue = 0;
    //if char is between 0 and 9
    if (lhs[i] > 47 && lhs[i] < 58) {
      charValue = lhs[i] - 48;
    }
    //if char is between A and Z
    else if (lhs[i] > 64 && lhs[i] < 91) {
      charValue = lhs[i] - 55;
    }
    //if char is between a and z
    else if (lhs[i] > 96 && lhs[i] < 123) {
      charValue = lhs[i] - 87;
    }
    leftHandSum = leftHandSum + charValue;
  }

  int rightHandSum = 0;
  for (size_t i = 0; i < rhs.size(); i++) {
    //this is the default value if the char is invalid
    int charValue = 0;
    //if char is between 0 and 9
    if (rhs[i] > 47 && rhs[i] < 58) {
      charValue = rhs[i] - 48;
    }
    //if char is between A and Z
    else if (rhs[i] > 64 && rhs[i] < 91) {
      charValue = rhs[i] - 55;
    }
    //if char is between a and z
    else if (rhs[i] > 96 && rhs[i] < 123) {
      charValue = rhs[i] - 87;
    }
    rightHandSum = rightHandSum + charValue;
  }

  //this breaks ties with standard comparator
  if (leftHandSum==rightHandSum) {
    return lhs < rhs;
  }
  else {
    return leftHandSum < rightHandSum;
  }
}
