cmake_minimum_required(VERSION 2.8)
# settings
project(spa)
set(DESCRIPTION "OSC plugin api")

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "0")
SET(VERSION_PATCH "1")

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	# enable these flags if you get tons of errors from boost...
	# set(WARN_EXC "-Wno-unused-local-typedefs -Wno-maybe-uninitialized")
	set(FLTO_FLAGS "-flto")
else()
	set(FLTO_FLAGS "")
endif()

# processing
include(cmake/process_project.txt)

# Spa CMake Config. Not finished and not working yet. May be removed
# Use pkg config instead
include(CMakePackageConfigHelpers)
export(EXPORT spa-export FILE cmake/modules/spa-config.cmake NAMESPACE TestSpace)
configure_file(cmake/modules/spa-config.cmake "${CMAKE_CURRENT_BINARY_DIR}/spa-config.cmake" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/spa-config.cmake" DESTINATION "${INSTALL_LIB_DIR}/cmake/SPA")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/spa.pc.in
	${CMAKE_CURRENT_BINARY_DIR}/spa.pc @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/spa.pc"
	DESTINATION "${INSTALL_LIB_DIR}/pkgconfig")


# examples
add_subdirectory(examples)

print_summary_base()

