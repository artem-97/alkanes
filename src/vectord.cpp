#include <algorithm>
#include <cmath>
#include <iomanip>
#include <numeric>

#include "vectord.h"

namespace Alkanes {
Vectord::Vectord(const arrayd &xyz) : xyz_(xyz) {
  // std::cout << "ctor" << std::endl;
}

Vectord::Vectord(arrayd &&xyz) : xyz_(xyz) {}

Vectord::Vectord(const Vectord &other) : xyz_(other.xyz_) {
  // std::cout << "copy ctor" << std::endl;
}

Vectord::Vectord(Vectord &&other) : xyz_(std::move(other.xyz_)) {
  // std::cout << "move ctor" << std::endl;
}

Vectord &Vectord::operator=(const Vectord &other) {
  if (&other == this)
    return *this;
  xyz_ = other.xyz_;

  // std::cout << "copy assign" << std::endl;

  return *this;
}

Vectord &Vectord::operator=(Vectord &&other) noexcept {
  xyz_ = std::move(other.xyz_);

  // std::cout << "move assign" << std::endl;

  return *this;
}

double &Vectord::operator[](std::size_t idx) { return xyz_[idx]; }

const double &Vectord::operator[](std::size_t idx) const { return xyz_[idx]; }

Vectord &Vectord::operator*=(const double d) {
  // std::transform(xyz_.begin(), xyz_.end(), xyz_.begin(),
  //     [&d](auto& e){ e/d; });
  for (auto &e : xyz_)
    e *= d;
  return *this;
}

Vectord Vectord::operator*(double d) const {
  auto res = *this;
  res *= d;
  return res;
}

Vectord operator*(double d, const Vectord &v) { return v * d; }

Vectord &Vectord::operator/=(double d) {
  // std::transform(xyz_.begin(), xyz_.end(), xyz_.begin(),
  //     [&d](auto& e){ e/d; });

  for (auto &e : xyz_)
    e /= d;
  return *this;
}

Vectord Vectord::operator/(double d) const {
  auto res = *this;
  res /= d;
  return res;
}

Vectord &Vectord::operator+=(const Vectord &rhs) {
  std::transform(xyz_.begin(), xyz_.end(), rhs.xyz_.begin(), xyz_.begin(),
                 std::plus<double>());
  return *this;
}

Vectord operator+(Vectord lhs, const Vectord &rhs) {
  lhs += rhs;
  return lhs;
}

Vectord &Vectord::operator-=(const Vectord &rhs) {
  std::transform(xyz_.begin(), xyz_.end(), rhs.xyz_.begin(), xyz_.begin(),
                 std::minus<double>());
  return *this;
}

Vectord operator-(Vectord lhs, const Vectord &rhs) {
  lhs -= rhs;
  return lhs;
}

double operator*(const Vectord &lhs, const Vectord &rhs) {
  auto &lxyz = lhs.xyz_;
  auto &rxyz = rhs.xyz_;
  return std::inner_product(lxyz.begin(), lxyz.end(), rxyz.begin(), 0.0);
}

Vectord operator^(const Vectord &a, const Vectord &b) {
  Vectord res;
  res[0] = a[1] * b[2] - a[2] * b[1];
  res[1] = a[2] * b[0] - a[0] * b[2];
  res[2] = a[0] * b[1] - a[1] * b[0];
  return res;
}

bool operator==(const Vectord &lhs, const Vectord &rhs) {
  return lhs.xyz_ == rhs.xyz_;
}

bool operator!=(const Vectord &lhs, const Vectord &rhs) {
  return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &os, const Vectord &v) {
  int width = 12;
  for (const auto &e : v.xyz_)
    os << std::setw(width) << e << std::setw(width);
  return os;
}

double Vectord::norm() const {
  const auto &v = *this;
  return std::sqrt(v * v);
}

Vectord &Vectord::normalize() {
  *this /= norm();
  return *this;
}

Vectord &Vectord::rotate(Vectord k, double theta) {
  k.normalize();

  auto fst = *this * std::cos(theta);
  auto snd = (k ^ (*this)) * std::sin(theta);
  auto thrd = k * (k * (*this)) * (1 - std::cos(theta));

  *this = fst + snd + thrd;
  return *this;
}
} // namespace Alkanes
