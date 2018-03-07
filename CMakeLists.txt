cmake_minimum_required(VERSION 3.8)
project(bitio)
set(CMAKE_CXX_STANDARD 11)

include_directories(bitio)

add_subdirectory(bitio)
add_subdirectory(bitio_tests)


SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
