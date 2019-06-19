/**
 * Copyright (C) 2019 Bsc. Armend Ukehaxhaj. All rights reserved
 * Rr. Agim Ramadani pn., Prishtine, Kosovo. armendd.u@hotmail.com
 *
 * @file  cmd_modes.c
 *
 * @brief Implements functions for the command modes that the program
 * uses
 * 
 * @author (IS) Bsc. Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: 19 May 19, 18:21:05 WEST 2019 $
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

/***************************************************************************/ /** 
 * @brief Starts one of the command line modes
 *
 * Interactive, where both append and list can be called, and
 * Non-Interactive, where the mode is chosen beforehand.
 *
 * @param[in,out] fp - file pointer
 * @param[in] mode - the mode speicified as an argument
 ******************************************************************************/
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

/***************************************************************************/ /** 
 * @brief Starts the interactive mode
 *
 * A user can write his command (append, list, or quit) and the
 * program executes the next action based on that input
 *
 * @param[in,out] fp - file pointer
 ******************************************************************************/
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

/***************************************************************************/ /** 
 * @brief Starts the append mode
 *
 * A subset of the non-interactive mode where the user is
 * asked to write the information of the next student that
 * is going to be registered.
 *
 * @param[in,out] fp - file pointer
 ******************************************************************************/
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

/***************************************************************************/ /** 
 * @brief Starts the lisiting mode
 *
 * A subset of the non-interactive mode where the program
 * shows the user all the registered students 
 *
 * @param[in,out] fp - file pointer
 ******************************************************************************/
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