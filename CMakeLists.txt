cmake_minimum_required(VERSION 3.10)
project(MyProgram LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)

add_executable(main main.cpp SearchEngine.cpp)
