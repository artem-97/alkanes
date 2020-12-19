#pragma once

#include <set>
#include <string>

#include "alkane.h"
#include "generator.h"

namespace Alkanes {
class All_conformations {
public:
  All_conformations(int); // ctor from N -- number of carbon atoms
  Alkane_generator
  conformations() const; // coroutine for generation conformations

private:
  int N_;
  std::set<std::string> conformations_;
  void gen_conformations(std::string &, int);
};
} // namespace Alkanes
