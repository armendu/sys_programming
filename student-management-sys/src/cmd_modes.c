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
#include <string.h>

#define APPEND "append"
#define LIST   "list"
#define QUIT   "quit"

void enter_interactive_mode (FILE *fp);
void enter_append_mode      (FILE *fp);
void enter_listing_mode     (FILE *fp);

#include "cmd_modes.h"
#include "student.h"
#include "s_manage.h"
#include "f_ser.h"

void start_cmd_mode(FILE *fp, char mode)
{
  switch (mode)
	{
		case 'i':
			enter_interactive_mode(fp);
			break;
		case 'a':
			enter_append_mode(fp);
			break;
		case 'l':
			enter_listing_mode(fp);
			break;
		default:
			break;
	}
}

void enter_interactive_mode(FILE *fp)
{
  char input[50];
  while (1)
  {
    printf("\nPlease write one of the commands: append, list, or quit: ");
    if (fgets(input, sizeof(input), stdin) != NULL)
    {
      int s_len = str_len(input);
      input[s_len - 1] = '\0';

      if (strcmp(APPEND, input) == 0)
      {
        enter_append_mode(fp);
      } 
      else if (strcmp(QUIT ,input) == 0)
      {
        printf("\nShutting down... \n");
        exit(0);
      } 
      else if (strcmp(LIST, input) == 0)
      {
        enter_listing_mode(fp);
      }
      else
      {
        printf("\nPlease type a valid command.");
      }      
    }
    else
    {
      printf("\nPlease type a valid command.");
    }    
  }
}

void enter_append_mode(FILE *fp)
{
	student_t student;
  get_student_info(&student);
  
  if (student_write(fp, student) == 0)
  {
    return;
  }
  printf("\nSuccessfully wrote the information to file.");
}

void enter_listing_mode(FILE *fp)
{
  /* reset the file pointer at the file begin  */
  (void)fseek(fp, 0, SEEK_SET);

  printf("\nReading information from the file now...");
  if (student_read(fp) == 0)
  {
    return;
  }
}