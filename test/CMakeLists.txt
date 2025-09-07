cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
add_executable(mytest ringbuf_test.cpp)
target_link_libraries(mytest ringbuf GTest::gtest_main)
include_directories(../src)
include(GoogleTest)

gtest_discover_tests(mytest)
