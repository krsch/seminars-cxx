#include <pstl/numeric>
#include <pstl/execution>
#include <range/v3/view.hpp>
#include <benchmark/benchmark.h>
#include <vector>
#include <iostream>
#include <functional>

template<typename Policy>
static void BM_reduce(Policy && policy, benchmark::State &state) {
  // Perform setup here
  std::vector v{1, 2, 3, 4};
  auto r = v | ranges::views::cycle;
  for (auto _ : state) {
    // This code gets timed
    benchmark::DoNotOptimize(
        std::reduce(policy, r.begin(), r.begin() + 1'000'000, 0L));
  }
}
auto BM_seq (benchmark::State &s) {
  return BM_reduce(std::execution::seq, s);
};
auto BM_par = [](benchmark::State &s) {
  return BM_reduce(std::execution::par, s);
};
auto BM_par_unseq = [](benchmark::State &s) {
  return BM_reduce(std::execution::par_unseq, s);
};
BENCHMARK(BM_par);
BENCHMARK(BM_par_unseq);
BENCHMARK(BM_seq);
BENCHMARK_MAIN();
