/**
 * Copyright (C) 2003-2019 Dipl.Ing. Dr. techn. Idriz Smaili. All rights reserved
 * Siebenbuergerstrasse 16-26/26/17, A--1220 Wien, Austria. smaili.idriz@gmail.com
 *
 * @file  f_str.c
 *
 * @brief Implements a function to count the length of a string
 * 
 * @author (IS) Dr.techn. Dipl.-Ing. Idriz Smaili (smaili.idriz@gmail.com)
 * @date   $Date: Fri Apr 19, 15:27:59 WEST 2019 $
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "f_str.h"
#include "string_compare.h"

int str_write(FILE *fp, const char* str)
{
  int status = 0;
  int length = 0;

  length = find_length(str);

  /**
  First we write the length of the string we want to save inside the file.
  SER_INT_LEN is defined inside the header file.
  */
  status = (int) fwrite ((const void *) &length, (size_t) 1, (size_t) SER_INT_LEN, fp);

  if (status == 0)
  {
    printf("\nError writing length of '%s' to the file", str);
  }

  return status;
}

int str_read(FILE *fp, char** str)
{
  int   s_len  = 0;
  int   status = 0;
  char *ptr    = NULL;

  /* First we read the first 4 bytes so that we know the length of the string  */
  status = fread((void *) &s_len, (size_t) 1, (size_t) SER_INT_LEN, fp);

  if (status == 0)
  {
    printf("\nError reading from file");
    return status;
  }

  ptr = (char *)malloc((size_t) s_len + 1);

  /* We must always check if malloc was executed successfully. */
  if (ptr == NULL)
  {
    printf("\nError allocating memory");
    return SER_ALLOC_ERROR;
  }

  status = fread((void *) ptr, (size_t) 1, (size_t) s_len, fp);

  ptr[s_len] = '\0';

  if (status == 0)
  {
    printf("\nError reading from file");
  }
  
  return status;
}

int append_string(FILE *fp, const char *str)
{
  int status = 0;
  int length = 0;

  length = find_length(str);

  /**
  First we write the length of the string we want to save inside the file.
  SER_INT_LEN is defined inside the header file.
  */
  status = (int) fwrite ((const void *) &length, (size_t) 1, (size_t) SER_INT_LEN, fp);

  if (status == 0)
  {
    printf("\nError writing length of '%s' to the file", str);
  }

  return status;
}

int list_file(FILE *fp)
{
  return 0;
}

typedef struct Studenti
{
  int id;
  char *emri;
  char *mbiemri;
} Studenti;
