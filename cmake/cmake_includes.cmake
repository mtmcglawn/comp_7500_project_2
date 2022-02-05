include(${BASE_DIR}/cmake/paths.cmake)
include(${CMAKE_DIR}/includes.cmake)
include(${CMAKE_DIR}/compiler.cmake)


#######################################
# Check that googletest is installed
#######################################
if(EXISTS ${GOOGLETEST_DIR}/CMakeLists.txt)
	set(ENABLE_TESTS TRUE)
endif()


#######################################
# Add External Dependencies
#######################################
if(NOT ${CMAKE_SOURCE_DIR} STREQUAL ${BASE_DIR})
	add_subdirectory(${EXTERNAL_DEPS_DIR} ${BUILD_DIR}/external)
endif()
