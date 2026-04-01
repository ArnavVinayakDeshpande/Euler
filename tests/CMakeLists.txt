cmake_minimum_required(VERSION 3.24.0)

set(EULER_TESTS_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include/")

add_executable(test_common "common/main.cpp")
target_include_directories(test_common PRIVATE "common" "${EULER_TESTS_INC_DIR}")
target_link_libraries(test_common PRIVATE euler)
