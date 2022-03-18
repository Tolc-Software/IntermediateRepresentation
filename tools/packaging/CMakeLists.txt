include_guard()

include(GNUInstallDirs)

# Export the IR library
install(
  TARGETS IR
  EXPORT IRTargets
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/IR)
install(
  EXPORT IRTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/IR
  NAMESPACE IR::)
install(FILES ${CMAKE_SOURCE_DIR}/cmake/packaging/IRConfig.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/IR)

# Add License
install(FILES ${CMAKE_SOURCE_DIR}/COPYRIGHT.md ${CMAKE_SOURCE_DIR}/LICENSE.md
        DESTINATION .)

set(CPACK_VERBATIM_VARIABLES YES)
# Allow packaging
include(CPack)
