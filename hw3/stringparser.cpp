#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include "stackstr.h"

using namespace std;

/* Here's an overview of how this program runs:
We getline each line of the file, remove all spaces, and then put the entire
line into MasterStack. Then, scanner is run which finds a subset of MasterStack
to begin parsing, puts it in stack, and removes it from masterStack
(for example, if our input is (something + (hi+there)), after scanner is run
masterStack contains (something + ) and stack contains hi+there). Stack is then
parsed by the logic within the while loop with the help of some helper functions
too. At the end of this while loop, the parsed result of whatever was in stack
gets put back where it came from into masterStack (in our example, MasterStack
would now read (something + hithere)) and then scanner is run again until it
detects there are no more subsets of masterStack stack to parse, at which point
stack is parsed one more time and then whatever is left on the stack is then
written as output.This all happens within a while loop that runs while(getline).
*/

//this function takes a string as an input and pushes it to the stack
//broken apart into individual single character strings
void pushStringAsChars(string toBePushed, StackStr* stack) {
  for (size_t i = 0; i < toBePushed.length(); i++) {
    char pushChar = toBePushed[i];
    string pushString = "";
    pushString = pushChar;
    stack -> push(pushString);
  }
}

string reverseString(string toBeReversed) {
  string reversed = "";
  for (size_t i = 0; i < toBeReversed.length(); i++) {
    reversed = (toBeReversed[i]) + reversed;
  }
  return reversed;
}

// this function is only used for debugging, please disregard
void printStack(StackStr* stack) {
  int staticSize = stack -> size();
  StackStr* soManyStacks = new StackStr();
  for (int i = 0; i < staticSize; i++) {
    soManyStacks -> push(stack -> top());
    cout << soManyStacks -> top() << endl;
    stack -> pop();
  }
  for (int j = 0; j < staticSize; j++) {
    stack -> push(soManyStacks -> top());
    soManyStacks -> pop();
  }
  delete soManyStacks;
}

//takes a stack and removes all instances of specified string
void popFromStack(StackStr* stack, string toPop) {
  int staticSize = stack -> size();
  StackStr* soManyStacks = new StackStr();
  for (int i = 0; i < staticSize; i++) {
    if (stack -> top() != toPop) {
      soManyStacks -> push(stack -> top());
    }
    stack -> pop();
  }
  for (int j = 0; j < staticSize; j++) {
    stack -> push(soManyStacks -> top());
    soManyStacks -> pop();
  }
  delete soManyStacks;
}

//takes a stack and pops num items, if num = -1 pops everything
void popStack (StackStr* toBeCleared, int num) {
  if (toBeCleared -> size() == 0) {
    return;
  }
  int index = num;
  if (num == -1) index = toBeCleared -> size();
  for (int i = 0; i < index; i++) {
    toBeCleared -> pop();
  }
}

//this function scans for a pair of parentheses in masterStack, and if it finds
//a pair it puts the pair and everything inside it into stack, and makes
//masterStack the total expression excluding the subexpression now in stack
//returns 0 for no parentheses, 1 for pair of parentheses, and -1 for a
//non-matching pair, also returns -1 if it finds + or - without a parentheses,
//also returns -1 for parentheses with no + or -
//posInMaster is set to the position where the subexpression now in stack
//lies inside of masterStack
int scanner(StackStr* masterStack, StackStr* stack, int &posInMaster) {
  //begin by making sure stack is empty
  popStack(stack,-1);
  int staticSize = masterStack -> size();
  int foundOpen = -1;
  int foundClosed = -1;
  bool foundPlusOrMinus = false;
  StackStr* scannerAuxStack = new StackStr();

  for (int i = 0; i < staticSize; i++) {
    if (masterStack -> top() == ")") foundClosed = staticSize - i;
    if (masterStack -> top() == "(") foundOpen = staticSize - i;
    if (masterStack -> top() == "+"
      || masterStack -> top() == "-") foundPlusOrMinus = true;
    scannerAuxStack -> push(masterStack -> top());
    masterStack -> pop();
    if (foundOpen != -1) break;
  }

  //now make stack contain the values in the parentheses, and make masterStack
  //contain everything except that
  int open, closed;
  if (foundOpen != -1 && foundClosed != -1) {
    open = foundOpen;
    closed = foundClosed;
  }

  //in case of no parentheses, put everything into stack
  if (foundOpen == -1 && foundClosed == -1) {
    closed = staticSize+1;
    open = 0;
  }

  if ((foundOpen != -1 && foundClosed != -1) ||
  (foundOpen == -1 && foundClosed == -1)) {

    if (foundOpen != -1 && foundClosed != -1) scannerAuxStack -> pop();
    //do this to get rid of (

    for (int j = 0; j < (closed-open)-1; j++) { //minus one for (
      stack -> push(scannerAuxStack -> top());
      scannerAuxStack -> pop();
    }

    if (foundOpen != -1 && foundClosed != -1) scannerAuxStack -> pop();
    //do this to get rid of )

    int remainderOfAuxStack = scannerAuxStack -> size();
    for (int k = 0; k < remainderOfAuxStack; k++) {
      masterStack -> push(scannerAuxStack -> top());
      scannerAuxStack -> pop();
    }
  }

  posInMaster = foundOpen - 1;
  delete scannerAuxStack;

  //if we found () but no + or -
  if (foundOpen != -1 && foundClosed != -1 && !foundPlusOrMinus) return -1;
  //if we found no () but found a + or -
  else if (foundOpen == -1 && foundClosed == -1 && foundPlusOrMinus) return -1;
  //if we found (), but masterStack is now empty (this will be last run)
  else if(masterStack -> size() == 0
  && foundOpen != -1 && foundClosed != -1) return 0;
  else if (foundOpen != -1 && foundClosed != -1) return 1;
  else if (foundOpen == -1 && foundClosed == -1) return 0;
  else return -1;
}

