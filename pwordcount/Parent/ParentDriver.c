#include "Parent.h"


/*
 * COMP 7500/001
 * Matthew Tyler McGlawn
 * Auburn University
 *
 * COMPILE
 *
 * 2 ways:
 * 1: $ ./build.sh
 * 2: $ mkdir build && cd build && cmake .. && cmake --build .
 *
 * Either way may be used
 * 
 *
 * TESTS
 *
 * To run tests in any directory with source code:
 * - googletest must be located in repository - run
 *
 *   `git submodule update --init`
 *
 *    to clone googletest into appropriate location
 *
 * First build, then either:
 * 1. $ cd build && ctest
 * 2. $ ./build.sh test
 */


int main(int argc, char *argv[]) {
  char *file_name = "Parent.h";
  int to_child_pipe[2];
  int from_child_pipe[2];
  char write_msg[MAX_BUFFER_SIZE];
  char read_msg[MAX_BUFFER_SIZE];
  if (pipe(to_child_pipe) == -1 || pipe(from_child_pipe) == -1)
  {
    fprintf(stderr, "Pipe creation failed");
    return 1;
  }
  return parent(file_name,
      to_child_pipe,
      from_child_pipe,
      write_msg,
      read_msg);
}
