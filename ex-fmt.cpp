#include "range/v3/algorithm/find.hpp"
#include "range/v3/algorithm/lower_bound.hpp"
#include "range/v3/numeric/accumulate.hpp"
#include "range/v3/range/conversion.hpp"
#include "range/v3/view/filter.hpp"
#include "range/v3/view/split.hpp"
#include "range/v3/view/transform.hpp"
#include <iostream>
#include <fmt/core.h>
#include <gsl/span>
#include <vector>
#include <range/v3/all.hpp>

void f(gsl::span<int> v) {
    // gsl::span<int> v2 = v;
    for (int& i : v)
        i *= i;
}

using namespace ranges;

double f(double x) {
    return x;
}

int main() {
    double pi = 3.1415926;
    std::cout << fmt::format("{}\n", pi);
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7};
    f(gsl::span<int>(v).subspan(2,3));
    for (int i : v)
        std::cout << i << ", ";
    std::cout << "\n";
    auto size = v.end() - v.begin();
    int i = 0;
    std::cout << i++ << ", ";
    std::cout << ++i << "\n";
    auto r = ranges::find_if(v, [](int a) { return a % 3 == 0; });
    int res = 0;
    for (auto a : v) {
        if (a % 2 == 1)
            res += a*a*a;
        // if (auto b = process(a))
        //     res += *b;
    }
    auto r2 = ranges::accumulate(
        v | views::filter([](int a) { return a % 2 == 1; }) |
            views::transform([](int a) { return a * a * a; }),
        0);
    std::vector<double> vd;
    auto pos =
        ranges::lower_bound(views::ints(1,1000'000'000) |
                                views::transform([](int a) { return f(a/100.); }),
                            0);
    // map(lambda a: a*a*a, filter(lambda a: a%2==1, v))
    // std::string s;
    // auto ss = s | views::split(' ') | ranges::to<std::set<std::string_view>>;
    // std::cout << pi << "\n";
    return 0;
}