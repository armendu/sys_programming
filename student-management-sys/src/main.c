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

#include "f_ser.h"
#include "opt_proc.h"
#include "f_append.h"

int main(int argc, char *argv[])
{
	FILE *fp 			= NULL;
	char *f_name 	= NULL;
	
	char mode = get_file_name(argc, argv, &f_name);
	
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

	switch (mode)
	{
		case 'i':
			/* interactive mode */
			break;
		case 'a':
			if(append_student(&fp) == -1)
			{
				printf("Error occurred with writing file\n");
			}
			break;
		case 'l':
			/* list all files */
			break;
		default:
			return -1;
			break;
	}

	char *str1 = "Programimi Sistemor";

	printf("\nThe first string '%s' is being written ... ", str1);
	if (str_write(fp, str1) == 0)
	{
		return -1;
	}
	printf(" done");

	char *str2 = "user";

  printf ("\nThe second string '%s' is being written ... ", str2);
  if (str_write (fp, str2) == 0)
	{
		return -1;
	}
  printf (" done");

  /* reset the file pointer at the file begin  */
  (void) fseek (fp, 0, SEEK_SET);

  /* close the file */
  fclose (fp);

	return 0;
}