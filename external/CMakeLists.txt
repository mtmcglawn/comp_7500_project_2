cmake_minimum_required(VERSION 3.22)
include_guard(GLOBAL)

# google test is a git submodule for the project, and it is also cmake-based
if(ENABLE_TESTS)
    add_subdirectory(googletest)
endif()
