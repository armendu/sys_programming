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
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#include "opt_proc.h"
#include "cmd_modes.h"

int main(int argc, char *argv[])
{
	signal(SIGINT, handle_sigint);

	FILE *fp 			= NULL;
	char *f_name 	= NULL;
	
	char mode = set_mode(argc, argv, &f_name);
	
	if (mode == 0 || f_name == NULL)
	{
		printf("\nPlease provide a file using the '-f' option.\n");
		return -1;
	}

	/* open a file */
	printf("\nThe file '%s' is opening ...\n", f_name);

	if ((fp = fopen(f_name, "a+")) == NULL)
	{
		printf("\nError opening the file: '%s' [Error string: '%s']",
					 f_name, strerror(errno));
		return -1;
	}

	start_cmd_mode(fp, mode);

	printf("\nShutting down...\n");
  /* close the file */
  fclose (fp);

	return 0;
}