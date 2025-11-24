cmake_minimum_required(VERSION 3.20)

project(pico_tablegen LANGUAGES CXX)

# 1) Force C++17 everywhere
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 2) Point CMake to your LLVM cmake package.
#    You can override this at configure time with:
#    -DLLVM_DIR="C:/Users/nanda/Desktop/llvm-project/build/lib/cmake/llvm"
if(NOT DEFINED LLVM_DIR)
  set(LLVM_DIR "C:/Users/nanda/Desktop/llvm-project/build/lib/cmake/llvm")
endif()

# 3) Find LLVM 17
find_package(LLVM 17 REQUIRED CONFIG)

message(STATUS "Using LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVM include dirs: ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM definitions: ${LLVM_DEFINITIONS}")

# 4) Bring in LLVM compile defs and includes the right way
add_definitions(${LLVM_DEFINITIONS})
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})

# 5) Make sure our generated headers (from tablegen) are discoverable
#    They are emitted under build/include/PicoISA/Gen
include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/include/PicoISA/Gen)

# 6) Our own public headers live here
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/Target/PicoISA)

# 7) Build the backend target directory
add_subdirectory(lib/TableGen)
add_subdirectory(lib/Target/PicoISA)

include_directories(BEFORE SYSTEM ${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_subdirectory(tests)
