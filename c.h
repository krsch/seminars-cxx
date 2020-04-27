#ifndef C_H
#define C_H

#include <type_traits>
#define CON 3
#define F(x) ((x)*(x))
template<typename Int>
auto f2(Int x) {
    return x*x;
}
// #undef CON
constexpr int con = 600/F(3+2); // 600/2*3 = 900
inline int t() {
    int i = 1;
    return f2(++i); // int x=++i; return x*x;
}
struct S { int f2() { return 3;} };
#ifdef _MSC_VER
// Code for Microsoft C++
#  if _MSC_VER < 1911
// Code for Visual Studio before 2017 Update 3
#  endif
#else
// Code for GCC and Clang etc.
#endif

#define MY_ASSERT(x) {if (!(x)) std::cerr << "Assertion " #x " failed\n";}

#include <array>
#include <vector>
struct true_type {
    constexpr static bool value = true;
};
template<typename C>
struct is_array_ : std::false_type {};
template<typename V, size_t S>
struct is_array_<std::array<V, S>> : true_type {};
template<typename C>
constexpr bool is_array = is_array_<C>::value;

template<typename C>
int fc(C & c) {
    if constexpr (!is_array<C>) {
        c.resize(100);
    }
    return 1;
}
bool tt() {
    if constexpr (con < 100) {
        std::array<int, con> a;
        return fc(a) > 0;
    } else {
        std::vector<int> a(con);
        return fc(a) > 0;
    }
}

template<int N>
int f() {
    if constexpr (N > 0) {
        return N*f<N-1>();
    } else {
        return 1;
    }
}
#endif