# Minimal placeholder TableGen target so LLVMPicoISA can depend on it.

# Ensure the generated include directory exists
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/include/PicoISA/Gen")

add_custom_target(PicoTableGen ALL
  COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/include/PicoISA/Gen"
  COMMENT "Preparing generated headers directory for PicoISA"
)