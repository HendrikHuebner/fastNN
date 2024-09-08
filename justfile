build_dir := "./build"

# Build release binary
default:
    cmake -B {{build_dir}} -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF
    ninja -C {{build_dir}}

# Build debug binary
debug:
    cmake -B {{build_dir}} -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug
    ninja -C {{build_dir}}

# Build release and run all tests
check-all:
    cmake -B {{build_dir}} -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug -DAVX_MODE=ON -DBUILD_TESTS=ON
    ninja -C {{build_dir}}
    ctest --test-dir {{build_dir}} --output-on-failure

# Build release and run specific test
check TEST:
    cmake -B {{build_dir}} -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug -DAVX_MODE=ON -DBUILD_TESTS=ON
    ninja -C {{build_dir}}
    ctest --test-dir {{build_dir}} --output-on-failure -R {{TEST}}

# Build debug with address sanitization and test
check-all-asan:
    cmake -B {{build_dir}} -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug -DAVX_MODE=OFF -DBUILD_TESTS=ON -DSAN=address
    ninja -C {{build_dir}}
    ./{{build_dir}}/tests

# Build debug with UB sanitization and test
check-all-ubsan:
    cmake -B {{build_dir}} -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug -DAVX_MODE=ON -DBUILD_TESTS=ON -DSAN=undefined
    ninja -C {{build_dir}}
    ./{{build_dir}}/tests

clean:
    rm -rf {{build_dir}}/*
