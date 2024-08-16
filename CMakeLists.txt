cmake_minimum_required(VERSION 3.12)
project(fastNN)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fstack-protector")

# config
option(BUILD_TESTS "Enable / Disable test suite" ON)
option(PYTHON_STUBS "Enable / Disable python stubs" OFF)
option(AVX_MODE "Enable / Disable avx mode" OFF)
option(CUDA_MODE "Enable / Disable CUDA mode" OFF)

# sources 
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(fastNN SHARED  ${INCLUDE_FILES} ${SOURCE_FILES})
add_subdirectory(src)
add_subdirectory(include)

target_include_directories(fastNN PUBLIC ${INCLUDE_DIR})

if (AVX_MODE)
    if (CUDA_MODE)
        message("W>> ARNING: CUDA and AVX512 are both enabled. Using CUDA implementation.")

    else()
        include(CheckCXXCompilerFlag)
        check_cxx_compiler_flag("-mavx512f" COMPILER_SUPPORTS_AVX512)

        if(COMPILER_SUPPORTS_AVX512)
            add_definitions(-D__AVX512__)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx512f")
            message(">> Enabling AVX512.")

        else()

            message(">> WARNING: AVX512 not supported by the compiler. Falling back to regular implementation.")
        endif()
    endif()
endif()

# python language interface
if (PYTHON_STUBS)
    # file(GLOB_RECURSE PYTHON_COMPAT "${CMAKE_CURRENT_SOURCE_DIR}/compat/*.cpp")

    # require pybind11
    find_package(Python COMPONENTS Interpreter Development REQUIRED)
    find_package(pybind11 REQUIRED)
    include_directories(${pybind11_INCLUDE_DIRS})

    pybind11_add_module(pyfastNN ${PYTHON_COMPAT} ${SOURCE_FILES} ${INCLUDE_FILES})
    target_include_directories(pyfastNN PUBLIC ${INCLUDE_DIR})

    add_custom_command(
            TARGET pyfastNN
            POST_BUILD
            COMMAND ${Python_EXECUTABLE} "pybind11-stubgen pyfastNN"
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_custom_target(generate-stubs DEPENDS pyfastNN)
    message(">> Building python stubs.")

endif()

# unit tests
if (BUILD_TESTS)
    add_executable(test)
    add_subdirectory(test)
    target_link_libraries(test PRIVATE fastNN)

    message(">> Building Unit tests.")
endif()
