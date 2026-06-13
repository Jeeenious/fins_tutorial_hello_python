/*******************************************************************************
 * nodes.cpp — 插件入口
 *
 * 加载 .so 时，FINS 框架通过 DEFINE_PLUGIN_ENTRY 进入插件，
 * 然后 py_bridge::init() 在静态初始化阶段启动 Python 解释器。
 ******************************************************************************/

#include "hello_python.hpp"

// Python 解释器采用惰性初始化（节点首次调用 Python 时自动启动）
DEFINE_PLUGIN_ENTRY(fins::STATELESS)
