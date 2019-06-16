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

#include "f_ser.h"
#include "opt_proc.h"
#include "s_manage.h"
#include "student.h"

int main(int argc, char *argv[])
{
	signal(SIGINT, handle_sigint);
	FILE *fp 			= NULL;
	char *f_name 	= NULL;
	
	char mode = set_mode(argc, argv, &f_name);
	
	if (mode == -1)
	{
		printf("An error occurred while setting the program mode.\n");
	}

	/* open a file */
	printf("\nThe file '%s' is opening ...\n", f_name);

	if ((fp = fopen(f_name, "a+")) == NULL)
	{
		printf("\nError opening the file: '%s' [Error string: '%s']",
					 f_name, strerror(errno));
		return -1;
	}

	student_t student;

	switch (mode)
	{
		case 'i':
			/* interactive mode */
			break;
		case 'a':
			get_student_info(&student);
			
			if (student_write(fp, student) == 0)
			{
				return -1;
			}
			printf("\nSuccessfully wrote the information to file.");
			break;
		case 'l':
				/* reset the file pointer at the file begin  */
				(void)fseek(fp, 0, SEEK_SET);

				if (student_read(fp) == 0)
				{
					return -1;
				}
			break;
		default:
			return -1;
			break;
	}

	printf("\nClosing now...\n");
  /* close the file */
  fclose (fp);

	return 0;
}