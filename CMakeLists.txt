cmake_minimum_required(VERSION 3.12)
project(fastNN)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)
include_directories(${pybind11_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE PYTHON_COMPAT "${CMAKE_CURRENT_SOURCE_DIR}/compat/*.cpp")

# python module
pybind11_add_module(pyfastNN ${PYTHON_COMPAT} ${SOURCE_FILES} ${INCLUDE_FILES})
target_include_directories(pyfastNN PUBLIC ${INCLUDE_DIR})

#add_custom_command(
#        TARGET pyfastNN
#        POST_BUILD
#        COMMAND ${Python_EXECUTABLE} "pybind11-stubgen pyfastNN"
#        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
#)

#add_custom_target(generate-stubs DEPENDS pyfastNN)


# library
add_library(fastNN SHARED  ${INCLUDE_FILES} ${SOURCE_FILES})
target_include_directories(fastNN PUBLIC ${INCLUDE_DIR})
# add_executable(test ${CMAKE_CURRENT_SOURCE_DIR}/test/test.cpp)
# target_link_libraries(test PRIVATE fastNN)
