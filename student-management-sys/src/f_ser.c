/**
 * Copyright (C) 2003-2019 Dipl.Ing. Dr. techn. Idriz Smaili. All rights reserved
 * Siebenbuergerstrasse 16-26/26/17, A--1220 Wien, Austria. smaili.idriz@gmail.com
 *
 * @file  f_ser.c
 *
 * @brief Implements functions for the string file serialization 
 * 
 * @author (IS) Dr.techn. Dipl.-Ing. Idriz Smaili (smaili.idriz@gmail.com)
 * @date   $Date: Fri Apr 20, 15:27:59 WEST 2019 $
 */

#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

#include "f_ser.h"

/***************************************************************************/ /** 
 * @brief Returns the number of characters in a given string
 *
 * @param[in] input string
 *
 * @retval number of characters
 ******************************************************************************/
int str_len(const char *str)
{
  register int count = 0;

  while (*str++ != '\0')
  {
    count++;
  }

  return count;
}

/***************************************************************************/ /** 
 * @brief Writes an input string into the file 
 *
 * First the four (4) bytes will be written indicating the length of the
 * string to be written, and then the string itself will be written.
 *
 * @param[in,out] fp - file pointer
 * @param[in] str - the input string
 *
 * @retval 0  in case an error was occured
 * @retval >0 number of bytes written in the file
 ******************************************************************************/
int str_write(FILE *fp, const char *str)
{
  int status = 0;
  int length = 0;

  length = str_len(str);

  status = (int)fwrite((const void *)&length, (size_t)1,
                       (size_t)SER_INT_LEN, fp);

  if (status == 0)
  {
    printf("\nError writing length of string '%s' to the file", str);
    return status;
  }

  status = (int)fwrite((const void *)str, (size_t)1,
                       (size_t)length, fp);

  if (status == 0)
  {
    printf("\nError writing string '%s' to the file", str);
  }

  return status;
}

/***************************************************************************/ /** 
 * @brief Reads an string from the file 
 *
 * First the four (4) bytes will be read, which indicate the length of the
 * string to be read, and then the string itself will be read.
 *
 * @param[in,out] fp - file pointer
 * @param[out] dst - pointer to the newly allocated string 
 *
 * @retval 0  in case an error was occured
 * @retval -1 error allocating memory was occured
 * @retval >0 number of bytes written in the file
 ******************************************************************************/
int str_read(FILE *fp, /*@null@*/ char **dst)
{
  int s_len = 0;
  int status = 0;
  char *ptr = NULL;

  status = fread((void *)&s_len, (size_t)1,
                 (size_t)SER_INT_LEN, fp);

  if (status == 0)
  {
    if (feof(fp) != 0)
    {
      return SER_EOF;
    }
    else
    {
      printf("\nError reading from file");
      return status;
    }
  }

  ptr = (char *)malloc((size_t)s_len + 1);

  if (ptr == NULL)
  {
    printf("\nError allocating memory");
    return SER_ALLOC_ERROR;
  }

  status = fread((void *)ptr, (size_t)1,
                 (size_t)s_len, fp);

  ptr[s_len] = '\0';

  if (status == 0)
  {
    printf("\nError reading from file");
  }

  *dst = ptr;
  return status;
}