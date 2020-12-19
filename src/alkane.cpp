#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

#include "alkane.h"
#include "vectord.h"

namespace Alkanes {

Alkane::Alkane(const std::string &conformation) : conformation_(conformation) {
  if (conformation_.empty()) { // CH4
    get_first_cube();
    atoms_.back().type = 'H';
    atoms_.back().r /= l_cc;
    atoms_.back().r *= l_ch;
  } else { // default case
    auto prev = get_first_cube();
    for (auto it = conformation_.cbegin(); it != conformation_.cend(); ++it) {
      prev = get_next_cube(prev, it);
    }
  }
}

Vectord Alkane::get_first_cube() noexcept {
  Vectord r0({0, 0, 0});

  Vectord h1({-1, -1, -1});
  h1 *= l_ch;

  Vectord h2({1, -1, 1});
  h2 *= l_ch;

  Vectord h3({1, 1, -1});
  h3 *= l_ch;

  Vectord c1({-1, 1, 1});
  c1 *= l_cc;

  atoms_.push_back(Atom{'C', r0});
  atoms_.push_back(Atom{'H', h1});
  atoms_.push_back(Atom{'H', h2});
  atoms_.push_back(Atom{'H', h3});
  atoms_.push_back(Atom{'C', c1});

  return c1;
}

Vectord Alkane::get_next_cube(const Vectord &prev,
                              std::string::const_iterator connection_type) {
  auto &theta = angle; // 60 degree
  auto &r0 = prev;     // center of the current cell (cube)
  Vectord h1, h2;      // two hydrogen atoms
  Vectord x1;          // h3 if internal cube or c1 if terminal
  Vectord k;           // direction of rotation

  // switch for x1: h3 or c1
  const char x1_c = (connection_type == conformation_.end() - 1) ? 'H' : 'C';
  const double l_cx = (x1_c == 'H') ? l_ch : l_cc;

  auto N = std::distance(conformation_.begin(), connection_type) +
           1; // carbon atoms done

  if (N % 2) {
    k = -1 * a_ + 1 * b_ + 1 * c_; // -1, 1, 1

    h1 = -1 * a_ - 1 * b_ + 1 * c_; // -1, -1, 1
    h2 = 1 * a_ + 1 * b_ + 1 * c_;  // 1, 1, 1
    x1 = -1 * a_ + 1 * b_ - 1 * c_; // -1, 1, -1

  } else {
    k = 1 * a_ - 1 * b_ + 1 * c_; // 1, -1, 1

    h1 = -1 * a_ - 1 * b_ - 1 * c_; // -1, -1, -1
    h2 = 1 * a_ + 1 * b_ - 1 * c_;  // 1, 1, -1
    x1 = -1 * a_ + 1 * b_ + 1 * c_; // -1, 1, 1
  }

  // rotate conformation
  int rotate_times;
  if (*connection_type == 'A') {
    rotate_times = 0;
  } else if (*connection_type == 'E') {
    rotate_times = 1;
  } else if (*connection_type == 'G') {
    rotate_times = 2;
  }

  while (rotate_times) {
    h1.rotate(k, theta);
    h2.rotate(k, theta);
    x1.rotate(k, theta);

    a_.rotate(k, theta);
    b_.rotate(k, theta);
    c_.rotate(k, theta);
    --rotate_times;
  }

  // scale and shift our cube
  h1 *= l_ch;
  h1 += r0;

  h2 *= l_ch;
  h2 += r0;

  x1 *= l_cx;
  x1 += r0;

  auto atom_h1 = Atom({'H', h1});
  auto atom_h2 = Atom({'H', h2});
  auto atom_x1 = Atom({x1_c, x1});

  auto ok = check_intersection(atom_h1, atoms_.size() - 3) &&
            check_intersection(atom_h2, atoms_.size() - 3) &&
            check_intersection(atom_x1, atoms_.size() - 3);
  if (!ok) {
    throw BadConformation{};
  }

  atoms_.push_back(atom_h1);
  atoms_.push_back(atom_h2);
  atoms_.push_back(atom_x1);

  return x1;
}

bool Alkane::check_intersection(const Atom &current, int last) noexcept {
  bool ok = true;
  const double l_hh = 1.21;
  const double l_cc = 0.87;
  double min_dist;
  for (int i = 0; i < last; i++) {
    if (atoms_[i].type == 'C' && current.type == 'C')
      min_dist = l_cc;
    if (atoms_[i].type == 'C' && current.type == 'H')
      min_dist = l_ch * std::sqrt(3);
    if (atoms_[i].type == 'H' && current.type == 'C')
      min_dist = l_ch * std::sqrt(3);
    if (atoms_[i].type == 'H' && current.type == 'H')
      min_dist = l_hh;

    if ((atoms_[i].r - current.r).norm() < min_dist) {
      ok = false;
    }
  }
  return ok;
}

std::ostream &operator<<(std::ostream &os, const Alkane &alkane) noexcept {
  for (const auto &a : alkane.atoms_) {
    os << a.type << '\t' << a.r << '\n';
  }
  return os;
}

const char *BadConformation::what() const throw() {
  return "Radius intersection";
};
} // namespace Alkanes
