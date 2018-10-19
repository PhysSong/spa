# build the main library

set(spa_src audio.cpp spa.cpp)
set(spa_hdr ../include/spa/spa_fwd.h ../include/spa/spa.h
        ../include/spa/audio_fwd.h ../include/spa/audio.h)
include_directories(../include/rtosc/include)
include_directories(../include/ringbuffer/include)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
	if(NOT WIN32)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
	endif()
	set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 ${FLTO_FLAGS}")
endif()
add_library(spa STATIC
        ${spa_src} ${spa_hdr}
        ${rtosc_lib_src} ${rtosc_lib_hdr}
        ${ringbuffer_lib_src} ${ringbuffer_lib_hdr})
install(TARGETS spa
	EXPORT spa-export
	ARCHIVE DESTINATION ${INSTALL_LIB_DIR})
