#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <string_view>
#include <unordered_set>
#include <memory>
#include <cassert>

struct S { // public by default
  int a = 0, b = 0;
  S() { std::cout << "S::S()\n"; }
  S(S const &s) { std::cout << "S::S(S const&)\n"; }
  ~S() { std::cout << "S::~S()\n"; }

private:
  int c = 2; // 0 .. 5
public:
  int getC() const { return c; }
  friend void f(S const &);
  friend S operator+(int, S const &b) { return b; }
};

class C {
public:
  int a;
}; // private by default

void f(S const &s) {
  std::cout << "f(S{" << s.a << ", " << s.b << "})\n";
  std::cout << "private " << s.c << "\n";
}

S g() { return S{}; }

// auto ft(S t) {
//   return t.a;
// }

// auto ft(C t) {
//   return t.a;
// }
// decay remove(const), remove(&)
template <typename C> auto isempty(C & t) { 
  std::cout << "isempty(C)\n";
  return t.size() == 0;
}
template <> auto isempty(std::string_view const& s) {
    std::cout << "isempty(std::string_view)\n";
    return s.length();
}

// auto isempty(std::string_view s) { 
//     std::cout << "free isempty(std::string_view)\n";
//     return s.length();
// }

template <typename T>
struct one {
  T t;
};

template <typename T> // partial specialization
struct one<one<T>> {
  T t;
  T v;
};

template <typename... Args> std::string strjoin(Args... args) {
  std::ostringstream ss;
  (ss << ... << args);
  return ss.str();
}

namespace std {
  template<> struct hash<::S> {
    auto operator()(S const & s) const noexcept {
      return hash<int>{}(s.getC())*100 + hash<int>{}(s.a) * 10 + hash<int>{}(s.b);
    }
  };
}

void us() {
  std::unordered_set<S> s;
}

int main() {
  {
    S const &s = g();
    s.getC();
  }
  for (int i = 0, j = 0; i < 5 && j < 5; ++i, ++j) {
  }
  f((S{}, S{}));
  std::vector v{S{}};
  isempty(v);
  std::string_view str{"123"};
  isempty(str);
  one<int> o1{1}; // struct { int t; }
  one<one<int>> o2{1,2}; // struct { int t; int v; }
  //isempty(std::string_view{"123"});
  std::ifstream ifstr(strjoin("example", 4, ".cpp"));
  std::cout << strjoin(1, 2, 3, 4, 5.5, "") << "\n";
  return 0;
}