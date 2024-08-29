cmake_minimum_required(VERSION 3.12)
project(fastNN)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CPP_COMPILER gcc)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fno-stack-protector")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

# config
option(BUILD_TESTS "Enable / Disable test suite" ON)
option(PYTHON_STUBS "Enable / Disable python stubs" OFF)
option(AVX_MODE "Enable / Disable avx mode" OFF)
option(CUDA_MODE "Enable / Disable CUDA mode" OFF)
set(SAN "none" CACHE STRING "Sanitizer (none, address, thread, undefined)")

# sources 
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(fastNN SHARED  ${INCLUDE_FILES} ${SOURCE_FILES})
add_subdirectory(src)
add_subdirectory(include)

target_include_directories(fastNN PUBLIC ${INCLUDE_DIR})

if (SAN STREQUAL "address")
    message(STATUS "Enabling AddressSanitizer.")
    set(SANITIZER_FLAGS "-fsanitize=address -fno-omit-frame-pointer")
    set(ENV{ASAN_OPTIONS} "detect_leaks=1")

elseif (SAN STREQUAL "thread")
    message(STATUS "Enabling ThreadSanitizer.")
    set(SANITIZER_FLAGS "-fsanitize=thread")

elseif (SAN STREQUAL "undefined")
    message(STATUS "Enabling UB Sanitizer.")
    set(SANITIZER_FLAGS "-fsanitize=undefined")
endif()

if (AVX_MODE)
    if (CUDA_MODE)
        message(WARNING "CUDA and AVX512 are both enabled. Using CUDA implementation.")

    else()
        include(CheckCXXCompilerFlag)
        check_cxx_compiler_flag("-mavx512f" COMPILER_SUPPORTS_AVX512)

        if(COMPILER_SUPPORTS_AVX512)
            add_definitions(-D__AVX512__)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx512f")
            message(STATUS "Enabling AVX512.")

        else()

            message(WARNING "AVX512 not supported by the compiler. Falling back to regular implementation.")
        endif()
    endif()
endif()

# python language interface
if (PYTHON_STUBS)
    # file(GLOB_RECURSE PYTHON_COMPAT "${CMAKE_CURRENT_SOURCE_DIR}/compat/*.cpp")

    # requires pybind11
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
    message(STATUS "Building python stubs.")

endif()

# unit tests
if (BUILD_TESTS)
    message(STATUS "Building Unit tests.")
    
    include(FetchContent)
    
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        DOWNLOAD_EXTRACT_TIMESTAMP NEW
    )
    
    enable_testing()

    FetchContent_MakeAvailable(googletest)

    add_executable(tests)
    add_subdirectory(test)
    
    SET(CTEST_OUTPUT_ON_FAILURE ON)

    target_link_libraries(
        tests
        GTest::gtest_main
        fastNN
    )

    include(GoogleTest)
    gtest_discover_tests(tests)
    
endif()
