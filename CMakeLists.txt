cmake_minimum_required(VERSION 3.25)
project(kuruc C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_CREATE_STATIC_LIBRARY "ar crs <TARGET> <OBJECTS>")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(BUILD_TESTING "Build tests" ON)

include(FetchContent)
FetchContent_Declare(
    jpegli
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/jpegli
)
FetchContent_MakeAvailable(jpegli)

file(GLOB SOURCES "src/*.c")
add_library(${CMAKE_PROJECT_NAME} STATIC
    ${SOURCES}
    $<TARGET_OBJECTS:jpegli-static-obj>
    $<TARGET_OBJECTS:jpegli-libjpeg-obj>
    $<TARGET_OBJECTS:hwy>
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${jpegli_BINARY_DIR}/lib/include/jpegli
    ${INCLUDE_DIRS}
)

find_package(Threads REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    m
    stdc++
    Threads::Threads
)

if(BUILD_TESTING)
    add_subdirectory(tests)
    include(CTest)
    enable_testing()
endif()
