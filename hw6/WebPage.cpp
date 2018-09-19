#include "WebPage.h"
#include <fstream>
#include <iostream>
#include <set>

using namespace std;

WebPage::WebPage(ifstream &ifile, string filepath) {
  _filepath = filepath;
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
          _parsedWords.insert(workingString);
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
          _linksAsStrings.insert(linkPath);
          break;
        } else if (workingString != "") {
          _parsedWords.insert(workingString);
          workingString = "";
        }
      }
    }

    else if (workingString != "") {
      _parsedWords.insert(workingString);
      workingString = "";
    }
  }
  if (workingString != "") {
    _parsedWords.insert(workingString);
  }
}

WebPage::~WebPage() {

}

void WebPage::addOutgoingLinks(set <WebPage*> webpages) {
  //iterate over every webpage in the set, if that webpage is in our set of
  //links then add that webpage to our outgoing links set and add this webpage
  //to that webpages' incoming link set
  string currentFilepath;
  set<WebPage*>::iterator it = webpages.begin();
  while (it != webpages.end()) {
    currentFilepath = (*it) -> getFilepath();
    if (_linksAsStrings.find(currentFilepath) != _linksAsStrings.end()) {
      _outgoingLinks.insert((*it));
      (*it) -> addIncomingLink(this);
    }
    it++;
  }
}

void WebPage::addIncomingLink(WebPage* toBeLinked) {
  _incomingLinks.insert(toBeLinked);
}

string WebPage::getFilepath() {
  return _filepath;
}

bool WebPage::isWordInWebPage(string word) {
  if (_parsedWords.find(word) != _parsedWords.end()) {
    return true;
  } else return false;
}

set<string> WebPage::getIncomingLinksAsStrings() {
  set<string> toReturn;
  set<WebPage*>::iterator it = _incomingLinks.begin();
  while (it != _incomingLinks.end()) {
    toReturn.insert((*it) -> getFilepath());
    it++;
  }
  return toReturn;
}

set<string> WebPage::getOutgoingLinksAsStrings() {
  return _linksAsStrings;
}

void WebPage::printPage(std::ifstream &ifile, std::ofstream &output) {
  char c;
  string workingString;
  ifile >> noskipws;
  while (ifile >> c) {
    if (c == '(') {
      while (ifile >> c) {
        if (c == ')') {
          break;
        }
      }
    } else {
      output << c;
    }
  }
}

bool WebPage::stringUnionWithPage(std::set <std::string> passedSet) {
  bool foundUnion = false;
  set<string>::iterator it = passedSet.begin();
  while (it != passedSet.end()) {
    if (_parsedWords.find(*it) != _parsedWords.end()) {
      foundUnion = true;
    }
    it++;
  }
  return foundUnion;
}


bool WebPage::stringIntersectionWithPage(std::set <std::string> passedSet) {
  bool foundIntersection = true;
  set<string>::iterator it = passedSet.begin();
  while (it != passedSet.end()) {
    if (_parsedWords.find(*it) == _parsedWords.end()) {
      foundIntersection = false;
    }
    it++;
  }
  return foundIntersection;
}

set<WebPage*> WebPage::getIncomingLinks() {
  return _incomingLinks;
}

set<WebPage*> WebPage::getOutgoingLinks() {
  return _outgoingLinks;
}

void WebPage::setPageRank(double pageRank) {
  _pageRank = pageRank;
}

double WebPage::getPageRank() {
  return _pageRank;
}

void WebPage::setPreviousPageRank(double previousPageRank) {
  _previousPageRank = previousPageRank;
}

double WebPage::getPreviousPageRank() {
  return _previousPageRank;
}

double WebPage::getOutDegree() {
  return _outgoingLinks.size();
}
