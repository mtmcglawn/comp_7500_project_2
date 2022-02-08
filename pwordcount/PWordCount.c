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
      char *file_name =argv[1];
      FILE *input_file = fopen(file_name, "r");
      fprintf(stdout, "Process 1 is reading file \"%s\" now...\n", file_name);
      if (!input_file)
      {
        fprintf(stderr, "Can not open file\n");
        return 1;
      }
      else
      {
        int parent_send_buffer_index = 0;
        fprintf(stdout, "Process 1 starts sending data to Process 2...\n");
        close(parent_to_child_pipe[READ_END]);
        while ((parent_write_msg[parent_send_buffer_index] = fgetc(input_file)) != EOF)
        {
          if (parent_send_buffer_index == MAX_BUFFER_SIZE - 2)
          {
            write(parent_to_child_pipe[WRITE_END], parent_write_msg, strlen(parent_write_msg) + 1);
            memset(parent_write_msg, 0, sizeof parent_write_msg);
            parent_send_buffer_index = -1;
          }
          parent_send_buffer_index++;
        }
        parent_write_msg[parent_send_buffer_index] = '\0';
        write(parent_to_child_pipe[WRITE_END], parent_write_msg, parent_send_buffer_index + 1);
        close(parent_to_child_pipe[WRITE_END]);
        fclose(input_file);
        wait(NULL);
        close(child_to_parent_pipe[WRITE_END]);
        int child_message_size = 0;
        while ((child_message_size = read(child_to_parent_pipe[READ_END], child_read_msg, MAX_BUFFER_SIZE)) > 0)
        {
          fprintf(stdout, "Process 1: The total number of words is %s\n", child_read_msg);
        }
        close(child_to_parent_pipe[READ_END]);
      }
    }
    else
    {
      int parent_message_size = 0;
      close(parent_to_child_pipe[WRITE_END]);
      int words = 0;
      while ((parent_message_size = read(parent_to_child_pipe[READ_END], child_read_msg, MAX_BUFFER_SIZE)) > 0)
      {
        bool isLetter = false;
        for (int child_buffer_index = 0; child_buffer_index < MAX_BUFFER_SIZE; child_buffer_index++)
        {
          if (child_read_msg[child_buffer_index] == ' ')
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
      fprintf(stdout, "%d\n", words);
      close(parent_to_child_pipe[READ_END]);
      fprintf(stdout, "Process 2 finishes receiving data from Process 1...\n");
      fprintf(stdout, "Process 2 is counting words now...\n");
      char words_as_string[MAX_BUFFER_SIZE];
      sprintf(words_as_string, "%d", words);
      close(child_to_parent_pipe[READ_END]);
      fprintf(stdout, "Process 2 is sending the result back to Process 1...\n");
      for (int child_send_buffer_index = 0; child_send_buffer_index < strlen(words_as_string); child_send_buffer_index++)
      {
        child_write_msg[child_send_buffer_index] = words_as_string[child_send_buffer_index];
      }
      write(child_to_parent_pipe[WRITE_END], child_write_msg, strlen(child_write_msg) + 1);
      close(child_to_parent_pipe[WRITE_END]);
    }
  }
  else
  {
    fprintf(stderr, "Usage: ./pwordcount <file_name>\n");
    return 1;
  }
  return 0;
}
