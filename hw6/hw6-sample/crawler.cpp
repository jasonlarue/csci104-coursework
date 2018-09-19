#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <unordered_set>

using namespace std;

unordered_set<string> pageParser(ifstream &ifile, string filepath) {
  unordered_set<string> links;
  char c;
  string workingString;
  ifile >> noskipws;
  while (ifile >> c) {
    //we need to convert everything to lower as queries are case insensitive
    c = tolower(c);
    if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
      workingString = workingString + c;
    }

    //if we find a [ keep parsing words as normal, but when we get to a ] stop
    //parsing, skip the ( and put everything into linkPath until we get to )
    else if (c == '[') {
      workingString = "";
      while (ifile >> c) {
        if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
          workingString = workingString + c;
        } else if (c == ']') {
          workingString = "";
          string linkPath;
          ifile >> c; //we do this to ignore the '('
          while (ifile >> c) {
            if (c == ')') {
              break;
            } else {
              linkPath = linkPath + c;
            }
          }
          links.insert(linkPath);
          cout << "adding link " << linkPath << endl;
          break;
        } else if (workingString != "") {
          workingString = "";
        }
      }
    }

    else if (workingString != "") {
      workingString = "";
    }
  }

  //we do this because entries in links are inserted similar to a stack, so
  //they are in reverse order. this ensures the order is correct before return
  unordered_set<string> linksToReturn;
  unordered_set<string>::iterator it = links.begin();
  while (it != links.end()) {
    linksToReturn.insert(*it);
    it++;
  }

  return linksToReturn;
}

void crawlerHelper(string inputPath, set<string> &setOfPages, ofstream &output){
  ifstream ifile;
  ifile.open(inputPath.c_str());

  //if ifile fails, this means this link is invalid and we shouldn't add it
  if (ifile.fail()) {
    cout << "404, didnt find " << inputPath << endl;
    ifile.close();
    return;
  }

  //if inputPath represents a webpage we haven't seen already, add it to the
  //list of pages we've seen and output it
  if (setOfPages.find(inputPath) == setOfPages.end()) {
    setOfPages.insert(inputPath);
    cout << "were adding " << inputPath << endl;
    output << inputPath << endl;
  }

  unordered_set<string> links = pageParser(ifile,inputPath);
  //loop through all links that this page contains and recursivley call helper
  unordered_set<string>::iterator it = links.begin();
  while (it != links.end()) {
    //this if statement ensures we only explore pages we haven't seen already
    if (setOfPages.find((*it)) == setOfPages.end()) {
      cout << "now calling func for " << *it << endl;
      crawlerHelper((*it), setOfPages, output);
    }
    it++;
  }
  ifile.close();
  return;
}

int main(int argc, char const *argv[]) {
  string pathToConfig = "config.txt";
  if (argc >= 1) {
    pathToConfig = argv[1];
  }

  ifstream config;
  config.open(pathToConfig.c_str());

  string INDEX_FILE;
  string OUTPUT_FILE;

  char charin;
  string tempInput;
  string tempValue;
  string tempLineOfFile;
  bool readingValue = false;

  while (getline(config,tempLineOfFile)) {
    stringstream ss;
    ss.str(tempLineOfFile);
    while (ss >> charin) {
      if (charin == '#') {
        break;
      }
      else if (charin == '=') {
        readingValue = true;
      }
      else if (readingValue == false) {
        if (charin != ' ') {
          tempInput = tempInput + charin;
        }
      }
      else if (readingValue == true) {
        if (charin != ' ') {
          tempValue = tempValue + charin;
        }
      }
    }

    if (tempInput == "INDEX_FILE") {
      INDEX_FILE = tempValue;
    } else if (tempInput == "OUTPUT_FILE") {
      OUTPUT_FILE = tempValue;
    }
    tempInput = "";
    tempValue = "";
    readingValue = false;
  }

  //open index and initialize set and output that we will need for crawlerHelper
  ifstream index;
  index.open(INDEX_FILE.c_str());
  string input = "";

  set<string> setOfPages;
  ofstream output;
  output.open(OUTPUT_FILE.c_str());

  //for each file listed in index, call crawlerHelper
  cout << "INDEX_FILE is " << INDEX_FILE << endl;
  while (getline(index,input)) {
    cout << "input is " << input << endl;
    if (input != "") {
      crawlerHelper(input, setOfPages, output);
    }
  }

  index.close();
  output.close();

  return 0;
}
