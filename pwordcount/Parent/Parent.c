#define _PARENT_C
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


int parent(char *file_name,
           int  to_child_pipe[],
           int  from_child_pipe[],
           char write_msg[],
           char read_msg[])
{
  FILE *input_file = fopen(file_name, "r");
  fprintf(stdout, "Process 1 is reading file \"%s\" now...\n", file_name);
  if (!input_file)
  {
    fprintf(stderr, "Can not open file\n");
    return 1;
  }
  else
  {
    sendDataToChild(input_file,
                    to_child_pipe,
                    write_msg);
    fclose(input_file);
    wait(NULL);
    readDataFromChild(from_child_pipe,
                      read_msg);
    return 0;
  }
}


void sendDataToChild(FILE *file,
                     int  to_pipe[],
                     char write_msg[])
{
  int parent_send_buffer_index = 0;
  fprintf(stdout, "Process 1 starts sending data to Process 2...\n");
  close(to_pipe[READ_END]);
  while ((write_msg[parent_send_buffer_index] = fgetc(file)) != EOF)
  {
    if (parent_send_buffer_index == MAX_BUFFER_SIZE - 2)
    {
      write(to_pipe[WRITE_END], write_msg, strlen(write_msg) + 1);
      memset(write_msg, 0, sizeof &write_msg);
      parent_send_buffer_index = -1;
    }
    parent_send_buffer_index++;
  }
  write_msg[parent_send_buffer_index] = '\0';
  write(to_pipe[WRITE_END], write_msg, parent_send_buffer_index + 1);
  close(to_pipe[WRITE_END]);
}


void readDataFromChild(int  from_pipe[],
                       char read_msg[])
{
  close(from_pipe[WRITE_END]);
  int child_message_size = 0;
  while ((child_message_size = read(from_pipe[READ_END], read_msg, MAX_BUFFER_SIZE)) > 0)
  {
    fprintf(stdout, "Process 1: The total number of words is %s\n", read_msg);
  }
  close(from_pipe[READ_END]);
}
