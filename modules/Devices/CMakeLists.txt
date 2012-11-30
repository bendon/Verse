cmake_minimum_required (VERSION 2.6) 

include_directories (${VERSE_API_SOURCE_DIR}/modules)

file(GLOB lib_srcs *.cpp)
file(GLOB lib_hdrs *.h)

add_library(VerseDevices STATIC ${lib_srcs} ${lib_hdrs})

add_dependencies(VerseDevices ${VUZIX_LIBRARY})
target_link_libraries(VerseDevices ${VUZIX_LIBRARY})