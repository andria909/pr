cmake_minimum_required(VERSION 3.10)
project(PrimeTests)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_library(utils src/utils.cpp)

add_library(prime_lib src/main.cpp)


enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests test/test.cpp)
target_link_libraries(tests GTest::GTest GTest::Main prime_lib utils)

add_test(NAME RunTests COMMAND tests)
