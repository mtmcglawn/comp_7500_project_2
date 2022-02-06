cmake_minimum_required(VERSION 3.21)

set(CURRENT_DIR PWORD_COUNT)
set(CLASS_NAME PWordCount)
set(DRIVER_NAME ${CLASS_NAME}Driver)
set(EXE_NAME pwordcount)


if (NOT ${CMAKE_SOURCE_DIR})
	#######################################
	# Project setup
	#######################################
	set(PROJECT_NAME ${EXE_NAME})
	project(${PROJECT_NAME})
	# After project(..) is called, the following variables are availble:
	# * PROJECT_SOURCE_DIR - Top level source directory for the project
	# * PROJECT_BINARY_DIR - Full path to build directory for project
	
	find_package(Git QUIET)

	execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse --show-toplevel
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		OUTPUT_VARIABLE BASE_DIR
		OUTPUT_STRIP_TRAILING_WHITESPACE
		)
	
	include(${BASE_DIR}/cmake/cmake_includes.cmake)

endif()

#######################################
# Define include directories
#######################################
include_directories(${COMMON_INCLUDES} ${${CURRENT_DIR}_INC}
	#Add additional required .h files here
	)


#######################################
# Source files
#######################################
file(GLOB SRC_FILES ${${CURRENT_DIR}_DIR}/*.c)
#set(SRC_FILES ${${CURRENT_DIR}_DIR}/${CLASS_NAME}.c
	#Add additional required .c files here
	#)

#######################################
# Remove the driver to create a library
#######################################
list(REMOVE_ITEM SRC_FILES ${${CURRENT_DIR}_DIR}/${DRIVER_NAME}.c)
# Key idea: SEPARATE OUT your main() function into its own file so it can be its
# own executable. Separating out main() means you can add this library to be
# used elsewhere (e.g., linking to the test executable).


#######################################
# Compile source files into a library
#######################################
add_library(${CLASS_NAME}_lib ${SRC_FILES})


#######################################
# Main is separate (e.g., library client)
#######################################
add_executable(${EXE_NAME} ${${CURRENT_DIR}_DIR}/${DRIVER_NAME}.c)


#######################################
# linking Main against the library
#######################################
target_link_libraries(${EXE_NAME} ${CLASS_NAME}_lib)


if(ENABLE_TESTS)
	#######################################
	# Testing
	#######################################
	# Options. Turn on with 'cmake -Dmyvarname=ON'.
	# option(BUILD_TESTS "Build all tests." ON) # Makes boolean 'test' available.
	enable_testing()
	
	# Include the gtest library. gtest_SOURCE_DIR is available due to
	# including the googletest external directory.
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
	
	
	#######################################
	# Test files
	#######################################
	# file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
	set(TEST_SRC_FILES
		${${CURRENT_DIR}_DIR}/${CLASS_NAME}_test.cpp
		)
	
	
	#######################################
	# Unit Tests
	#######################################
	add_executable(${EXE_NAME}_test.exe ${TEST_SRC_FILES})
	
	
	#######################################
	# Standard linking to gtest stuff
	#######################################
	target_link_libraries(${EXE_NAME}_test.exe gtest gtest_main)
	
	
	#######################################
	# Extra linking for the project.
	#######################################
	target_link_libraries(${EXE_NAME}_test.exe ${CLASS_NAME}_lib)
	
	
	# This is so you can do 'make test' to see all your tests run, instead of
	# manually running the executable *_tests.exe to see those specific tests.
	add_test(${EXE_NAME}Tests ${EXE_NAME}_test.exe)
endif()
