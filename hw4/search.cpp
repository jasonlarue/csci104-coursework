#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "WebPage.h"

using namespace std;

string stringToLowercase(string toBeLowercase) {
  string converted;
  for (size_t i = 0; i < toBeLowercase.size(); i++) {
    char c = tolower(toBeLowercase[i]);
    converted = converted + c;
  }
  return converted;
}

int main(int argc, char const *argv[]) {
  if (argc < 4) {
    //cmd line args error
    return 1;
  }
  //start by opening the index
  ifstream ifile;
  ifile.open(argv[1]);
  if (ifile.fail()) {
    //index.txt error
    return 1;
  }
  //now iterate through files in the index, create new WebPages and add to a set
  set <WebPage*> webpages;
  string input;
  while (getline(ifile,input)) {
    if (input == "") {
      break;
    }
    ifstream jfile;
    jfile.open(input.c_str());
    if (jfile.fail()) {
      //webpage open error
      return 1;
    }
    WebPage* thispage = new WebPage(jfile,input);
    webpages.insert(thispage);
    input = "";
  }
  //now go back through all webpages and establish incoming and outgoing links
  set<WebPage*>::iterator it = webpages.begin();
  while (it != webpages.end()) {
    (*it) -> addOutgoingLinks(webpages);
    it++;
  }
  //prepare the output, we're going to need this is a minute
  ofstream output;
  output.open(argv[3]);

  //open up query, loop through commands
  ifstream kfile;
  kfile.open(argv[2]);
  input = "";
  string firstCommandInLine;
  set<string> commands;

  while (getline(kfile,input)) {
    stringstream commandstream;
    if (input == "") {
      break;
    }
    //put the line into a stringstream, put the first word into a string and
    //put the rest into a set
    commandstream << input;
    commandstream >> firstCommandInLine;
    string tempString;
    while (commandstream >> tempString) {
      tempString = stringToLowercase(tempString);
      commands.insert(tempString);
    }

    //if the set is empty, that means firstCommandInLine was the only part
    //of the command, so perform a search for webpages that contain the term
    if (commands.size() == 0) {
      firstCommandInLine = stringToLowercase(firstCommandInLine);
      vector<string> namesOfPageResults;
      int numOfResults = 0;
      set<WebPage*>::iterator it = webpages.begin();
      while (it != webpages.end()) {
        if ((*it) -> isWordInWebPage(firstCommandInLine) == true) {
          namesOfPageResults.push_back((*it) -> getFilepath());
          numOfResults++;
        }
        it++;
      }
      //print the number of results, followed by the names of each result
      output << numOfResults << endl;
      for (size_t i = 0; i < namesOfPageResults.size(); i++) {
        output << namesOfPageResults[i] << endl;
      }
    }
    else if (firstCommandInLine == "AND") {
      if (commands.size() < 2) {
        output << "0" << endl;
      } else {
        int howManyIntersections = 0;
        set<WebPage*> pagesWithIntersections;
        set<WebPage*>::iterator it = webpages.begin();
        while (it != webpages.end()) {
          if ((*it) -> stringIntersectionWithPage(commands) == true) {
            howManyIntersections++;
            pagesWithIntersections.insert(*it);
          }
          it++;
        }

        if (howManyIntersections != 0) {
          output << howManyIntersections << endl;
          set<WebPage*>::iterator it2 = pagesWithIntersections.begin();
          while (it2 != pagesWithIntersections.end()) {
            output << (*it2) -> getFilepath() << endl;
            it2++;
          }
        } else {
          output << "0" << endl;
        }
      }
    }
    else if (firstCommandInLine == "OR") {
      int howManyUnions = 0;
      set<WebPage*> pagesWithUnion;
      set<WebPage*>::iterator it = webpages.begin();
      while (it != webpages.end()) {
        if ((*it) -> stringUnionWithPage(commands) == true) {
          howManyUnions++;
          pagesWithUnion.insert(*it);
        }
        it++;
      }

      if (howManyUnions != 0) {
        output << howManyUnions << endl;
        set<WebPage*>::iterator it2 = pagesWithUnion.begin();
        while (it2 != pagesWithUnion.end()) {
          output << (*it2) -> getFilepath() << endl;
          it2++;
        }
      } else {
        output << "0" << endl;
      }
    }
    else if (firstCommandInLine == "PRINT") {
      bool foundPage = false;
      //first, find the pointer to webpage the user entered
      set<WebPage*>::iterator it = webpages.begin();
      while (it != webpages.end()) {
        if (stringToLowercase((*it) -> getFilepath()) == (*commands.begin())) {
          foundPage = true;
          break;
        }
        it++;
      }

      if (foundPage) {
        output << (*it) -> getFilepath() << endl;
        ifstream ifile;
        ifile.open((*commands.begin()).c_str());
        (*it) -> printPage(ifile,output);
      } else output << "Invalid query" << endl;
    }
    else if (firstCommandInLine == "INCOMING") {
      bool foundPage = false;
      //first, find the pointer to webpage the user entered
      set<WebPage*>::iterator it = webpages.begin();
      while (it != webpages.end()) {
        if (stringToLowercase((*it) -> getFilepath()) == (*commands.begin())) {
          foundPage = true;
          break;
        }
        it++;
      }

      if (foundPage) {
        //then, put incoming links for designated webpage into set and print
        set<string> toPrint = (*it) -> getIncomingLinksAsStrings();
        output << toPrint.size() << endl;
        set<string>::iterator it2 = toPrint.begin();
        while (it2 != toPrint.end()) {
          output << *it2 << endl;
          it2++;
        }
      } else output << "Invalid query" << endl;
    }
    else if (firstCommandInLine == "OUTGOING") {
      bool foundPage = false;
      //first, find the pointer to webpage the user entered
      set<WebPage*>::iterator it = webpages.begin();
      while (it != webpages.end()) {
        if (stringToLowercase((*it) -> getFilepath()) == (*commands.begin())) {
          foundPage = true;
          break;
        }
        it++;
      }
      if (foundPage) {
        //then, put incoming links for designated webpage into set and print
        set<string> toPrint = (*it) -> getOutgoingLinksAsStrings();
        output << toPrint.size() << endl;
        set<string>::iterator it2 = toPrint.begin();
        while (it2 != toPrint.end()) {
          output << *it2 << endl;
          it2++;
        }
      } else output << "Invalid query" << endl;
    }
    else {
      output << "Invalid query" << endl;
    }

    firstCommandInLine = "";
    commands.clear();
  }

  //free memory
  set<WebPage*>::iterator it3 = webpages.begin();
  while (it3 != webpages.end()) {
    delete (*it3);
    it3++;
  }

  return 0;
}
