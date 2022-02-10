#define _CHILD_C
#include "Child.h"


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

int child(int  to_parent_pipe[],
          int  from_parent_pipe[],
          char write_msg[],
          char read_msg[])
{
  int parent_message_size = 0;
  close(from_parent_pipe[WRITE_END]);
  int words = 0;
  while ((parent_message_size = read(from_parent_pipe[READ_END], read_msg, MAX_BUFFER_SIZE)) > 0)
  {
    bool isLetter = false;
    for (int child_buffer_index = 0; child_buffer_index < MAX_BUFFER_SIZE; child_buffer_index++)
    {
      if (read_msg[child_buffer_index] == ' ')
      {
        isLetter = false;
      }
      else
      {
        if (!isLetter)
        {
          words++;
        }
        isLetter = true;
      }
    }
  }
  close(from_parent_pipe[READ_END]);
  fprintf(stdout, "Process 2 finishes receiving data from Process 1...\n");
  fprintf(stdout, "Process 2 is counting words now...\n");
  char words_as_string[MAX_BUFFER_SIZE];
  sprintf(words_as_string, "%d", words);
  close(to_parent_pipe[READ_END]);
  fprintf(stdout, "Process 2 is sending the result back to Process 1...\n");
  for (int child_send_buffer_index = 0; child_send_buffer_index < strlen(words_as_string); child_send_buffer_index++)
  {
    write_msg[child_send_buffer_index] = words_as_string[child_send_buffer_index];
  }
  write(to_parent_pipe[WRITE_END], write_msg, strlen(write_msg) + 1);
  close(to_parent_pipe[WRITE_END]);
}
