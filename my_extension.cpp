//cppimport
/* my_extension.cpp */
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <cmath>
#include <iostream>

using namespace std;
namespace py=pybind11;

void hello_world(int x) {
    std::cout << "Hello world! Your number is " << x << std::endl;
}

void print_double(double x) {
    std::cout << "The double you entered is " << x << std::endl;
}

uint64_t greet_and_return5(std::string name) {
    std::cout << "Howdy, " << name << std::endl;
    return 5;
}

double f_norm(py::array_t<double> mat_py) {
    py::buffer_info info = mat_py.request();
    double* ptr = static_cast<double*>(info.ptr);
    uint64_t num_elements = info.shape[0] * info.shape[1];

    double sq_fnorm = 0.0;
    for(uint64_t i = 0; i < num_elements; i++) {
        sq_fnorm += ptr[i] * ptr[i];
    }
    return sqrt(sq_fnorm);
}

void add3(py::array_t<double> mat_py) {
    py::buffer_info info = mat_py.request();
    double* ptr = static_cast<double*>(info.ptr);
    uint64_t num_elements = info.shape[0] * info.shape[1];

    for(uint64_t i = 0; i < num_elements; i++) {
        ptr[i] += 3.0;
    }
}

py::array_t<double> add3_returncopy(py::array_t<double> mat_py) {
    py::buffer_info info_in = mat_py.request();
    double* ptr_in = static_cast<double*>(info_in.ptr);
    uint64_t num_elements = info_in.shape[0] * info_in.shape[1];

    auto result = py::array_t<double>(info_in.shape);
    py::buffer_info info_out = result.request();
    double* ptr_out = static_cast<double*>(info_out.ptr);

    for(int i = 0; i < num_elements; i++) {
        ptr_out[i] = ptr_in[i] + 3.0;
    }
    return result;
}

PYBIND11_MODULE(my_extension, m) {
    m.def("hello_world", &hello_world);
    m.def("print_double", &print_double);
    m.def("greet_and_return5", &greet_and_return5);
    m.def("f_norm", &f_norm);
    m.def("add3", &add3);
    m.def("add3_returncopy", &add3_returncopy);
}
/*
<%
setup_pybind11(cfg)
%>
*/