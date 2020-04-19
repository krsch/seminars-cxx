#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

void f(std::vector<int> & v)
{
  auto start = begin(v);
  int & first = *start;
  start += 1;
  first = 5;
  *start = 6;
  //sort(begin(v), end(v));
  //sort(v);
}

int main() {
  int i;
  double d;
  std::vector<int> v{1,2,3,4,5};
  std::map<int, double> m;
  char c;
  std::string str;
  // for (int el : v)
  //   std::cout << el << ", ";
  // std::cout << "\n";
  // f(v);
  // for (int el : v)
  //   std::cout << el << ", ";
  // std::cout << "\n";
  // for (int i=0; i<v.size(); ++i)
  //   std::cout << v[i] << "\n";
  std::set<int> s1{2,3,4,5}, s2{1,2,3};
  // std::vector<int> v2(std::max(s1.size(), s2.size()));
  std::vector<int> v2;
  auto out = std::back_inserter(v2);
  auto new_end = std::set_intersection(s1.begin(), s1.end(), s2.begin(),
                                       s2.end(), out);
  // ranges::set_intersection(s1, s2, v2);
  // v2.resize(new_end - v2.begin());
  // v2.erase(new_end, v2.end());
  for (int el : v2)
    std::cout << el << ", ";
  std::cout << "\n";
  return 0;
}