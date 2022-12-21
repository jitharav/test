cmake_minimum_required(VERSION 2.8)

link_directories("${CMAKE_SOURCE_DIR}/lib")
add_executable(test test.cpp)

include_directories(${CMAKE_SOURCE_DIR}/gtest)
include_directories(${CMAKE_SOURCE_DIR}/gtest/internal)
include_directories(${CMAKE_SOURCE_DIR}/gtest/internal/custom)

add_library(hvac hal_x86.cpp hvac.cpp hvac_observer.cpp)

target_link_libraries(test gtestd.lib)

target_link_libraries(test  gtest_maind.lib)

target_link_libraries(test hvac)



