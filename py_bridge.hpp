/*******************************************************************************
 * py_bridge.hpp — C++ 可调用的 Python HelloPython 接口
 *
 * 将 hello_py 中的 Python 函数封装为 C++ 函数。
 * FINS 节点只需调这些函数，不直接接触 Python API。
 ******************************************************************************/
#pragma once

#include <string>

namespace py_bridge {

/// 初始化 Python 解释器，导入 hello_py 包
void init();

/// 调 Python hello_py.source.generate() → C++ string
std::string generate_message();

/// 调 Python hello_py.printer.print_msg(msg)
void print_message(const std::string &msg);

}  // namespace py_bridge
