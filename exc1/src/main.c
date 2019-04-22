/**
 * Copyright (C) 2003-2019 Dipl.Ing. Dr. techn. Idriz Smaili. All rights reserved
 * Siebenbuergerstrasse 16-26/26/17, A--1220 Wien, Austria. smaili.idriz@gmail.com
 *
 * @file  main.c
 *
 * @brief Implements the main function
 * 
 * @author (IS) Dr.techn. Dipl.-Ing. Idriz Smaili (smaili.idriz@gmail.com)
 * @date   $Date: Fri Apr 19, 15:39:59 WEST 2019 $
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "opt_proc.h"
#include "string_compare.h"
#include "string.h"
#include "interactive_prog.h"

int main (int argc, char *argv [])
{
  /**
  usage  (argv [0]);
  */

  /** // Function to call the find_length function
  char s[1000];
  printf("Please enter a string: ");
  scanf("%s", s);

  int result = find_length(s);
  printf("The length of input string '%s' is %d \n", s, result);
  */
  
  /**
  const char* source = "TestSource";
  char *destination = malloc(strlen(source) + 1);

  copy_string(destination, source);

  printf("The destination string is %s \n", destination);
  */
  

  /**
   * Detyra ka me qene qe me mujt me rujt te dhenat e studenteve ne nje file
   * Konventat qe ne i ndjekim jane:
   * Cdo e dhene ka numrin e bajtave ne fillim
   * Cdo objekt studenti duhet te kete madhesine para vetes (not confirmed)
   * Ne fillim te fajllit shenohet se sa objekte jane
  */
  
  int opt;
  char* input = NULL;
  while((opt = getopt(argc, argv, "ali:")) != -1)
  {
    switch (opt)
    {
      case 'a':
        printf("Write the name of the file: ");
        break;
      case 'i':
        printf("You are entering interactive mode, please type your next command:");
        while (1)
        {
          scanf("%s", input);
          enter_interactive_mode(input);
        }
        
      default:
        return 0;
    }
  }
  
  return 0;
}
