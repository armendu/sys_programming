/**
 * Copyright (C) 2003-2019 Dipl.Ing. Dr. techn. Idriz Smaili. All rights reserved
 * Siebenbuergerstrasse 16-26/26/17, A--1220 Wien, Austria. smaili.idriz@gmail.com
 *
 * @file  opt_proc.c
 *
 * @brief Implements functions for processing of the command line options
 * 
 * @author (IS) Dr.techn. Dipl.-Ing. Idriz Smaili (smaili.idriz@gmail.com)
 * @date   $Date: Fri Apr 19, 15:27:59 WEST 2019 $
 */

#include <stdio.h>
#include <unistd.h>

#include "opt_proc.h"

/* static char file_opt  = 0x0; */
/* static char outpu_opt = 0x0; */

/* static char * opt_arg1 = NULL; */

void usage (const char *app_name)
{
  printf ("\nexc1 - The first exercise in the sys prog lecture\n");
  printf ("\nSYNOPSIS\n");
  printf ("\texc1 [OPTION] ... arg1 arg2\n");
  printf ("\t -f arg,      The file option with an argument\n");
  printf ("\t -o,          The output option without an argument\n\n");
}
