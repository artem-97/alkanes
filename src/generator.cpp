#include <coroutine>
#include <iostream>

#include "generator.h"

namespace Alkanes {
// Promise interface

std::suspend_always Alkane_generator::promise_type::initial_suspend() const {
  return std::suspend_always();
}

std::suspend_always Alkane_generator::promise_type::final_suspend() const {
  return std::suspend_always();
}

void Alkane_generator::promise_type::return_void() const {};

void Alkane_generator::promise_type::unhandled_exception() const {
  std::terminate;
}

Alkane_generator::promise_type::coro_handle
Alkane_generator::promise_type::get_return_object() {
  return coro_handle::from_promise(*this);
}

std::suspend_always Alkane_generator::promise_type::yield_value(
    Alkane_generator::value_type value) {
  value_ = value;
  return std::suspend_always();
}

// Generator interface
Alkane_generator::Alkane_generator(coro_handle handle) : handle_(handle){};

Alkane_generator::value_type Alkane_generator::get() const {
  return handle_.promise().value_;
}

bool Alkane_generator::next() {
  if (!handle_.done())
    handle_.resume();
  return !handle_.done();
}

Alkane_generator::~Alkane_generator() {
  if (handle_)
    handle_.destroy();
}
} // namespace Alkanes
