#include "functor.h"

using namespace std;

bool WebPageCompByPageRank::operator()
                            (const WebPage*& lhs, const WebPage*& rhs); {
  if (lhs -> getPageRank() < rhs -> getPageRank() {
    return true;
  }

  if (lhs -> getPageRank() > rhs -> getPageRank() {
    return false;
  }

  return false;
}
