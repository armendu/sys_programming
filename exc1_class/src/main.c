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
#include <string.h>
#include <errno.h>

#include "opt_proc.h"
#include "f_ser.h"

int main (int argc, const char *argv [])
{
  char *str1   = "Programimi Sistemor";
  char *str2   = "Eshte Cool";
  char *f_name = ".test";

  char *r_str1 = NULL; /*@null@*/
  char *r_str2 = NULL; /*@null@*/

  FILE *fp     = NULL;

  /* open a file */
  printf ("\nThe file '%s' is opening ... ", f_name);
  
  if ((fp = fopen (f_name, "a+")) == NULL)
    {
      printf ("\nError opening the file: '%s' [Error string: '%s']",
              f_name, strerror (errno));
      return -1;
    }
  
  printf (" done");

  printf ("\nThe first string '%s' is being written ... ", str1);
  if (str_write (fp, str1) == 0)
    {
      return -1;
    }
  printf (" done");

  printf ("\nThe second string '%s' is being written ... ", str2);
  if (str_write (fp, str2) == 0)
    {
      return -1;
    }
  printf (" done");

  /* reset the file pointer at the file begin  */
  (void) fseek (fp, 0, SEEK_SET);
  
  printf ("\nThe first string is being read ... ");
  if (str_read (fp, &r_str1) == 0)
    {
      return -1;
    }
  printf (" done [%s]", r_str1);

  printf ("\nThe second string is being read ... ");
  if (str_read (fp, &r_str2) == 0)
    {
      return -1;
    }
  printf (" done [%s]", r_str2);

  /* close the file */
  fclose (fp);

  free (r_str1);
  free (r_str2);
  
  usage  (argv [0]);
  
  return 0;
}
