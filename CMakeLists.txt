cmake_minimum_required(VERSION 3.10)
project(Pico_IR_Backend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

# Find LLVM
find_package(LLVM REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Add your source files
add_executable(Pico_IR_Backend
    src/main.cpp
    src/lexer.cpp
    src/symbol_table.cpp
    src/token.cpp
    src/ast.cpp
    src/ir_generator.cpp
)

# Map the LLVM components
llvm_map_components_to_libnames(llvm_libs
    core
    irreader
    analysis
    transformutils
    scalaropts
)

target_link_libraries(Pico_IR_Backend ${llvm_libs})
