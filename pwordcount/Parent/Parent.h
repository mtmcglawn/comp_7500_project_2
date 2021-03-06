#ifndef _PARENT_H
#define _PARENT_H

#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "Config.h"


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


int parent(char *file_name,
           int  to_child_pipe[],
           int  from_child_pipe[],
           char write_msg[],
           char read_msg[]);


void sendDataToChild(FILE *file,
                     int  to_pipe[],
                     char write_msg[]);


void readDataFromChild(int  from_pipe[],
                       char read_msg[]);


#endif
