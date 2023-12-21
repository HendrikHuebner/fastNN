cmake_minimum_required(VERSION 3.27)
project(fastNN)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_library(fastNN SHARED
        src/model/Model.cpp
        include/model/Model.h
        src/math/Matrix.cpp
        include/math/Matrix.h
        src/math/Vector.cpp
        include/math/Vector.h
        include/model/activationFunction.h
        src/model/activationFunction.cpp
        src/model/costFunction.cpp
        include/model/Layer.h
        src/model/DenseLayer.cpp
        include/model/DenseLayer.h
        src/model/OutputLayer.cpp
        include/model/OutputLayer.h
        include/model/weightInit.h)

target_include_directories(fastNN PUBLIC ${INCLUDE_DIR})
add_executable(test ${CMAKE_CURRENT_SOURCE_DIR}/test/test.cpp)
target_link_libraries(test PRIVATE fastNN)
