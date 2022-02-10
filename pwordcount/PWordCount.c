#define _PWORD_COUNT_C
#include "PWordCount.h"


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


int pWordCount(int argc, char *argv[])
{
  int ret_val = 0;
  if (argc == 1)
  {
    fprintf(stderr, "Please enter a file name.\n");
    fprintf(stderr, "Usage: ./pwordcount <file_name>\n");
    return 1;
  }
  else if (argc == 2)
  {
    char parent_write_msg[MAX_BUFFER_SIZE];
    char child_write_msg[MAX_BUFFER_SIZE];
    char child_read_msg[MAX_BUFFER_SIZE];
    char parent_read_msg[MAX_BUFFER_SIZE];
    pid_t pid;
    int parent_to_child_pipe[2];
    int child_to_parent_pipe[2];
    if (pipe(parent_to_child_pipe) == -1 || pipe(child_to_parent_pipe) == -1)
    {
      fprintf(stderr, "Pipe creation failed");
      return 1;
    }
    pid = fork();
    if (pid < 0)
    {
      fprintf(stderr, "Fork creation failed");
      return 1;
    }
    if (pid > 0)
    {
      ret_val = parent(argv[1],
                       parent_to_child_pipe,
                       child_to_parent_pipe,
                       parent_write_msg,
                       child_read_msg);
    }
    else
    {
      ret_val = child(child_to_parent_pipe,
                      child_to_parent_pipe,
                      child_write_msg,
                      parent_read_msg);
    }
  }
  else
  {
    fprintf(stderr, "Usage: ./pwordcount <file_name>\n");
    return 1;
  }
  return ret_val;
}
