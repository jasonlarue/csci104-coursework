#ifndef WEBPAGE_H
#define WEBPAGE_H
#include <set>
#include <string>
#include <fstream>

class WebPage {
  public:
    //the constructor takes ifstream as an argument so it knows where to parse
    //from, and a filepath as a string so it can assign that value to _filepath
    WebPage(std::ifstream &ifile, std::string filepath);
    ~WebPage();
    //this function is called right after all webpages are initialized, to help
    //establish links between WebPages
    void addOutgoingLinks(std::set <WebPage*> webpages);
    //this function also helps establish links between pages
    void addIncomingLink(WebPage* toBeLinked);
    //this is a getter for _filepath
    std::string getFilepath();
    //
    bool isWordInWebPage(std::string word);
    //this converts _incomingLinks to a set of strings that contain the
    //filenames of each of the webpages in _incomingLinks and returns the set
    std::set<std::string> getIncomingLinksAsStrings();
    //this is a getter for _linksAsStrings
    std::set<std::string> getOutgoingLinksAsStrings();
    //this function is used when the query contains a PRINT command, it takes
    //an ifstream to reparse the webpage and an ofstream to output the webpage
    void printPage(std::ifstream &ifile, std::ofstream &output);
    //these functions take in a set of strings as an argument, then return
    //true if the set has a union/intersection with _parsedWords, respectively.
    bool stringUnionWithPage(std::set <std::string> passedSet);
    bool stringIntersectionWithPage(std::set <std::string> passedSet);
    //getters for _incomingLinks and _outgoingLinks
    std::set <WebPage*> getIncomingLinks();
    std::set <WebPage*> getOutgoingLinks();

    //setter and getter for pageRank
    void setPageRank(double pageRank);
    double getPageRank();

    //setter and getter for previousPageRank
    void setPreviousPageRank(double pageRank);
    double getPreviousPageRank();

    double getOutDegree();


  private:
    std::string _filepath;
    std::set <std::string> _parsedWords;
    std::set <std::string> _linksAsStrings;
    std::set <WebPage*> _incomingLinks;
    std::set <WebPage*> _outgoingLinks;
    double _pageRank;
    double _previousPageRank;
};

#endif
