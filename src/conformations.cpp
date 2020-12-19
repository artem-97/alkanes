#include <set>
#include <string>

#include "conformations.h"

namespace Alkanes {
All_conformations::All_conformations(int N) : N_(N - 1) {
  std::string tmp("A", N_);
  gen_conformations(tmp, 0);
}

void All_conformations::gen_conformations(std::string &s, int idx) {
  if (idx == s.size()) {
    if (s.front() == 'G' or s.back() == 'G')
      return;
    // check new conformation and reversed in set
    if (!conformations_.contains(s) and
        !conformations_.contains(std::string(s.rbegin(), s.rend())))
      conformations_.insert(s);
    return;
  }

  s[idx] = 'A';
  gen_conformations(s, idx + 1);

  s[idx] = 'G';
  gen_conformations(s, idx + 1);

  s[idx] = 'E';
  gen_conformations(s, idx + 1);
}

Alkane_generator All_conformations::conformations() const {
  for (const auto &conf : conformations_) {
    co_yield conf;
  }
}
} // namespace Alkanes
