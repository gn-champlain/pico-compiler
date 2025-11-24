cmake_minimum_required(VERSION 3.10)

project(Pico_IR_Backend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

# Point CMake to your locally-built LLVM (you pass LLVM_DIR on the command line)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Using LLVM from: ${LLVM_DIR}")
message(STATUS "LLVM include dirs: ${LLVM_INCLUDE_DIRS}")

# Make sure our code sees LLVM headers (IRBuilder.h, etc.)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# -------------------------
# Main Pico IR backend app
# -------------------------
add_executable(Pico_IR_Backend
    src/main.cpp
    src/lexer.cpp
    src/symbol_table.cpp
    src/token.cpp
    src/ast.cpp
    src/ir_generator.cpp
)

# Link minimal LLVM pieces we use
llvm_map_components_to_libnames(llvm_libs
    core
    irreader
    analysis
    transformutils
    scalaropts
)

target_link_libraries(Pico_IR_Backend ${llvm_libs})

# -------------------------
# Out-of-tree LLVM pass
# -------------------------
add_subdirectory(llvm-pass)
