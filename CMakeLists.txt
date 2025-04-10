cmake_minimum_required(VERSION 3.10)
project(PrimeTests)

set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/src)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_library(math src/math.cpp)
add_library(random src/random.cpp)
add_library(fft src/fft.cpp)
add_library(prime_tests src/prime_tests.cpp)

add_library(matrix_solver src/matrix_solver.cpp)
target_link_libraries(matrix_solver PRIVATE Eigen3::Eigen)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests test/test.cpp)
target_link_libraries(tests GTest::GTest GTest::Main math matrix_solver random fft  prime_tests)

add_test(NAME RunTests COMMAND tests)



