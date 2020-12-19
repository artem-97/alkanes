#pragma once

#include <cmath>
#include <exception>
#include <numbers>
#include <string>
#include <vector>

#include "vectord.h"

namespace Alkanes {
class Alkane {
public:
  Alkane(const std::string &);

  Alkane(const Alkane &) = delete;
  Alkane(Alkane &&) = delete;

  Alkane &operator=(const Alkane &) = delete;
  Alkane &operator=(Alkane &&) = delete;

  virtual ~Alkane() = default;

  friend std::ostream &operator<<(std::ostream &, const Alkane &) noexcept;

private:
  static constexpr double l_cc = 1.54 / std::sqrt(3); // in A,  1.54 -- Cc bond
  static constexpr double l_ch = 1.1 / std::sqrt(3);  // in A,  1.1 -- CH bond
  static constexpr double angle = std::numbers::pi / 3;

  const std::string conformation_; // "AGEAAEG..."

  Vectord get_first_cube() noexcept;
  Vectord get_next_cube(const Vectord &, const std::string::const_iterator);

  struct Atom {
    char type; // C or H
    Vectord r; // position
  };

  std::vector<Atom> atoms_;
  bool check_intersection(const Atom &, int) noexcept;

  Vectord a_ = Vectord({1, 0, 0});
  Vectord b_ = Vectord({0, 1, 0});
  Vectord c_ = Vectord({0, 0, 1});
};

struct BadConformation : public std::exception {
  const char *what() const throw();
};
} // namespace Alkanes
