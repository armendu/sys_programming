/** 
 * Copyright (C) 2003-2019 Dipl.Ing. Dr. techn. Idriz Smaili. All rights reserved
 * Siebenbuergerstrasse 16-26/26/17, A--1220 Wien, Austria. smaili.idriz@gmail.com
 *
 * @file  f_str.h
 *
 * @brief Provides functions for processing of the command line options
 * 
 * @author (IS) Dr.techn. Dipl.-Ing. Idriz Smaili (smaili.idriz@gmail.com)
 * @date   $Date: Fri Apr 19, 15:27:59 WEST 2019 $
 */

#ifndef _F_STR_H_
#define _F_STR_H_ 1_

#include <stdio.h>

#define SER_INT_LEN 4
#define SER_ALLOC_ERROR -1

int str_write(FILE *fp, const char *str);
int str_read(FILE *fp, char** str);
int append_string(FILE *fp, const char *str);
int list_file(FILE *fp);

#endif /* _F_STR_H_ */

 
