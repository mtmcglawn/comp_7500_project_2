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
  if (argc == 2)
  {
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file)
    {
      fprintf(stderr, "Can not open file %s\n", argv[1]);
      ret_val = 1;
    }
    else
    {
      ret_val = pipelining(argv[1]);
    }
  }
  else
  {
    ret_val = printBadInputs();
  }
  return ret_val;
}


int printBadInputs()
{
    fprintf(stderr, "Please enter a file name.\n");
    fprintf(stderr, "Usage: ./pwordcount <file_name>\n");
    return 1;
}
