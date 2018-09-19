#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

class node {
public:
  int g;
  int h;
  int f;
  node* predecessor;
  string bitString;
};

struct comparator {
  bool operator()(node* const &a, node* const &b) {
    if ((a -> f == b -> f) && (a -> h == b -> h)) {

      string aString = a -> bitString;
      string bString = b -> bitString;
      for (size_t i = 0; i < aString.size(); i++) {
        if (aString[i] != bString[i]) {
          if (aString[i] == '1') {
            return true;
          } else {
            return false;
          }
        }
      }
    }
    if (a -> f == b -> f) {
      return a -> h > b -> h;
    } else {
      return a -> f > b -> f;
    }
  }
};

bool isNodeAllOnes(node* nodeToCheck) {
  string bitString = nodeToCheck -> bitString;
  for (size_t i = 0; i < bitString.length(); i++) {
    if (bitString[i] != '1') {
      return false;
    }
  }
  return true;
}

int findHForNode(node* nodeToCheck) {
  string bitString = nodeToCheck -> bitString;
  int numOfZeros = 0;
  for (size_t i = 0; i < bitString.length(); i++) {
    if (bitString[i] == '0') {
      numOfZeros++;
    }
  }
  return numOfZeros;
}

int main(int argc, char const *argv[]) {
  if (argc < 3) {
    return 1;
  }

  string startNodeString = argv[1];

  ifstream ifile;
  ifile.open(argv[2]);

  string numOfNodesAsString;
  getline(ifile, numOfNodesAsString);
  int numOfNodes = stoi(numOfNodesAsString);

  vector<string> validNodes;

  string tempValidNodeString;
  for (int i = 0; i < numOfNodes; i++) {
    getline(ifile,tempValidNodeString);
    validNodes.push_back(tempValidNodeString);
  }

  int expansions = 0;
  set<string> visitedList;
  priority_queue<node*, vector<node*>, comparator> pq;

  //everytime we dynamically allocate a node we add it to this vector to make
  //freeing memory at the end easier
  vector<node*> everyDynamicallyAllocatedNode;

  node* startingNode = new node();
  everyDynamicallyAllocatedNode.push_back(startingNode);
  startingNode -> bitString = startNodeString;
  startingNode -> predecessor = NULL;
  startingNode -> g = 0;
  startingNode -> h = findHForNode(startingNode);
  startingNode -> f = startingNode -> g + startingNode -> h;

  pq.push(startingNode);


  node* endNode = NULL;
  //while priority_queue is not empty
  while (!pq.empty()) {
    //start by getting the top from pq
    node* top = pq.top();
    pq.pop();

    //if top is equal to all ones, we're done
    if (isNodeAllOnes(top)) {
      endNode = top;
      break;
    }

    //if we havent seen this node before, add it to the set and iterate
    //expansions (otherwise we do nothing)
    if (visitedList.count(top->bitString)==0) {
      visitedList.insert(top->bitString);
      expansions++;


      //now we add valid neighbors
      for (size_t i = 0; i < top -> bitString.size(); i++) {
        //for the ith char in bitString, flip the bit and check if its
        //in validNodes
        string bitStringCopy = top -> bitString;

        if (bitStringCopy[i] == '1') {
          bitStringCopy[i] = '0';
        } else if (bitStringCopy[i] == '0') {
          bitStringCopy[i] = '1';
        }

        //iterate through all valid nodes, if the bitString we modified is equal
        //to one of them we will create a new neighbor and add it to pq
        for (size_t i = 0; i < validNodes.size(); i++) {
        //  cout << validNodes[i] << " and "  <<  bitStringCopy << endl;
          if (validNodes[i] == bitStringCopy) {
            node* newNeighbor = new node();
            everyDynamicallyAllocatedNode.push_back(newNeighbor);
            newNeighbor -> bitString = validNodes[i];
            newNeighbor -> predecessor = top;
            newNeighbor -> g = top->g+1;
            newNeighbor -> h = findHForNode(newNeighbor);
            newNeighbor -> f = newNeighbor -> g + newNeighbor -> h;

            pq.push(newNeighbor);
          }
        }
      }
    }
  }

  if (endNode != NULL) {
    vector<node*> finishedPath;
    while (endNode -> predecessor != NULL) {
      finishedPath.push_back(endNode);
      endNode = endNode -> predecessor;
    }
    //this last one pushes the start node to the vector
    finishedPath.push_back(endNode);

    //iterate through vector in reverse order and print
    for (size_t i = finishedPath.size(); i-- > 0; ) {
      cout << finishedPath[i]->bitString << endl;
    }

    cout << "expansions = " << expansions << endl;
  } else {
    cout << "No transformation" << endl;
    cout << "expansions = " << expansions << endl;
  }

  //finally to clear all memory we loop through everyDynamicallyAllocatedNode
  //and delete contents
  for (size_t i = 0; i < everyDynamicallyAllocatedNode.size(); i++) {
    delete everyDynamicallyAllocatedNode[i];
  }
  return 0;
}
