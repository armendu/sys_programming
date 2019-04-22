/**
 * Copyright (C) 2003-2019 Dipl.Ing. Dr. techn. Idriz Smaili. All rights reserved
 * Siebenbuergerstrasse 16-26/26/17, A--1220 Wien, Austria. smaili.idriz@gmail.com
 *
 * @file  string_compare.c
 *
 * @brief Implements a function to count the length of a string
 * 
 * @author (IS) Dr.techn. Dipl.-Ing. Idriz Smaili (smaili.idriz@gmail.com)
 * @date   $Date: Fri Apr 19, 15:27:59 WEST 2019 $
 */

#include <stdio.h>
#include <unistd.h>

#include "string_compare.h"

int find_length (const char *input)
{
  int length = 0;
  while(*input != '\0' && input++) {
    length++;
  }
  return length;
}

void copy_string (char *destination, const char *source)
{
  while(*source != '\0')
  {
    *destination++ = *source++;
  }
}
