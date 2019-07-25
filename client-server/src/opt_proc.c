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

#define ERROR_CODE -1 

#include "opt_proc.h"

/***************************************************************************/ /**
 * @brief Returns the synopsis for server
 ******************************************************************************/
void usage_server()
{
  printf ("\nSYNOPSIS\n");
  printf ("\nstudent_management_sys [OPTION] ... \n");
  printf ("\t -f arg,      (mandatory) the log file name\n");
}

/***************************************************************************/ /**
 * @brief Returns the synopsis for client
 ******************************************************************************/
void usage_client()
{
  printf ("\nSYNOPSIS\n");
  printf ("\nstudent_management_sys [OPTION] ... \n");
  printf ("\t -f arg,      (mandatory) the file name\n");
  printf ("\t -t arg,      (mandatory) seconds\n");
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
int get_client_args(int argc, char **argv, char** f_name)
{
  int f_set 	= 0;
	int s_set   = 0;
  int n_secs 	= 0;

  /* Check no. of arguments */
	if(argc < 5)
	{
		printf("Too few arguments provided. \n");
		usage_client();
		return ERROR_CODE;
	}

	int opt;
	while ((opt = getopt(argc, argv, "f:t:")) != -1)
	{
		switch (opt)
		{
			case 'f':
        f_set = opt;
				*f_name = optarg;
				break;
			case 't':
				s_set = opt;
				n_secs = atoi(optarg);
				break;
			default:
				usage_client();
				return ERROR_CODE;
		}
	}
	
	if (f_set == 0)
	{
		printf("The option '-f' is mandatory\n");
		usage_client();
		return ERROR_CODE;
	}

	if (s_set == 0)
	{
		printf("The option '-s' is mandatory\n");
		usage_client();
		return ERROR_CODE;
	}

  return n_secs;
}

int get_server_args(int argc, char **argv, char** f_name)
{
  int f_set = 0;

  /* Check no. of arguments */
	if(argc < 3)
	{
		printf("Too few arguments provided. \n");
		usage_server();
		return ERROR_CODE;
	}

	int opt;
	while ((opt = getopt(argc, argv, "f:")) != -1)
	{
		switch (opt)
		{
			case 'f':
        f_set = opt;
				*f_name = optarg;
				break;
			default:
				usage_server();
				return ERROR_CODE;
		}
	}
	
	if (f_set == 0)
	{
		printf("The option '-f' is mandatory\n");
		usage_server();
		return ERROR_CODE;
	}

  return 0;
}