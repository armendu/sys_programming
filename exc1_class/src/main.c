/**
 * Copyright (C) 2003-2019 Dipl.Ing. Dr. techn. Idriz Smaili. All rights reserved
 * Siebenbuergerstrasse 16-26/26/17, A--1220 Wien, Austria. smaili.idriz@gmail.com
 *
 * @file  main.c
 *
 * @brief Implements the main function
 * 
 * @author (IS) Dr.techn. Dipl.-Ing. Idriz Smaili (smaili.idriz@gmail.com)
 * @date   $Date: Fri Apr 19, 15:39:59 WEST 2019 $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>

#include "opt_proc.h"
#include "f_ser.h"
#include "interactive_prog.h"

int main (int argc, char *argv [])
{
  int opt;

  while((opt = getopt(argc, argv, "a:l:i")) != -1)
  {
    switch (opt)
    {
      case 'a':
        /* TODO: Add the bussiness logic. */
        printf("Write the name of the file: ");
        break;
      case 'i':
        printf("NOTE: You are now entering interactive mode!");
        printf("Please use one of the following commands: append, list, or quit:\n");
        
        enter_interactive_mode();
        break;
      default:
        return 0;
    }
  }
  
  return 0;
}
