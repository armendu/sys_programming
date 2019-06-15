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
#include <getopt.h>
#include <string.h>
#include <errno.h>

int main (int argc, char *argv [])
{
  FILE *fp     = NULL;
  char *f_name   = NULL;

  int opt;
  int f = -1;
  char* input = NULL;
  while((opt = getopt(argc, argv, "f:ali:")) != -1)
  {
    switch (opt)
    {
      case 'f':
        f = (int)atol(optarg);
        f_name = optarg;
        printf("\nGot f with filename: %s\n", optarg);
        break;
      case 'a':
        printf("Write the name of the file: ");
        break;
      case 'i':
        printf("You are entering interactive mode, please type your next command:");
        while (1)
        {
          scanf("%s", input);
          /*enter_interactive_mode(input); */
        }
        break;
      case ':':
        printf("Option '-f' needs a value.\n");
        return -1;
        break;
      default:
        return 0;
    }
  }

  if (f == -1) 
  {
    printf("File name shoud be specified using '-f' as it is mandatory.\n");
    return -1;
  }
  
  /* open a file */
  printf("\nThe file '%s' is opening ... ", f_name);

  if ((fp = fopen (f_name, "a+")) == NULL)
  {
    printf("\nError opening the file: '%s' [Error string: '%s']",
              f_name, strerror (errno));
    return -1;
  }
  
  return 0;
}