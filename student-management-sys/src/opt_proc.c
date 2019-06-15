/**
 * Copyright (C) 2019 Bsc. Armend Ukehaxhaj. All rights reserved
 * Rr. Agim Ramadani pn., Prishtine, Kosovo. armendd.u@hotmail.com
 *
 * @file  main.c
 *
 * @brief Implements the main function
 * 
 * @author (IS) Bsc. Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: 19 May 19, 18:20:52 WEST 2019 $
 */

#include <stdio.h>
#include <unistd.h>

#include "opt_proc.h"

/* static char file_opt  = 0x0; */
/* static char outpu_opt = 0x0; */

/* static char * opt_arg1 = NULL; */

void usage (const char *app_name)
{
  printf ("\nSYNOPSIS\n");
  printf ("\nstudent_management_sys [OPTION] ... \n");
  printf ("\t -f arg,      (mandatory) the file name\n");
  printf ("\t -a,          (optional) append a string to the file\n");
  printf ("\t -i,          (optional) start the interactive mode\n");
  printf ("\t -l,          (optional) list all strings stored in the file\n");
}