//this function returns true if symbol1 or 2 is in the stackToScan, otherwise
//it returns false
bool auxScanner(StackStr* stackToScan, string symbol1, string symbol2) {
  int staticSize = stackToScan -> size();
  int result = 0;
  //this stack is needed to help return stackToScan to its original state
  StackStr* tooManyAuxStacks = new StackStr;
  for (int i = 0; i < staticSize; i++) {
    tooManyAuxStacks -> push(stackToScan -> top());
    if (stackToScan -> top() == symbol1 || stackToScan -> top() == symbol2) {
      result = 1;
    }
    stackToScan -> pop();
  }

  for (int j = 0; j < staticSize; j++) {
    stackToScan -> push(tooManyAuxStacks -> top());
    tooManyAuxStacks -> pop();
  }
  delete tooManyAuxStacks;
  return result;
}

//this function is used by the angle bracket part of the program,
//it takes a stack (the whileLoopAuxStack) as an input and returns the string
//that the angle brackets should subtract from, we know we've found this string
//when we encounter a +, -, or the end of the stack
string parserForAngleBrackets(StackStr* stackToScan) {
  int staticSize = stackToScan -> size();
  string result;
  //this stack is needed to help return stackToScan to its original state
  StackStr* tooManyAuxStacks = new StackStr;

  for (int i = 0; i < staticSize; i++) {

    if (stackToScan -> top() == "+" || stackToScan -> top() == "-") {
      break;
    }

    tooManyAuxStacks -> push(stackToScan -> top());
    stackToScan -> pop();
  }

  int remainderOfAuxStack = tooManyAuxStacks -> size();
  for (int j = 0; j < remainderOfAuxStack; j++) {
    result = tooManyAuxStacks -> top() + result;
    tooManyAuxStacks -> pop();
  }
  delete tooManyAuxStacks;
  return result;
}

//this function is used by the plus minus part of the program, it takes stack
//as an input and returns the two terms on either side of the + or - sign
//it returns 1 for addition, 2 for subtraction, 0 if there is no + or -,
//and -1 for malformed
int parserForPlusMinus(StackStr* stack, string &term1, string &term2) {
  term1 = "";
  term2 = "";
  int foundPlus = -1;
  int foundMinus = -1;
  int staticSize = stack -> size();
  StackStr* tooManyAuxStacks = new StackStr();
  for (int i = 0; i < staticSize; i++) {
    if (stack -> top() == "+") {
      if (foundPlus == -1) {
        foundPlus = staticSize  -1 - i;
      } else {
        int offset = stack -> size();
        foundPlus=foundPlus - offset;
        break;
      }//this ensures that the first plus encountered is chosen
    }
    if (stack -> top() == "-") {
      //this makes sure there isn't more than one - sign
      if (foundMinus == -1) {
        foundMinus = staticSize -1 - i;
      } else {
        delete tooManyAuxStacks;
        return -1;
      }
    }
    tooManyAuxStacks -> push(stack -> top());
    stack -> pop();
  }

  //if there was no plus or minus, return stack to original state and return 0
  if (foundPlus == -1 && foundMinus == -1) {
    for (int k = 0; k < staticSize; k++) {
      stack -> push(tooManyAuxStacks -> top());
      tooManyAuxStacks -> pop();
    }
    delete tooManyAuxStacks;
    return 0;
  }
  if (foundPlus != -1 && foundMinus != -1) {
    delete tooManyAuxStacks;
    return -1;
  }

  int signIndex;
  if (foundPlus != -1) signIndex = foundPlus;
  else if (foundMinus != -1) signIndex = foundMinus;

  staticSize = tooManyAuxStacks -> size();
  for (int j = 0; j < staticSize; j++) {
    if (j < signIndex) {
      term1 = term1 + tooManyAuxStacks -> top();
    }
    if (j == signIndex) {

    }
    if (j > signIndex) {
      if (tooManyAuxStacks -> top() != "+") {
        term2 = term2 + tooManyAuxStacks -> top();
      } /* else {
        //if we find another + sign, put the rest of the stack back and return 1
        for (int l = 0; l < staticSize-j; l++) {
        stack -> push(tooManyAuxStacks -> top());
        tooManyAuxStacks -> pop();
      }
      return 1;
    } */
  }
  tooManyAuxStacks -> pop();
}

delete tooManyAuxStacks;
//if one of the terms is empty, this counts as malformed
if (term1 == "" || term2 == "") return -1;
if (foundPlus != -1) return 1;
else if (foundMinus != -1) return 2;

return -1;
}

