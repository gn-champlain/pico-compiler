# Build the pico_sanity test

if(NOT LLVM_FOUND)
  find_package(LLVM REQUIRED CONFIG)
endif()

include("${LLVM_CMAKE_DIR}/AddLLVM.cmake")

# Force LLVM headers onto the include path for everything in this dir too
include_directories(BEFORE SYSTEM ${LLVM_INCLUDE_DIRS})

# Minimal set of LLVM libs
llvm_map_components_to_libnames(LLVM_TEST_LIBS
  support
  core
  mc
  mcparser
  target
  asmparser
  asmprinter
)

add_executable(pico_sanity pico_sanity.cpp)

# Also attach includes + defs directly to the target
target_include_directories(pico_sanity PRIVATE
  ${LLVM_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_BINARY_DIR}/include/PicoISA/Gen
)
target_compile_definitions(pico_sanity PRIVATE ${LLVM_DEFINITIONS})

target_link_libraries(pico_sanity PRIVATE
  LLVMPicoISA
  ${LLVM_TEST_LIBS}
)

# Ensure generated headers and backend lib exist first
add_dependencies(pico_sanity PicoTableGen LLVMPicoISA)