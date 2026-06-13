/*******************************************************************************
 * py_bridge.cpp — pybind11::embed 实现，调 hello_py Python 模块
 ******************************************************************************/

#include "py_bridge.hpp"

#include <pybind11/embed.h>
#include <pybind11/stl.h>

namespace py = pybind11;

void py_bridge::init() {
  static bool inited = false;
  if (inited) return;
  inited = true;

  // 启动嵌入式 Python 解释器
  py::initialize_interpreter();

  // 将项目目录加入 sys.path，使 import hello_py 能找到
  py::module_ sys = py::module_::import("sys");
  py::list path = sys.attr("path");
  path.attr("insert")(0, "/home/jenny/tutorial/hello-python");

  // 验证导入
  try {
    py::module_::import("hello_py.source");
    py::module_::import("hello_py.printer");
  } catch (py::error_already_set &e) {
    py::print("[py_bridge] Python 导入失败:", e.what());
    throw;
  }
}

std::string py_bridge::generate_message() {
  init();
  py::module_ source = py::module_::import("hello_py.source");
  return source.attr("generate")().cast<std::string>();
}

void py_bridge::print_message(const std::string &msg) {
  init();
  py::module_ printer = py::module_::import("hello_py.printer");
  printer.attr("print_msg")(msg);
}
