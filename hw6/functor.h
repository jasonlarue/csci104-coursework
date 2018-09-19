#include <WebPage.h>

struct WebPageCompByPageRank {
  bool operator() (const WebPage*& lhs, const WebPage*& rhs);
};