//returns true if stack has invalid characters in it (malformed)
bool hasInvalidChars(StackStr* stack) {
  int staticSize = stack -> size();
  StackStr* theLastAuxStack = new StackStr();
  for (int i = 0; i < staticSize; i++) {

    //this code is to help evaluate if there are capital letters present
    string stackTopTempString = stack -> top();
    char stackTopAsChar = stackTopTempString[0];
    //if we find anything besides lowercase letters and allowed characters,
    //malformed
    if (!((stackTopAsChar >= 'a' && stackTopAsChar <= 'z')
    || stackTopAsChar == '(' || stackTopAsChar == ')'
    || stackTopAsChar == '<' || stackTopAsChar == '>'
    || stackTopAsChar == '+' || stackTopAsChar == '-'
    || stackTopAsChar == ' ')) {
      delete theLastAuxStack;
      return true;
    }
    theLastAuxStack -> push(stack->top());
    stack -> pop();
  }
  for (int j = 0; j < staticSize; j++) {
    stack -> push(theLastAuxStack -> top());
    theLastAuxStack -> pop();
  }
  delete theLastAuxStack;
  return false;
}

int main(int argc, char *argv[]) {

  if (argc < 3) {
    cout << "Please provide both input and output file names" << endl;
    return 1;
  }

  ifstream ifile;
  ifile.open(argv[1]);
  if (ifile.fail()) {
    cout << "File read error" << endl;
    return 1;
  }

  ofstream ofile(argv[2]);

  string rawInput;
  string output;
  bool fileIsJustEmpty = true;

  while (getline(ifile, rawInput)) {
    fileIsJustEmpty = false;

    StackStr* masterStack = new StackStr();
    StackStr* stack = new StackStr();

    string parsedInput = "";

    //this gets rid of whitespace in rawInput
    for (size_t h = 0; h < rawInput.length(); h++) {
      if (rawInput[h] != ' ') parsedInput = parsedInput +  rawInput[h];
    }

    stringstream input;
    input << parsedInput;

    size_t len = input.str().length();
    for (size_t i = 0; i < len; i++) {
      char c;
      input >> c;
      string s = "";
      s = c;
      masterStack -> push(s);
    }

    int resultOfScan = 1;
    int posInMaster = -1;

    //if the masterStack has any invalid chars, don't even bother running
    //the loop and just write malformed
    if (hasInvalidChars(masterStack)) {
      resultOfScan = -1;
      output = "Malformed";
    }

    //if masterStack is empty, malformed
    if (masterStack -> size() == 0) {
      resultOfScan = -1;
      output = "Malformed";
    }

    while (resultOfScan == 1) {
      //make sure it's not malformed before continuing
      resultOfScan = scanner(masterStack, stack, posInMaster);
      if (resultOfScan == -1) {
        output = "Malformed";
        break;
      }

      //first do all < and > operators, don't continue until there's none left
      if (auxScanner(stack, "<",">")) {
        StackStr* whileLoopAuxStack = new StackStr();
        do {
          if (stack -> top() == "<") {
            popStack(stack,1); //this gets rid of the < we just found

            if (stack -> size() != 0) {
              string stackTopTempString = stack -> top();
              char stackTopAsChar = stackTopTempString[0];
              //if we find lowercase letters then malformed
              if (stackTopAsChar >= 'a' && stackTopAsChar <= 'z') {
                output = "Malformed";
                break;
              }
            }

            int staticSize = whileLoopAuxStack -> size();
            string result;
            string toBeModified = parserForAngleBrackets(whileLoopAuxStack);
            if (toBeModified == "") {
              output = "Malformed";
              break;
            }
            size_t sizeOfString = toBeModified.size();
            if (sizeOfString > 1) {
              for (size_t i = 0; i < sizeOfString-1; i++) {
                result = result + toBeModified[i];
              }
            } else {
              result = toBeModified;
            }


            pushStringAsChars(reverseString(result), whileLoopAuxStack);
            staticSize = whileLoopAuxStack -> size();
            for (int j = 0; j < staticSize; j++) {
              stack -> push(whileLoopAuxStack -> top());
              whileLoopAuxStack -> pop();
            }
          }

          else if (stack -> top() == ">") {
            popStack(stack,1); //this gets rid of the > we just found

            if (stack -> size() != 0) {
              string stackTopTempString = stack -> top();
              char stackTopAsChar = stackTopTempString[0];
              //if we find lowercase letters then malformed
              if (stackTopAsChar >= 'a' && stackTopAsChar <= 'z') {
                output = "Malformed";
                break;
              }
            }

            int staticSize = whileLoopAuxStack -> size();
            string result;
            string toBeModified = parserForAngleBrackets(whileLoopAuxStack);
            if (toBeModified == "") {
              output = "Malformed";
              break;
            }
            size_t sizeOfString = toBeModified.size();
            if (sizeOfString != 1) {
              for (size_t i = 1; i < sizeOfString; i++) {
                result = result + toBeModified[i];
              }
            } else {
              result = toBeModified;
            }

            pushStringAsChars(reverseString(result), whileLoopAuxStack);
            staticSize = whileLoopAuxStack -> size();
            for (int j = 0; j < staticSize; j++) {
              stack -> push(whileLoopAuxStack -> top());
              whileLoopAuxStack -> pop();
            }
          }

          else {
            whileLoopAuxStack -> push(stack -> top());
            stack -> pop();
          }

        } while (auxScanner(stack,"<",">"));

        if (output == "Malformed") {
          delete whileLoopAuxStack;
          break;
        }

        int staticSize = whileLoopAuxStack -> size();
        for (int n = 0; n < staticSize; n++) {
          stack -> push(whileLoopAuxStack -> top());
          whileLoopAuxStack -> pop();
        }
        delete whileLoopAuxStack;
      }

      string term1, term2;
      int plusMinusResult = parserForPlusMinus(stack,term1,term2);
      if (plusMinusResult == -1) {

        output = "Malformed";
        break;
      }
      if (plusMinusResult == 2) {
        size_t subIndex = term1.find(term2);
        if (subIndex >= 0) {
          term1.erase(subIndex,term2.length());
        }
        pushStringAsChars(term1,stack);

      } else if (plusMinusResult == 1) {
        int parserResult;
        do {
          pushStringAsChars(term1+term2,stack);
        } while((parserResult = parserForPlusMinus(stack,term1,term2)) == 1);
        if (parserResult == -1) {
          output = "Malformed";
          break;
        }
      }





      if (resultOfScan == 0) {
        string contentsOfStack = "";
        int staticSize = stack -> size();
        for (int m = 0; m < staticSize; m++) {
          contentsOfStack = stack -> top() + contentsOfStack;
          stack -> pop();
        }
        output = contentsOfStack;
        break;
      }

      //if we get here, we have more to do,
      //so we put what's in stack back in master stack,
      //but we have to be mindful of the subsection's pos in masterStack

      //pop numToPopFromMaster off of master, add what's in stack, then put
      //what's in finalAuxStack back into master
      int numToPopFromMaster = masterStack -> size() - posInMaster;
      StackStr* finalAuxStack = new StackStr();
      for (int a = 0; a < numToPopFromMaster; a++) {
        finalAuxStack -> push(masterStack -> top());
        masterStack -> pop();
      }

      string contentsOfStack;
      int staticSize = stack -> size();
      for (int m = 0; m < staticSize; m++) {
        contentsOfStack = contentsOfStack + stack -> top();
        stack -> pop();
      }
      pushStringAsChars(reverseString(contentsOfStack), masterStack);

      for (int b = 0; b < numToPopFromMaster; b++) {
        masterStack -> push(finalAuxStack -> top());
        finalAuxStack -> pop();
      }
      delete finalAuxStack;
    }
    delete masterStack;
    delete stack;

    ofile << output << endl;

    output = "";
    rawInput = "";
  }

  if (fileIsJustEmpty) {
    output = "Malformed";
    ofile << output << endl;
  }

  return 0;
}
