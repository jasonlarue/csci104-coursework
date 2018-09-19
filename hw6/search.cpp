#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include "WebPage.h"

using namespace std;

bool WebPageCompByPageRank (WebPage* lhs, WebPage* rhs) {
  if ((lhs -> getPageRank()) < (rhs -> getPageRank())) {
    return true;
  }
  return false;
}


string stringToLowercase(string toBeLowercase) {
  string converted;
  for (size_t i = 0; i < toBeLowercase.size(); i++) {
    char c = tolower(toBeLowercase[i]);
    converted = converted + c;
  }
  return converted;
}

vector<WebPage*> orderPagesByPageRank (set<WebPage*> candidateSet) {
  vector<WebPage*> sortedPages;

  set<WebPage*>::iterator it = candidateSet.begin();
  while (it != candidateSet.end()) {
    sortedPages.push_back(*it);
    it++;
  }

  sort(sortedPages.begin(),sortedPages.end(),WebPageCompByPageRank);
  reverse(sortedPages.begin(),sortedPages.end());

  return sortedPages;
}

void pageRank(set<WebPage*> candidateSet, double RESTART_PROBABILITY,
  double STEP_NUMBER) {
    //begin by initializing all pageRanks to be 1/n
    set<WebPage*>::iterator initializerIt = candidateSet.begin();
    while (initializerIt != candidateSet.end()) {
      (*initializerIt) -> setPageRank(1.0/candidateSet.size());
      initializerIt++;
    }

    //for number of steps (t)
    for (int i = 0; i < STEP_NUMBER; i++) {

      //assign previousPageRank to the current pageRank, before we begin a new
      //iteration
      set<WebPage*>::iterator pprIt = candidateSet.begin();
      while (pprIt != candidateSet.end()) {
        double tempPageRank = (*pprIt) -> getPageRank();
        (*pprIt) -> setPreviousPageRank(tempPageRank);
        pprIt++;
      }

      //for all pages in candidate set
      set<WebPage*>::iterator it = candidateSet.begin();
      while (it != candidateSet.end()) {

        double pageRankForPage = 0;
        set<WebPage*> incomingLinksForPage = (*it) -> getIncomingLinks();
        //we add this so we have a self loop
        incomingLinksForPage.insert(*it);
        //iterate over all other pages that link to this page

        set<WebPage*>::iterator it2 = incomingLinksForPage.begin();
        while (it2 != incomingLinksForPage.end()) {

          set<WebPage*> outgoingLinksIt2 = (*it2)-> getOutgoingLinks();
          set<WebPage*> cardinalOutgoingLinksIt2;

          set<WebPage*>::iterator outLinkIt = outgoingLinksIt2.begin();
          while (outLinkIt != outgoingLinksIt2.end()) {
            if (candidateSet.find(*outLinkIt) != candidateSet.end()) {
              cardinalOutgoingLinksIt2.insert(*outLinkIt);
            }
            outLinkIt++;
          }

          cardinalOutgoingLinksIt2.insert(*it2);

          pageRankForPage = pageRankForPage +
                                (1.0/(cardinalOutgoingLinksIt2.size()) *
          ((*it2)->getPreviousPageRank()));
          it2++;
        }
        pageRankForPage = pageRankForPage * (1.0-RESTART_PROBABILITY);
        pageRankForPage = pageRankForPage + RESTART_PROBABILITY *
        (1.0/candidateSet.size());
        (*it) -> setPageRank(pageRankForPage);
        it++;
      }
    }
  }

  int main(int argc, char const *argv[]) {
    string pathToConfig = "config.txt";
    if (argc >= 1) {
      pathToConfig = argv[1];
    }

    ifstream config;
    config.open(pathToConfig.c_str());

    string INDEX_FILE;
    string QUERY_FILE;
    string OUTPUT_FILE;
    double RESTART_PROBABILITY;
    double STEP_NUMBER;

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
      } else if (tempInput == "QUERY_FILE") {
        QUERY_FILE = tempValue;
      } else if (tempInput == "OUTPUT_FILE") {
        OUTPUT_FILE = tempValue;
      } else if (tempInput == "RESTART_PROBABILITY") {
        RESTART_PROBABILITY = atof(tempValue.c_str());
      } else if (tempInput == "STEP_NUMBER") {
        STEP_NUMBER = atof(tempValue.c_str());
      }
      tempInput = "";
      tempValue = "";
      readingValue = false;
    }

    //start by opening the index
    ifstream ifile;
    ifile.open(INDEX_FILE.c_str());
    if (ifile.fail()) {
      //index.txt error
      return 1;
    }
    //now iterate through files in the index, create new WebPages and add to set
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
    output.open(OUTPUT_FILE.c_str());

    //open up query, loop through commands
    ifstream kfile;
    kfile.open(QUERY_FILE.c_str());
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
        set<WebPage*> namesOfPageResults;
        set<WebPage*>::iterator it = webpages.begin();
        while (it != webpages.end()) {
          if ((*it) -> isWordInWebPage(firstCommandInLine) == true) {
            namesOfPageResults.insert(*it);

            //get the incoming and outgoing links for this webpage and add
            //them to results
            set<WebPage*> thisPageOutgoingLinks=(*it)-> getOutgoingLinks();
            namesOfPageResults.insert(thisPageOutgoingLinks.begin(),
            thisPageOutgoingLinks.end());
            set<WebPage*> thisPageIncomingLinks=(*it)-> getIncomingLinks();
            namesOfPageResults.insert(thisPageIncomingLinks.begin(),
            thisPageIncomingLinks.end());
          }
          it++;
        }

        //print the number of results, followed by the names of each result
        output << namesOfPageResults.size() << endl;

        pageRank(namesOfPageResults, RESTART_PROBABILITY, STEP_NUMBER);
        vector<WebPage*> orderedResults=orderPagesByPageRank
                                                          (namesOfPageResults);
        for (size_t i = 0; i < orderedResults.size(); i++) {
          output << orderedResults[i] -> getFilepath() << endl;

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

              //get the incoming and outgoing links for this webpage and add
              //them to results
              set<WebPage*> thisPageOutgoingLinks=(*it)-> getOutgoingLinks();
              pagesWithIntersections.insert(thisPageOutgoingLinks.begin(),
              thisPageOutgoingLinks.end());
              set<WebPage*> thisPageIncomingLinks=(*it)-> getIncomingLinks();
              pagesWithIntersections.insert(thisPageIncomingLinks.begin(),
              thisPageIncomingLinks.end());
            }
            it++;
          }

          if (howManyIntersections != 0) {
            output << pagesWithIntersections.size() << endl;

            pageRank(pagesWithIntersections, RESTART_PROBABILITY, STEP_NUMBER);
            vector<WebPage*> orderedResults =
            orderPagesByPageRank(pagesWithIntersections);

            for (size_t i = 0; i < orderedResults.size(); i++) {
              output << orderedResults[i] -> getFilepath() << endl;


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

            //get the incoming and outgoing links for this webpage and add
            //them to results
            set<WebPage*> thisPageOutgoingLinks=(*it)-> getOutgoingLinks();
            pagesWithUnion.insert(thisPageOutgoingLinks.begin(),
            thisPageOutgoingLinks.end());
            set<WebPage*> thisPageIncomingLinks=(*it)-> getIncomingLinks();
            pagesWithUnion.insert(thisPageIncomingLinks.begin(),
            thisPageIncomingLinks.end());
          }
          it++;
        }

        if (howManyUnions != 0) {
          output << pagesWithUnion.size() << endl;

          pageRank(pagesWithUnion, RESTART_PROBABILITY, STEP_NUMBER);
          vector<WebPage*> orderedResults =orderPagesByPageRank(pagesWithUnion);
          for (size_t i = 0; i < orderedResults.size(); i++) {
            output << orderedResults[i] -> getFilepath() << endl;
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
          if (stringToLowercase((*it) -> getFilepath()) ==(*commands.begin())) {
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
          if (stringToLowercase((*it) -> getFilepath()) ==(*commands.begin())) {
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
          if (stringToLowercase((*it) -> getFilepath()) ==(*commands.begin())) {
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
