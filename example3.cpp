#include <cctype>
#include <exception>
#include <functional>
#include <iostream>
#include <locale>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <vector>
#include <variant>
#include <any>
int global_max = 0;
struct unique_int {
  int &a;
  unique_int() noexcept : a(++global_max) {
    // global_max += 1;
    // a = global_max;
  }
  explicit unique_int(int &a) : a(a) {}
  unique_int(unique_int const &s) = delete;
  unique_int &operator=(unique_int const &s) = delete;
  unique_int(unique_int &&s) noexcept : a(s.a) {
    s.a = -1;
    // throw std::domain_error("error");
  }
  unique_int &operator=(unique_int &&s) noexcept {
    a = s.a;
    s.a = -1;
    return *this;
  }
  operator int() { return a; }
};
void t(unique_int const &s) {}
void g() {
  int i;
  t(unique_int{i});
  auto a = unique_int{} * 5;
  // unique_int a = i;
}
namespace std {
void swap(unique_int &s1, unique_int &s2) noexcept {
  auto tmp = std::move(s1);
  s1 = std::move(s2);
  s2 = std::move(tmp);
}
} // namespace std

struct List {
  List *prev;
  std::unique_ptr<List> next;
  int value;
};
void remove_one(List &l) {
  if (l.next)
    l.next->prev = l.prev;
  if (l.prev)
    l.prev->next = std::move(l.next);
  auto & [prev, next, val] = l;
}
void insert(List & l, int val) {
  std::unique_ptr<List> next = std::move(l.next);
  l.next = std::make_unique<List>(List{&l, std::move(next), val});
}

std::tuple<int, float, double, int> tup() { return {1, 1.f, 1., 2}; }

void tup2() {
  std::tuple t2{1, 2, 3.};
  auto [i, f, d, i2] = tup();
  std::tuple t = tup();
  int i3{std::get<0>(t)};
}

void var1() {
  std::variant<int, float, double> v = 1.;
  std::cout << v.index() << '\n';
  v = 3;
  std::cout << v.index() << '\n';
  int x { std::get<int>(v) };
}

std::optional<int> get_index() {
  return std::nullopt;
}

void opt1() {
  if (auto opt = get_index())
    std::cout << *opt << '\n';
  // else opt.value_or(-1);
}

void any1(std::any *a) {
  if (auto i = std::any_cast<int>(a))
    std::cout << *i << '\n';
  else if (auto i = std::any_cast<float>(a))
    std::cout << *i << '\n';
}

struct Add {
  int x;
  int operator()(int b) const noexcept {
    return x + b;
  }
};

int fun1(std::function<int(int)> f) {
  return f(f(f(3)));
}

int fun2() {
  int x = 1;
  fun1([x](int b) { return x + b; });
  return fun1(Add{1});
}

void sv1() {
  std::string s = "Hello World!";
  std::string_view sv{s};
  auto space = sv.find_first_of(' ');
  std::string_view word1 = sv.substr(0, space);
  std::locale loc{""};
  sv.remove_prefix(space + 1);
  auto word_end = std::find_if(sv.begin(), sv.end(),
                               [&loc](char c) { return !std::isalpha(c, loc); }) -
                  sv.begin();
  std::string_view word2 = sv.substr(0, word_end);
  auto i = sv.begin();
  while (i!= sv.end())
    std::cout << *i++ << ", ";
  // int i = 0;
  // std::cout << i++;
  // std::cout << i;
  // std::cout << ++i;
}

void f() {
  std::logic_error e{"bad logic"};
  throw e;
}
int main() {
  std::locale loc{""};
  std::cout << 3.1415926 << "\n";
  std::cout.imbue(loc);
  // std::locale::global(loc);
  std::cout << 3.1415926 << "\n";
  std::cout << loc.name() << "\n";
  var1();
  try {
    // std::vector<int> v(10);
    // int * p = &v[0];
    // *p = 3;
    // p = &v[1];
    // int & r = v[0];
    // r = 2;
    // p = &r;
    throw 1;
    f();
  } catch (std::exception &ex) {
    std::cerr << ex.what() << '\n';
  } catch (...) {
    std::cerr << "Unknown error\n";
    throw;
  }
  return 0;
}