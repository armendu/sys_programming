/**
 * Copyright (C) 2019 Bsc. Armend Ukehaxhaj. All rights reserved
 * Rr. Agim Ramadani pn., Prishtine, Kosovo. armendd.u@hotmail.com
 *
 * @file  opt_proc.c
 *
 * @brief Implements functions for processing of the command line options
 * 
 * @author (IS) Bsc. Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: 19 May 19, 22:48:08 WEST 2019 $
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>

#include "opt_proc.h"

/***************************************************************************/ /** 
 * @brief Returns the synopsis
 *
 * @param[in] input app_name
 ******************************************************************************/
void usage (const char *app_name)
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
	int  f_set	=  0 ;
  char mode 	= 'i';

  /* Check no. of arguments */
	if(argc > 4)
	{
		printf("Too many arguments provided. \n");
		return 0;
	}

	int opt;
	while ((opt = getopt(argc, argv, "f:ail")) != -1)
	{
		switch (opt)
		{
			case 'f':
        f_set = opt;
				*f_name = optarg;
				break;
			case 'i':
				mode = opt;
				break;
			case 'l':
			case 'a':
				mode = opt;
				break;
			default:
				return -1;
		}
	}
	
	if (f_set == 0)
	{
		printf("The option '-f' is mandatory\n");
		usage(argv[0]);
		return 0;
	}

  return mode;
}

void handle_sigint(int sig_num)
{
  signal(SIGINT, handle_sigint);
  fflush(stdout);
  printf("\nShutting down...\n");
  exit(-1);
}