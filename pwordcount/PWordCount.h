#ifndef _PWORD_COUNT_H
#define _PWORD_COUNT_H

#include <stdio.h>
#include <string.h>

#include "Config.h"


void PWordCount();
char* getString();

#ifdef _PWORD_COUNT_C
static char output[150];
#endif

#endif
