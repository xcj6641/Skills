cmake_minimum_required(VERSION 3.10)
project(MemoryManagement)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# add_executable(TemplateNew TemplateNewandDelete.cpp)
# add_executable(TemplateArray TemplateArrayNewandDelete.cpp)
add_executable(TestMemoryLeak TestMenoryLeak.cpp)