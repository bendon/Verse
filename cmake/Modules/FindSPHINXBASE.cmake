# - Try to find SPHINXBASE
# Once done this will define
#  SPHINXBASE_FOUND - System has SPHINXBASE
#  SPHINXBASE_INCLUDE_DIRS - The SPHINXBASE include directories
#  SPHINXBASE_LIBRARIES - The libraries needed to use SPHINXBASE
#  SPHINXBASE_DEFINITIONS - Compiler switches required for using SPHINXBASE

find_path(SPHINXBASE_INCLUDE_DIR iWearSDK.h)

find_library(SPHINXBASE_LIBRARY NAMES iweardrv SPHINXBASE)

set(SPHINXBASE_LIBRARIES ${SPHINXBASE_LIBRARY} )
set(SPHINXBASE_INCLUDE_DIRS ${SPHINXBASE_INCLUDE_DIR} )
set(SPHINXBASE_INCLUDE ${SPHINXBASE_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set SPHINXBASE_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(SPHINXBASE  DEFAULT_MSG
                                  SPHINXBASE_LIBRARY SPHINXBASE_INCLUDE_DIR)

mark_as_advanced(SPHINXBASE_INCLUDE_DIR SPHINXBASE_LIBRARY )