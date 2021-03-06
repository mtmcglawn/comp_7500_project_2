include_guard(GLOBAL)

#######################################
# Set up the directory locations
#######################################
set(TOP_LEVEL_DIR     ${BASE_DIR})


set(BUILD_DIR         ${CMAKE_SOURCE_DIR}/build)

set(CMAKE_DIR         ${TOP_LEVEL_DIR}/cmake)
set(EXTERNAL_DEPS_DIR ${TOP_LEVEL_DIR}/external)
set(PWORD_COUNT_DIR   ${TOP_LEVEL_DIR}/pwordcount)

set(GOOGLETEST_DIR    ${EXTERNAL_DEPS_DIR}/googletest)

set(PARENT_DIR        ${PWORD_COUNT_DIR}/Parent)
set(CHILD_DIR         ${PWORD_COUNT_DIR}/Child)
set(PIPELINING_DIR    ${PWORD_COUNT_DIR}/Pipelining)
