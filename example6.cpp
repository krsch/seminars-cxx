#include <iostream>
#include <vector>
#include <gsl/span>

int postinc(int i) { // i++
  int j = i;
  i = i + 1;
  return j;
}

int preinc(int i) { // ++i
  i = i + 1;
  return i;
}

int cyclic_at(std::vector<int> const &v, int idx) {
  if (idx < 0)
    return v[v.size() + idx];
  else
    return v[idx];
}

int cyclic_at2(std::vector<int> const &v, int idx) {
    return (idx < 0) ? v[v.size() + idx] : v[idx];
}

int cyclic_at3(std::vector<int> const &v, int idx) {
    // v[(v.size() if idx < 0 else 0) + idx]
    return v[(idx < 0 ? v.size() : 0) + idx];
}

int get_or(gsl::span<int> v, int idx, int def) {
  return (idx < 0 || idx >= v.size()) ? def : v[idx];
}

int main() {
  int i = 0;
  std::cout << i << "\n";
  std::cout << i++ << "\n";
  std::cout << i << "\n";
  std::cout << i++ << "\n";
  std::cout << i << "\n";
  std::cout << i++ << "\n";
  std::cout << i << "\n\n";
  std::cout << ++i << "\n";
  std::cout << i << "\n";
  std::cout << ++i << "\n";
  std::cout << i << "\n";

  std::vector<int> v{1, 2, 3, 4};
  std::vector<int> v2(4);
  auto from = v.begin(), to = v2.begin();
  while (from != v.end())
    *to++ = 2 * *from++ - 1;

  to = v2.begin(); // 1, 3, 5, 7, to: [0]= 1
  for (int i : v2)
    std::cout << i << ", ";
  std::cout << "to: [" << to - v2.begin() << "]= " << *to << "\n";
  ++*to; // 2, 3, 5, 7, to: [0]= 2
  for (int i : v2)
    std::cout << i << ", ";
  std::cout << "to: [" << to - v2.begin() << "]= " << *to << "\n";
  ++to; // 2, 3, 5, 7, to: [0]= 3
  for (int i : v2)
    std::cout << i << ", ";
  std::cout << "to: [" << to - v2.begin() << "]= " << *to << "\n";

  std::vector<int> v4;
  return 0;
}