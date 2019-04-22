/**
 * Copyright (C) 2003-2019 Dipl.Ing. Dr. techn. Idriz Smaili. All rights reserved
 * Siebenbuergerstrasse 16-26/26/17, A--1220 Wien, Austria. smaili.idriz@gmail.com
 *
 * @file  interactive_prog.c
 *
 * @brief Implements a function to count the length of a string
 * 
 * @author (IS) Dr.techn. Dipl.-Ing. Idriz Smaili (smaili.idriz@gmail.com)
 * @date   $Date: Fri Apr 19, 15:27:59 WEST 2019 $
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "interactive_prog.h"
#include "f_str.h"

#define _POSIX_SOURCE

int enter_interactive_mode (const char *input)
{
  char* user_text = NULL;
  char* file_name = NULL;
  FILE *fp        = NULL;

  if (strcmp(input, INTERACTIVE_QUIT) == 0)
  {
    /* Use terminate with a SIGNAL */
    terminate(1);
  }
  else if (strcmp(input, INTERACTIVE_APPEND) == 0)
  {
    printf("Please type the name of the file: ");
    scanf("%s", file_name);
    printf("Please type the text that you want to append: ");
    scanf("%s", user_text);

    if((fp = fopen(file_name, "a+")) == NULL)
    {
      printf("File couldn't be opened!\n");
      return -1;
    }

    printf("The string %s is being written to the file!\n", user_text);

    if (str_write(fp, user_text) == 0)
    {
      printf("Couldn't write on the file!\n");
      return -1;
    }

    printf("Done!");
  }
  else if (strcmp(input, INTERACTIVE_LIST) == 0)
  {
    printf("Please type the name of the file: ");
    scanf("%s", file_name);
    
    if((fp = fopen(file_name, "a+")) == NULL)
    {
      printf("File couldn't be opened!\n");
      return -1;
    }

    (void) fseek(fp, 0, SEEK_SET);

    printf("We are reading from the file now\n");

    char* read_string = NULL;

    if(str_read(fp, &read_string) == 0)
    {
      free(read_string);

      printf("Couldn't read from the file!\n");
      return -1;
    }
  }
  else
  {
    printf("Invalid command, please type another");
  }

  free(user_text);
  free(file_name);
  free(fp);
  return 0;
}

void terminate(int interrupt)
{
  printf("It was very nice to meet you, bye!");
  exit(0);
}