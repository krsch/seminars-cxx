#include "range/v3/algorithm/mismatch.hpp"
#include "range/v3/range/concepts.hpp"
#include "range/v3/view/subrange.hpp"
#include "range/v3/view/transform.hpp"
#include <cctype>
#include <iostream>
#include <locale>
#include <range/v3/all.hpp>
#include <set>
#include <string>
#include <vector>

template <typename FwdRange> void print_range(FwdRange rng) {
  for (auto const &i : rng) {
    std::cout << i << ", ";
  }
  std::cout << "\n";
}

int main() {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
  print_range(ranges::subrange{v.begin() + 3, v.end() - 3});
  print_range(v | ranges::views::slice(3, 6));
  std::set<int> s(begin(v), end(v));
  print_range(s);
  auto case_insensitive1 = [loc = std::locale{""}](std::string const &a,
                                                   std::string const &b) {
    auto lower_transform = ranges::views::transform(
        [&loc](char x) { return std::tolower(x, loc); });
    return ranges::lexicographical_compare(a | lower_transform,
                                           b | lower_transform);
  };
  auto case_insensitive1a = [loc = std::locale{""}](std::string const &a,
                                                    std::string const &b) {
    return ranges::lexicographical_compare(a, b, [&loc](char x, char y) {
      return std::tolower(x, loc) < std::tolower(y, loc);
    });
  };
  auto case_insensitive2 = [loc = std::locale{""}](std::string const &a,
                                                   std::string const &b) {
    for (size_t i = 0; i < std::min(a.size(), b.size()); ++i)
      if (std::tolower(a[i], loc) != std::tolower(b[i], loc))
        return std::tolower(a[i], loc) < std::tolower(b[i], loc);
    return a.size() < b.size();
  };
  auto case_insensitive = [loc = std::locale{""}](std::string const &a,
                                                  std::string const &b) {
    auto low = [&loc](char x) { return std::tolower(x, loc); };
    for (size_t i = 0; i < std::min(a.size(), b.size()); ++i)
      if (low(a[i]) != low(b[i]))
        return low(a[i]) < low(b[i]);

    return a.size() < b.size();
  };

  std::set<std::string, decltype(case_insensitive)> s2({"abc", "Abd", "aBd"},
                                                       case_insensitive);
  print_range(s2);
  return 0;
}

void up() {
  struct List {
    int val;
    // List next;
  }; // sizeof(List) = sizeof(int) + size(List)
  auto p = std::make_unique<int>(3);
  auto p2 = p.get();
  auto &r = *p;
  auto p3 = &*p;
  // std::unique_ptr<int> up{p3}; // ERROR
  auto up2 = std::move(p);
  assert(p == nullptr);
  auto i = int(3);
}