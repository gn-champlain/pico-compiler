# PicoISA backend library
# Assumes tablegen headers are created by "PicoTableGen" into:
#   ${PROJECT_BINARY_DIR}/include/PicoISA/Gen

include(GNUInstallDirs)

# Ensure LLVM is loaded (from the top level find_package)
if(NOT LLVM_FOUND)
  find_package(LLVM REQUIRED CONFIG)
endif()

# Helpful LLVM CMake helpers
include("${LLVM_CMAKE_DIR}/AddLLVM.cmake")

# 1) Source files for the backend
set(PICOISA_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/PicoInstrInfo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PicoRegisterInfo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PicoSubtarget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PicoTargetMachine.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PicoTarget.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/TargetDesc/PicoMCTargetDesc.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/TargetDesc/PicoMCAsmInfo.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/TargetInfo/PicoTargetInfo.cpp
)

# 2) Create the library
add_library(LLVMPicoISA STATIC ${PICOISA_SOURCES})

# 3) Include paths
target_include_directories(LLVMPicoISA
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/Target/PicoISA
    ${PROJECT_BINARY_DIR}/include
    ${PROJECT_BINARY_DIR}/include/PicoISA/Gen
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}                # so "TargetDesc/..." works
    ${LLVM_INCLUDE_DIRS}                       # headers like <llvm/...>
)

# 4) Common definitions
target_compile_definitions(LLVMPicoISA
  PRIVATE
    ${LLVM_DEFINITIONS}
    __STDC_CONSTANT_MACROS
    __STDC_FORMAT_MACROS
    __STDC_LIMIT_MACROS
)

# 5) MSVC quality of life
if(MSVC)
  target_compile_options(LLVMPicoISA PRIVATE /bigobj /Zc:__cplusplus)
  target_compile_definitions(LLVMPicoISA PRIVATE NOMINMAX)
endif()

# 6) Link to LLVM components
llvm_map_components_to_libnames(LLVM_LIBS
  core
  support
  mc
  mca
  mcparser
  ipo
  codegen
  selectiondag
  target
  asmparser
  asmprinter
)
target_link_libraries(LLVMPicoISA PRIVATE ${LLVM_LIBS})

# 7) Make sure generated headers exist before building
add_dependencies(LLVMPicoISA PicoTableGen)

# 8) Nice grouping in IDEs
set_target_properties(LLVMPicoISA PROPERTIES FOLDER "Targets/PicoISA")

# 9) Optional install
# install(TARGETS LLVMPicoISA
#   ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
