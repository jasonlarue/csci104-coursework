#include <set>

using std::set;

template <class T>
set<T> templatedUnion(set<T> &set1, set<T> &set2) {
  set<T> unionSet;

  set<T>::iterator it = set1.begin();
  while (it != set1.end()) {
    unionSet.insert(*it);
    it++;
  }
  set<T>::iterator it2 = set2.begin();
  while (it != set2.end()) {
    unionSet.insert(*it);
    it2++;
  }
  return unionSet;
}

template <class T>
set<T> templatedIntersect(set<T> &set1, set<T> &set2) {
  set<T> intersectionSet;

  set<T>::iterator it = set1.begin();
  while (it != set1.end()) {
    if (set2.find(*it) != set2.end()) {
      intersectionSet.insert(*it);
    }
    it++;
  }
  return intersectionSet;
}
