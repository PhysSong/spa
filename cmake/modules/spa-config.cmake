# WARNING: Not working, and *may* be removed in future versions
# use pkg config instead (or fix this file...)

# - Try to find SPA
# Once done this will define
#  SPA_FOUND - System has SPA
#  SPA_INCLUDE_DIRS - The SPA include directories
#  SPA_LIBRARY_DIRS - The SPA library directories
#  SPA_LIBRARIES - The libraries needed to use SPA
#  SPA_DEFINITIONS - Compiler switches required for using SPA


message(STATUS "FOUND SPA CONFIG!!!!!")
set(SPA_INCLUDE_DIR "@CMAKE_INSTALL_PREFIX@/include")
set(SPA_LIBRARY_DIR "@CMAKE_INSTALL_PREFIX@/@INSTALL_LIB_DIR@")
set(SPA_LIBRARY spa)


add_library(SPA STATIC IMPORTED)

set_target_properties(SPA PROPERTIES
	INTERFACE_INCLUDE_DIRECTORIES "${SPA_INCLUDE_DIR}"
	INTERFACE_LINK_LIBRARIES "spa"
)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBSPA_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(SPA DEFAULT_MSG
				  SPA_INCLUDE_DIR SPA_LIBRARY_DIR SPA_LIBRARY)

mark_as_advanced(SPA_INCLUDE_DIR SPA_LIBRARY_DIR SPA_LIBRARY)

set(SPA_INCLUDE_DIRS ${SPA_INCLUDE_DIR})
set(SPA_LIBRARY_DIRS ${SPA_LIBRARY_DIR})
set(SPA_LIBRARIES ${SPA_LIBRARY})

