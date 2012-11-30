# - Try to find PTHREAD
# Once done this will define
#  PTHREAD_FOUND - System has PTHREAD
#  PTHREAD_INCLUDE_DIRS - The PTHREAD include directories
#  PTHREAD_LIBRARIES - The libraries needed to use PTHREAD
#  PTHREAD_DEFINITIONS - Compiler switches required for using PTHREAD

find_path(PTHREAD_INCLUDE_DIR iWearSDK.h)

find_library(PTHREAD_LIBRARY NAMES iweardrv PTHREAD)

set(PTHREAD_LIBRARIES ${PTHREAD_LIBRARY} )
set(PTHREAD_INCLUDE_DIRS ${PTHREAD_INCLUDE_DIR} )
set(PTHREAD_INCLUDE ${PTHREAD_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set PTHREAD_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(PTHREAD  DEFAULT_MSG
                                  PTHREAD_LIBRARY PTHREAD_INCLUDE_DIR)

mark_as_advanced(PTHREAD_INCLUDE_DIR PTHREAD_LIBRARY )