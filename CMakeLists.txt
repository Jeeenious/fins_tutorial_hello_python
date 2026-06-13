cmake_minimum_required(VERSION 3.16)

project(fins_hello_python)

# ── Python 3 ──
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# ── pybind11 ──
find_package(pybind11 REQUIRED)

# ── FINS 节点 ──
fins_add_node(${PROJECT_NAME} nodes.cpp py_bridge.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${Python3_INCLUDE_DIRS}
  ${pybind11_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  pybind11::embed
  Python3::Python
)
