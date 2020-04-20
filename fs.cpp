#include <iostream>
#include <system_error>
#include "expected.hpp"
#include <outcome.hpp>

class my_category_t : public std::error_category {
public:
  enum Errors { SUCCESS, ERROR1 };
  const char *name() const noexcept override { return "my cat"; }
  std::string message(int condition) const override {
    if (condition == int(Errors::ERROR1))
      return "Error #1";
    return "Unknown error";
  }
} my_category;

void f(int x, std::error_code &ec) {
  if (x < 0)
    ec = std::error_code(my_category_t::Errors::ERROR1, my_category);
}

void f(int x) {
  std::error_code ec;
  f(x, ec);
  if (ec)
    throw std::system_error(ec);
}

tl::expected<int, int> f2(int x) {
  if (x < 0)
    return tl::make_unexpected(my_category_t::ERROR1);
  return 2*x;
}

tl::expected<int, int> f3(int x) {
  if (x > 100)
    return tl::make_unexpected(my_category_t::ERROR1);
  return x*x;
}

tl::expected<int, int> g3(int x) {
  auto r = f2(x);
  if (!r)
    return r;
  if (*r > 100)
    return tl::make_unexpected(my_category_t::ERROR1);
  return *r * *r;
}

int main() {
  // f(-1);
  std::error_code ec;
  f(-1, ec);
  if (ec == std::error_code(my_category_t::ERROR1, my_category))
    std::cerr << "Error: " << ec.message() << "\n";
  if (auto r = f2(100).and_then(f3))
    std::cout << *r << "\n";
  else
    std::cerr << "Error #" << r.error() << "\n";
  return 0;
}