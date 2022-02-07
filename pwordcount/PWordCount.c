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
  if (argc == 1)
  {
    fprintf(stderr, "Please enter a file name.\n");
    fprintf(stderr, "Usage: ./pwordcount <file_name>\n");
    return 1;
  }
  else if (argc == 2)
  {
    char write_msg[MAX_BUFFER_SIZE];
    char read_msg[MAX_BUFFER_SIZE];
    pid_t pid;
    int pipe_descriptor[2];
    if  (pipe(pipe_descriptor) == -1)
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
      char *file_name =argv[1];
      FILE *input_file = fopen(file_name, "r");
      if (!input_file)
      {
        fprintf(stderr, "Can not open file\n");
        return 1;
      }
      else
      {
        int buffer_index = 0;
        close(pipe_descriptor[READ_END]);
        while ((write_msg[buffer_index] = fgetc(input_file)) != EOF)
        {
          if (buffer_index == MAX_BUFFER_SIZE - 2)
          {
            write(pipe_descriptor[WRITE_END], write_msg, strlen(write_msg) + 1);
            memset(write_msg, 0, sizeof write_msg);
            buffer_index = -1;
          }
          buffer_index++;
        }
        write_msg[buffer_index] = '\0';
        write(pipe_descriptor[WRITE_END], write_msg, buffer_index + 1);
        close(pipe_descriptor[WRITE_END]);
        fclose(input_file);
      }
    }
    else
    {
      int byte_size = 0;
      close(pipe_descriptor[WRITE_END]);
      while ((byte_size = read(pipe_descriptor[READ_END], read_msg, MAX_BUFFER_SIZE)) > 0)
      {
        fprintf(stdout, read_msg);
      }
      close(pipe_descriptor[READ_END]);
    }
  }
  else
  {
    fprintf(stderr, "Usage: ./pwordcount <file_name>\n");
    return 1;
  }
  return 0;
}
