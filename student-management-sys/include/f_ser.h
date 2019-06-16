/** 
 * Copyright (C) 2003-2019 Dipl.Ing. Dr. techn. Idriz Smaili. All rights reserved
 * Siebenbuergerstrasse 16-26/26/17, A--1220 Wien, Austria. smaili.idriz@gmail.com
 *
 * @file  f_ser.h
 *
 * @brief Provides functions for the string file serialization
 * 
 * @author (IS) Dr.techn. Dipl.-Ing. Idriz Smaili (smaili.idriz@gmail.com)
 * @date   $Date: Fri Apr 20, 15:27:59 WEST 2019 $
 */

#ifndef _F_SER_H_
#define _F_SER_H 1_

#include <stdio.h>
#include "student.h"

int str_len       (          const char *str);
int student_write (FILE *fp, student_t   s);
int student_read  (FILE *fp);
int get_no_bytes  (FILE *fp);

#endif /* _F_SER_H */