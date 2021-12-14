cmake_minimum_required(VERSION 2.8)
project(test CXX)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
add_executable(a.out main.cpp)
target_link_libraries(a.out ${PYTHON_LIBRARIES})

