#pragma once

#include <coroutine>
#include <string>

namespace Alkanes {

class Alkane_generator {
public:
  using value_type = std::string;
  struct promise_type {
    using coro_handle = std::coroutine_handle<promise_type>;
    value_type value_;
    std::suspend_always initial_suspend() const;
    std::suspend_always final_suspend() const;
    void return_void() const;
    void unhandled_exception() const;
    coro_handle get_return_object();
    std::suspend_always yield_value(value_type value);
  };

  using coro_handle = std::coroutine_handle<promise_type>;

  Alkane_generator(coro_handle);

  value_type get() const;
  bool next();

  ~Alkane_generator();

private:
  coro_handle handle_;
};
} // namespace Alkanes
