cmake_minimum_required (VERSION 2.6) 

include_directories (${VERSE_API_SOURCE_DIR}/modules)

file(GLOB lib_srcs *.cpp)
file(GLOB lib_hdrs *.h)

set( devices_srcs
		Platform.cpp
)
set( devices_hdrs
		Platform.h
)

IF(WIN32)
	SET( devices_srcs ${devices_srcs} Vuzix.cpp )
	SET( devices_hdrs ${devices_hdrs} Vuzix.h )
ENDIF(WIN32)

add_library(VerseDevices STATIC ${devices_srcs} ${devices_hdrs})

IF(WIN32)
	add_dependencies(VerseDevices ${VUZIX_LIBRARY})
	target_link_libraries(VerseDevices ${VUZIX_LIBRARY})
ENDIF(WIN32)
