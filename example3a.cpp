#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct S {
    int val = 0;
    S() = default;
    explicit S(int a) : val(a) {}
    S(S const & s) {
        if (s.val == 4) throw std::logic_error("Bad value");
        val = s.val;
        std::cout << "S::S(S const & s = " << s.val << ")\n";
    }
    S& operator=(S const& s) {
        val = s.val;
        std::cout << "S::operator=(S const & s = " << s.val << ")\n";
        return *this;
    }
    S(S && s) {
        if (s.val == 4) throw std::logic_error("Bad value");
        val = s.val;
        s.val = 0;
        std::cout << "S::S(S && s = " << s.val << ")\n";
    }
    S& operator=(S && s) noexcept {
        val = s.val;
        s.val = 0;
        std::cout << "S::operator=(S && s = " << s.val << ")\n";
        return *this;
    }
    explicit operator int() {
        return val;
    }
};

void g() {
    std::vector<S> vs{S{1},S{2},S{3}};
    vs[2].val = 4;
    int x = static_cast<int>(vs[0]);
    try {
        vs.emplace_back();
    } catch (std::exception const& e) {
        std::cerr << "Cannot emplace: " << e.what() << "\n";
    }
    std::cout << "vs.size() = " << vs.size() << ": {";
    for (auto& s : vs)
      std::cout << s.val << ", ";
    std::cout << "}\n";
    // S s1{2};
    // S s2 = s1;
    // s1 = S{};
    int i = 0, j = 2;
    int & r = i;
    r = j; // i = j;
    std::swap(vs[0], vs[1]);
}

void f() {
    throw std::runtime_error("some error");
}
int main()
{
    try {
        g();
    } catch (std::exception const& e) {
        std::cerr << e.what() << "\n";
    } catch (...) {
        std::cerr << "Some unknown error\n";
        throw;
    }
    return 0;
}