#include <pybind11/embed.h>
#include <iostream>

namespace py = pybind11;

int main() {
    py::scoped_interpreter python;

    py::module sys = py::module::import("sys");
    py::print(sys.attr("path"));

    py::module t = py::module::import("test04");
    t.attr("add")(1, 2);
    return 0;
}
