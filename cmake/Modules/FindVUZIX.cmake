# - Try to find VUZIX
# Once done this will define
#  VUZIX_FOUND - System has VUZIX
#  VUZIX_INCLUDE_DIRS - The VUZIX include directories
#  VUZIX_LIBRARIES - The libraries needed to use VUZIX
#  VUZIX_DEFINITIONS - Compiler switches required for using VUZIX

find_path(VUZIX_INCLUDE_DIR iWearSDK.h)

find_library(VUZIX_LIBRARY NAMES iweardrv VUZIX)

set(VUZIX_LIBRARIES ${VUZIX_LIBRARY} )
set(VUZIX_INCLUDE_DIRS ${VUZIX_INCLUDE_DIR} )
set(VUZIX_INCLUDE ${VUZIX_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set VUZIX_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(VUZIX  DEFAULT_MSG
                                  VUZIX_LIBRARY VUZIX_INCLUDE_DIR)

mark_as_advanced(VUZIX_INCLUDE_DIR VUZIX_LIBRARY )