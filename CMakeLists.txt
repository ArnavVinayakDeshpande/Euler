cmake_minimum_required(VERSION 3.24.0)

project(Euler)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(EULER_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(EULER_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(EULER_TST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test/")

file(GLOB_RECURSE EULER_SRC_FILES "${EULER_SRC_DIR}/*.cpp" CONFIGURE_DEPENDS "${EULER_SRC_DIR}/*.cpp")
file(GLOB_RECURSE EULER_INC_FILES "${EULER_INC_DIR}/*.hpp" CONFIGURE_DEPENDS "${EULER_INC_DIR}/*.hpp")

option(EULER_BUILD_SHARED "Build Euler as shared library" OFF)

if (EULER_BUILD_SHARED)
    add_library(euler SHARED ${EULER_SRC_FILES})
    target_compile_definitions(euler PRIVATE EULER_LIB_SHARED)
else()
    add_library(euler STATIC ${EULER_SRC_FILES})
    target_compile_definitions(euler PRIVATE EULER_LIB_STATIC)
endif()

target_include_directories(euler PUBLIC ${EULER_SRC_DIR} ${EULER_INC_DIR})
target_compile_definitions(
    euler PUBLIC 
    $<$<CONFIG:Debug>:EULER_BUILD_DBG>
    $<$<CONFIG:Release>:EULER_BUILD_RLS>)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/tests")
