/**
 * Copyright (C) 2019 Bsc. Armend Ukehaxhaj. All rights reserved
 * Rr. Agim Ramadani pn., Prishtine, Kosovo. armendd.u@hotmail.com
 *
 * @file  f_ser.c
 *
 * @brief Implements functions for the student file serialization
 * 
 * @author (IS) Bsc. Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: 19 May 19, 18:02:55 WEST 2019 $
 */

#include <stdio.h>

#include "f_ser.h"

/***************************************************************************/ /**
 * @brief Returns the number of characters in a given string
 *
 * @param[in] str - the input string
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