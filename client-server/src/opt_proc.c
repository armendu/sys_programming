/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  opt_proc.c
 *
 * @brief 
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: 21, Jul 21, 2019 23:40$
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>

#include "opt_proc.h"


/***************************************************************************/ /**
 * @brief Returns the synopsis
 ******************************************************************************/
void usage()
{
  printf ("\nSYNOPSIS\n");
  printf ("\nstudent_management_sys [OPTION] ... \n");
  printf ("\t -f arg,      (mandatory) the file name\n");
  printf ("\t -a,          (optional) append a string to the file\n");
  printf ("\t -i,          (optional) start the interactive mode\n");
  printf ("\t -l,          (optional) list all strings stored in the file\n");
}

/***************************************************************************/ /**
 * @brief Returns the number of characters in a given string
 *
 * @param[in]     argc    - no. of arguments
 * @param[in]     argv    - argument value
 * @param[in,out] f_name  - the file name
 *
 * @retval char respresenting the mode
 ******************************************************************************/
char set_mode(int argc, char **argv, char** f_name)
{
  return 0;
}

/***************************************************************************/ /**
 * @brief Called when user presses CTRL+C and terminates any open operation
 *
 * @param[in] sig_num - the signal
 ******************************************************************************/
void handle_sigint(int sig_num)
{
  signal(SIGINT, handle_sigint);
  /* TODO: IMPROVE */
  printf("\nShutting down...\n");
  exit(-1);
}