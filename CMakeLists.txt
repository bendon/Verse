cmake_minimum_required (VERSION 2.6) 

PROJECT(VERSE_API)
SET(PROJECT_VERSION "0.1")
# load macros
include(cmake/macros.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}")
SET(RUNTIME_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE PATH "Directory for dlls and binaries")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE PATH "Directory for binaries")
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE PATH "Directory for dlls")


# Opencv Package
FIND_PACKAGE( OpenCV REQUIRED )
IF (${OpenCV_VERSION} VERSION_LESS 2.3.0)
	MESSAGE(FATAL_ERROR "OpenCV version is not compatible : ${OpenCV_VERSION}")
ENDIF()

# OpenGL Package
FIND_PACKAGE( OpenGL REQUIRED )

# GLUT package
find_package(GLUT)#standard package

# FreeType Package
FIND_PACKAGE( Freetype REQUIRED )

# LibXML Package
FIND_PACKAGE( LIBXML2 )
IF (NOT LIBXML2_FOUND)
	include_directories (${VERSE_API_SOURCE_DIR}/3rdparty/libxml2/include)
ENDIF (NOT LIBXML2_FOUND)

IF (WIN32)
	FIND_PACKAGE (PTHREAD REQUIRED)
	FIND_PACKAGE ( VUZIX REQUIRED )
ENDIF (WIN32)

FIND_PACKAGE ( SPHINXBASE REQUIRED )
FIND_PACKAGE ( POCKETSPHINX REQUIRED )


#Libdecodeqr variables. QR
set(QR_LIBRARY libqrdecode)
set(QR_INCLUDE ${VERSE_API_SOURCE_DIR}/3rdparty/libdecodeqr/include)

#Assimp library variables. 3d models
set(ASSIMP_LIBRARY assimp)
set(ASSIMP_INCLUDE ${VERSE_API_SOURCE_DIR}/3rdparty/assimp/include)

#Aruco library variables. Marker detector and transform
set(ARUCO_LIBRARY aruco)
set(ARUCO_INCLUDE ${VERSE_API_SOURCE_DIR}/3rdparty/aruco/src)

include_directories( 
	${OpenGL_INCLUDE_DIR}
	${OpenCV_INCLUDE_DIR}
	${FREETYPE_INCLUDE_DIRS}
	${LIBXML2_INCLUDE_DIR}
	${QR_INCLUDE}
	${ASSIMP_INCLUDE}
	${ARUCO_INCLUDE}
	${VUZIX_INCLUDE}
	${SPHINXBASE_INCLUDE}
	${POCKETSPHINX_INCLUDE}
	${PTHREAD_INCLUDE}
)

#Process folders
add_subdirectory(3rdparty)
add_subdirectory(modules)


#Create Doxygen code documentation.
OPTION(INSTALL_DOC	"Set to OFF to skip build/install Documentation"            ON)
OPTION(USE_DOT		"Set to ON to perform diagram generation with graphviz"     OFF)
OPTION(USE_LATEX	"Set to ON to build latex documentation"                    OFF)
OPTION(USE_CHM		"Set to ON to build CHM Windows documentation"              OFF)
 
IF (INSTALL_DOC)
	GENERATE_DOCUMENTATION(${PROJECT_SOURCE_DIR}/lib${PROJECT_NAME}.dox.in)
ENDIF()
