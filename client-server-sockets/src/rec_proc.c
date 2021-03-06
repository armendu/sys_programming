/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  rec_proc.c
 *
 * @brief Implements the functionality for the record process
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun21, Jul 21, 2019 23:42$
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <semaphore.h>

#include "rec_proc.h"
#include "f_ser.h"
#include "sh_mem.h"

void signal_handler(int signum);
FILE *fp;

/***************************************************************************/ /**
 * @brief Writes data read from the shared memory to a file
 *
 * @param[in] 		f_name  - the file name
 * @param[in,out]	shm_ptr - The shared memory pointer
 *
 * @retval -1 - If an error occurred
 * @retval  0 - If the writing was successful
 ******************************************************************************/
int handle_rec(const char *f_name, shm_elm_t *shm_ptr, sem_t *reader_sem)
{
	signal(SIGINT, signal_handler);

	/* Record child process */
	if ((fp = fopen(f_name, "a+")) == NULL)
	{
		printf("\nError opening the file: '%s' [Error string: '%s']\n",
					 f_name, strerror(errno));
		return -1;
	}

	while (1)
	{
		if (shm_ptr->state == SHM_FULL)
		{
			if (str_write(fp, shm_ptr->msg) > 0)
			{
				printf("Record process: Wrote content to file.\n");
			}
			fflush(fp);
			shm_ptr->state = SHM_EMPTY;
		}
	}

	return 0;
}

/***************************************************************************/ /** 
 * @brief Handles the CTRL+C signal.
 *
 * @param[in] signum - The signal number
 ******************************************************************************/
void signal_handler(int signum)
{
	fflush(stdout);
	free(fp);
}