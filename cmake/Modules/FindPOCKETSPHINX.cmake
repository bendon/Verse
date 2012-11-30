# - Try to find POCKETSPHINX
# Once done this will define
#  POCKETSPHINX_FOUND - System has POCKETSPHINX
#  POCKETSPHINX_INCLUDE_DIRS - The POCKETSPHINX include directories
#  POCKETSPHINX_LIBRARIES - The libraries needed to use POCKETSPHINX
#  POCKETSPHINX_DEFINITIONS - Compiler switches required for using POCKETSPHINX

find_path(POCKETSPHINX_INCLUDE_DIR iWearSDK.h)

find_library(POCKETSPHINX_LIBRARY NAMES iweardrv POCKETSPHINX)

set(POCKETSPHINX_LIBRARIES ${POCKETSPHINX_LIBRARY} )
set(POCKETSPHINX_INCLUDE_DIRS ${POCKETSPHINX_INCLUDE_DIR} )
set(POCKETSPHINX_INCLUDE ${POCKETSPHINX_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set POCKETSPHINX_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(POCKETSPHINX  DEFAULT_MSG
                                  POCKETSPHINX_LIBRARY POCKETSPHINX_INCLUDE_DIR)

mark_as_advanced(POCKETSPHINX_INCLUDE_DIR POCKETSPHINX_LIBRARY )