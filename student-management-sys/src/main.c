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
#include "s_manage.h"
#include "student.h"

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

	if ((fp = fopen(f_name, "w")) == NULL)
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
			if(get_student_info(&student) == 0)
			{
				if (student_write(fp, student) == 0)
				{
					printf("\nAn error occurred while writing information to file");
					return -1;
				}

				printf("\n%s", student.firstname);
				printf("\n%s", student.lastname);
				printf("\n%s", student.indexNumber);
				printf("\n%d", student.age);
				printf("\n%s", student.address);

				/* reset the file pointer at the file begin  */
				(void)fseek(fp, 0, SEEK_SET);

				if (student_read(fp) == 0)
				{
					printf("\nAn error occurred while reading information from file");
					return -1;
				}

				int no_students = 0; /*@null@*/

				printf("\nThe length is being written ... ");

				no_students = get_no_bytes(fp);

				printf(" done [%d]", no_students);
				printf("Error occurred while writing file.\n");
			}
			break;
		case 'l':
			/* list all files */
			break;
		default:
			return -1;
			break;
	}

  /* reset the file pointer at the file begin  */
  (void) fseek (fp, 0, SEEK_SET);

  /* close the file */
  fclose (fp);

	return 0;
}