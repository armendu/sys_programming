/**
 * Copyright (C) 2019 Bsc. Armend Ukehaxhaj. All rights reserved
 * Rr. Agim Ramadani pn., Prishtine, Kosovo. armendd.u@hotmail.com
 *
 * @file  opt_proc.c
 *
 * @brief Implements functions for processing of the command line options
 * 
 * @author (IS) Bsc. Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: 19 May 19, 18:20:52 WEST 2019 $
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>

#include "opt_proc.h"

void usage (const char *app_name)
{
  printf ("\nSYNOPSIS\n");
  printf ("\nstudent_management_sys [OPTION] ... \n");
  printf ("\t -f arg,      (mandatory) the file name\n");
  printf ("\t -a,          (optional) append a string to the file\n");
  printf ("\t -i,          (optional) start the interactive mode\n");
  printf ("\t -l,          (optional) list all strings stored in the file\n");
}

char set_mode(int argc, char **argv, char** f_name)
{
	int   f     = -1;
  char  mode  = 'i';

  /* Check no. of arguments */
	if(argc > 4)
	{
		printf("Too many arguments provided. \n");
		return -1;
	}

	int opt;
	while ((opt = getopt(argc, argv, "f:ail")) != -1)
	{
		switch (opt)
		{
			case 'f':
        f = (int)atol(optarg);
				*f_name = optarg;
				printf("\nGot f with filename: %s\n", optarg);
				break;
			case 'i':
			case 'l':
			case 'a':
				mode = opt;
				break;
			default:
				usage(argv[0]);
				return -1;
		}
	}

	if (f == -1)
	{
		printf("The option '-f' is mandatory\n");
		return -1;
	}

  return mode;
}

void handle_sigint(int sig_num)
{
  signal(SIGINT, handle_sigint);
  fflush(stdout);
  printf("\nClosing... \n");
  exit(0);
}