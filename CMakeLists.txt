cmake_minimum_required(VERSION 3.22)
project(pico_compiler CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find LLVM (expects LLVM_DIR to be set)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(pico
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
    src/codegen.cpp
    src/jit.cpp        # <--- Week 5
    src/M88kTargetInfo.cpp   # <--- Week 6 M88k helper
    src/M88kInstrFormats.cpp # <--- Week 6 M88k instruction formats
    src/M88kFallthroughPass.cpp   # <-- Week 7
)

target_include_directories(pico PRIVATE include)

# Map LLVM components to libraries
llvm_map_components_to_libnames(REQ_LLVM_LIBS
    Core
    Support
    OrcJIT
    ExecutionEngine
    MC
    MCJIT
    native
    nativecodegen
)

target_link_libraries(pico PRIVATE ${REQ_LLVM_LIBS})
