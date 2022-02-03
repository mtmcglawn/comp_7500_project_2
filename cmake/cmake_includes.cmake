include(${BASE_DIR}/cmake/paths.cmake)
include(${CMAKE_DIR}/includes.cmake)
include(${CMAKE_DIR}/compiler.cmake)


#######################################
# Add External Dependencies
#######################################
if(NOT ${CMAKE_SOURCE_DIR} STREQUAL ${BASE_DIR})
	add_subdirectory(${EXTERNAL_DEPS_DIR} ${BUILD_DIR}/external)
endif()
