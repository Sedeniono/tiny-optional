cmake_minimum_required(VERSION 3.14)

project(
    tiny-optional
    VERSION 1.5.2
    DESCRIPTION "Replacement for std::optional that does not waste memory unnecessarily."
    HOMEPAGE_URL "https://github.com/Sedeniono/tiny-optional"
    LANGUAGES CXX
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(tiny-optional INTERFACE)
add_library(tiny-optional::tiny-optional ALIAS tiny-optional)

if (NOT PROJECT_IS_TOP_LEVEL)
    set(warning_guard SYSTEM)
endif()

target_include_directories(
    tiny-optional ${warning_guard}
    INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
              "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

target_compile_features(tiny-optional INTERFACE cxx_std_17)

install(
    DIRECTORY include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(
    TARGETS tiny-optional
    EXPORT tiny-optionalTargets
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")

write_basic_package_version_file(
    "tiny-optionalConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    # Different major and minor versions of tiny::optional cannot be mixed.
    # It is actively prevented by the use of inline namespaces.
    COMPATIBILITY SameMinorVersion)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/tiny-optionalConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/tiny-optionalConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}/tiny-optional")

install(
    EXPORT tiny-optionalTargets
    FILE tiny-optionalTargets.cmake
    NAMESPACE tiny-optional::
    DESTINATION "${CMAKE_INSTALL_DATADIR}/tiny-optional")
    
install(
    FILES "${PROJECT_BINARY_DIR}/tiny-optionalConfig.cmake"
          "${PROJECT_BINARY_DIR}/tiny-optionalConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/tiny-optional")
