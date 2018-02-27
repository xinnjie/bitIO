project(test)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runBitIOTests basic_check.cpp)
target_link_libraries(runBitIOTests gtest gtest_main)
target_link_libraries(runBitIOTests bitio)
