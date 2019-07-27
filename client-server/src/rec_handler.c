/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  rec_handler.c
 *
 * @brief Implements the functionality for the record handler
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun21, Jul 21, 2019 23:42$
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "rec_handler.h"

int handle_recording(const char *f_name)
{
	/* Record child process */
	FILE *fp;
	if ((fp = fopen(f_name, "a+")) == NULL)
	{
		printf("\nError opening the file: '%s' [Error string: '%s']\n",
					 f_name, strerror(errno));
		return -1;
	}

	char *msg = NULL;
	while (1)
	{
		/*
			if (shm_read(shm_id, &shmptr, msg) == 0)
			{
				if (str_write(fp, msg) > 0)
				{
					printf("Record process: Wrote all content to file.\n");
				}
			}
			*/
	}
}
