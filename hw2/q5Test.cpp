#include <iostream>

using namespace std;

struct Node {
    int value;
    Node *next;
};

Node* funcB(Node* in) {
    if (!in) return nullptr;
    Node *p = funcB(in->next);
    if (p) {
        p->next = in;
    }
    return in;
}

Node* funcA(Node* in) {
    if (!in) return nullptr;
    Node *r = in;
    while (r->next) r = r->next;
    cout << in-> value << endl;
    Node *l = funcB(in);
    l->next = nullptr;
    return r;
}

int main(int argc, char const *argv[]) {
  Node* node1 = new Node();
  Node* node2 = new Node();
  Node* node3 = new Node();
  Node* node4 = new Node();
  Node* node5 = new Node();

  node1 -> value = 1;
  node2 -> value = 2;
  node3 -> value = 3;
  node4 -> value = 4;
  node5 -> value = 5;

  node1 -> next = node2;
  node2 -> next = node3;
  node3 -> next = node4;
  node4 -> next = node5;
  node5 -> next = NULL;

  Node* returnNode = funcA(node1);

  cout << returnNode -> value;
  returnNode = returnNode -> next;
  cout << returnNode -> value;
  returnNode = returnNode -> next;
  cout << returnNode -> value;
  returnNode = returnNode -> next;
  cout << returnNode -> value;
  returnNode = returnNode -> next;
  cout << returnNode -> value;
  returnNode = returnNode -> next;


  return 0;
}
