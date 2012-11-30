# ----------------------------------------------------------------------------
#  CMake file for libqrdecode. See root CMakeLists.txt
#
# ----------------------------------------------------------------------------
PROJECT(libqrdecode)

# List of C++ files:

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB lib_srcs *.cpp)
file(GLOB lib_hdrs *.h)

set(the_target "libqrdecode")

add_library(${the_target} STATIC  ${lib_srcs} ${lib_hdrs})
add_dependencies(${the_target} ${OpenCV_LIBS})
target_link_libraries(${the_target} ${OpenCV_LIBS})
