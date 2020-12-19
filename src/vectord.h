#pragma once

#include <array>
#include <iostream>

namespace Alkanes {
class Vectord {
public:
  using arrayd = std::array<double, 3>;
  Vectord() = default;
  Vectord(const arrayd &);
  Vectord(arrayd &&);

  Vectord(const Vectord &);
  Vectord(Vectord &&);

  Vectord &operator=(const Vectord &);
  Vectord &operator=(Vectord &&) noexcept;

  double &operator[](std::size_t);
  const double &operator[](std::size_t) const;

  Vectord &operator*=(double);
  Vectord operator*(double)const;
  friend Vectord operator*(double, const Vectord &);

  Vectord &operator/=(double);
  Vectord operator/(double) const;

  Vectord &operator+=(const Vectord &);
  friend Vectord operator+(Vectord, const Vectord &);

  Vectord &operator-=(const Vectord &);
  friend Vectord operator-(Vectord, const Vectord &);

  friend double operator*(const Vectord &, const Vectord &);  // dot product
  friend Vectord operator^(const Vectord &, const Vectord &); // cross product

  friend bool operator==(const Vectord &, const Vectord &);
  friend bool operator!=(const Vectord &, const Vectord &);

  virtual ~Vectord() = default;

  double norm() const;
  Vectord &normalize();

  Vectord &rotate(Vectord, double);

  friend std::ostream &operator<<(std::ostream &, const Vectord &);

private:
  arrayd xyz_;
};
} // namespace Alkanes
