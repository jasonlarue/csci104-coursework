#include <string>

struct NumStrComp {
  bool operator() (const std::string& lhs, const std::string& rhs);
};
