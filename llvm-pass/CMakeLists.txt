cmake_minimum_required(VERSION 3.10)
project(llvm_pass LANGUAGES CXX)

# Build the pass as a DLL
add_library(MyOptimizer SHARED
    MyOptimizer.cpp
)

# On MSVC, explicitly include the .def so llvmGetPassPluginInfo is exported
if (MSVC)
  target_sources(MyOptimizer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/llvm-pass.def)
endif()

# Inherit LLVM include dirs from the parent CMake (already set there)
target_include_directories(MyOptimizer PRIVATE ${LLVM_INCLUDE_DIRS})

# Link against the same LLVM libs used by the parent (variable is visible to subdirs)
# If this variable doesn't exist in your parent, we’ll hard-link specific LLVM targets next step.
target_link_libraries(MyOptimizer PRIVATE ${llvm_libs})
