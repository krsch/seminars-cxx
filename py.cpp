#include <vector>
#include <numeric>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

int add(std::vector<int> const& v) {
    return std::accumulate(v.begin(), v.end(), 0);
}

PYBIND11_MODULE(py_cpp, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function which adds two numbers");
}