configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)


add_definitions(-DDAFEI)
add_library(foo STATIC foo.c foo.h config.h.in)

set_target_properties(foo PROPERTIES
  PUBLIC_HEADER "foo.h;${CMAKE_CURRENT_BINARY_DIR}/config.h")
set_target_properties(foo PROPERTIES
  COMPILE_DEFINITIONS "${COMPILE_DEFINITIONS}")

get_target_property(tmp foo COMPILE_DEFINITIONS)
message("dafei in foo cmake file get_target_property COMPILE_DEFINITIONS:${tmp}")

get_target_property(tmp foo PUBLIC_HEADER)
message("dafei in foo cmake file get_target_property PUBLIC_HEADER:${tmp}")

install(TARGETS foo
  # IMPORTANT: Add the foo library to the "export-set"
  EXPORT FooBarTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/foo"
    COMPONENT dev)
