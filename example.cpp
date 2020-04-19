#include <set>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

void f(std::vector<int> &v) {
  v[0] = 5;
  std::sort(v.begin(), v.end());
  auto it = v.begin();
  int ref = *it;
  ref = 10;
  it += 1;
  ++it;
  *it = 8;
  int sz = v.end() - it;
}

int main()
{
  int i = 0;
  double d = 0.0;
  char c = 'c';
  bool b = true;
  std::string str = "123";
  std::vector<int> v = {1, 2, 3}, v2 = {3,2,1};
  std::set<int> s = {1, 2, 3, 4};
  std::map<int, double> m = {{1, 1.0}};
  f(v);
  for (int el : v)
    std::cout << el << ", ";
  for (auto it = v.begin(), e = v.end(); it != e; ++it) {
    int el = *it;
    std::cout << el << ", ";
  }
  std::cout << "\n";
//   for (auto & [key, value] : m) {
//     value += 1;
//     std::cout << key << ": " << value << ", ";
//   }
//   std::cout << "\n";
  std::vector<double> factorials(100);
  factorials.front() = 1; // factorials[0], *(factorials.begin())
  factorials.back(); // factorials[factorials.size() - 1]
   // *(factorial.end() - 1)
  for (int i=1; i<factorials.size(); ++i)
    factorials[i] = factorials[i-1] * i;
  return 0;
}