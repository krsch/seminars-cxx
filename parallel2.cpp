#include <algorithm>
#include <pstl/numeric>
#include <pstl/algorithm>
#include <pstl/execution>
#include <range/v3/view.hpp>
#include <thread>
#include <vector>
#include <iostream>
#include <functional>
#include <mutex>
#include <future>
#include <chrono>

// using namespace std::chrono_literals;
using namespace std::literals;
std::chrono::seconds operator""_s(unsigned long long x){
  return std::chrono::seconds(x);
}

std::mutex cout_mutex;
std::mutex cout_mutex2;

double f(int idx) {
  {
    std::scoped_lock lock(cout_mutex, cout_mutex2);
    std::cout << "Starting thread " << idx << "\n";
  }
  std::this_thread::sleep_for(1_s);
  // unsigned long x = idx;
  // for (int i = 0; i < 1000'000'000; ++i)
  //   x *= x + 1;
  {
    std::scoped_lock lock(cout_mutex2, cout_mutex);
    std::cout << "Thread " << idx << " got result " << 0 << "\n";
  }
  return 0.;
}

int main() {
    // std::vector v{0,1,2,3};
    // std::vector<double> out(4);
    // std::transform(std::execution::par, v.begin(), v.end(), out.begin(), f);
    auto f1 = std::async(std::launch::async, f, 1);
    int x = 2;
    std::thread t2([&x]() { return f(x); });
    // auto f2 = std::async(std::launch::async, f, 2);
    f1.wait();
    std::cout << "Thread 1 returned " << f1.get() << "\n";
    t2.join();
    std::cout << "Thread 2 returned " << 0 << "\n";
    auto s = "1234"s;
    auto sv = "1234"sv;
    return 0;
}