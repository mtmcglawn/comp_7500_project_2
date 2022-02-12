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
 *
 *
 * USE
 *
 * To run the program you can either:
 * 1: $ ./build/pwordcount/pwordcount <file_name>
 * 2: $ cd ./build/pwordcount/ && ./pwordcount <file_name>
 */

int child(int  to_parent_pipe[],
          int  from_parent_pipe[],
          char write_msg[],
          char read_msg[])
{
  int words = receiveDataFromParent(from_parent_pipe,
                                    read_msg);
  fprintf(stdout, "Process 2 is counting words now...\n");
  sendDataToParent(to_parent_pipe,
                   write_msg,
                   words);
  return words;
}


int receiveDataFromParent(int  from_pipe[],
                           char read_msg[])
{
  int parent_message_size = 0;
  close(from_pipe[WRITE_END]);
  int word_count = 0;
  while ((parent_message_size = read(from_pipe[READ_END], read_msg, MAX_BUFFER_SIZE)) > 0)
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
          word_count++;
        }
        isLetter = true;
      }
    }
  }
  close(from_pipe[READ_END]);
  fprintf(stdout, "Process 2 finishes receiving data from Process 1...\n");
  return word_count;
}


char* sendDataToParent(int  to_pipe[],
                      char write_msg[],
                      int  word_count)
{
  char word_count_as_string[MAX_BUFFER_SIZE];
  sprintf(word_count_as_string, "%d", word_count);
  close(to_pipe[READ_END]);
  fprintf(stdout, "Process 2 is sending the result back to Process 1...\n");
  for (int child_send_buffer_index = 0; child_send_buffer_index < strlen(word_count_as_string); child_send_buffer_index++)
  {
    write_msg[child_send_buffer_index] = word_count_as_string[child_send_buffer_index];
  }
  write(to_pipe[WRITE_END], write_msg, strlen(write_msg) + 1);
  close(to_pipe[WRITE_END]);
  char *return_string = word_count_as_string;
  return return_string;
}
