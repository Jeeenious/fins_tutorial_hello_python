# fins-hello-pybind

FINS HelloWorld 教程的 Python + pybind11 版本。

## 架构

```
hello_py/  (Python 业务逻辑)
  source.py    → generate()  产生 "Hello, World! #N"
  printer.py   → print_msg() 打印消息

py_bridge.cpp  (pybind11 桥接)
  py_bridge::generate_message()  → 调 Python source.generate()
  py_bridge::print_message(msg)  → 调 Python printer.print_msg(msg)

hello_pybind.hpp  (C++ FINS 节点)
  HelloWorldSource    → run() 中调 bridge.generate_message()，1kHz 发送
  HelloWorldPrinter   → 回调中调 bridge.print_message(msg)
```

## 和原始 hello-world 的区别

|        | 原始 hello-world                      | 本示例                             |
| ------ | ----------------------------------- | ------------------------------- |
| 消息生成   | C++ `const std::string msg = "..."` | Python `source.generate()`      |
| 消息打印   | C++ `logger->info(...)`             | Python `printer.print_msg()`    |
| 框架延迟测量 | C++ `fins::latency_us()`            | 相同（仍由 C++ 侧完成）                  |
| 插件入口   | `DEFINE_PLUGIN_ENTRY` 只             | 同上 + 静态 `PyInitGuard` 启动 Python |

## 编译

```bash
fins build
```

## 依赖

- pybind11
