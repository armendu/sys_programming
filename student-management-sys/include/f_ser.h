 /**
 * Copyright (C) 2019 Bsc. Armend Ukehaxhaj. All rights reserved
 * Rr. Agim Ramadani pn., Prishtine, Kosovo. armendd.u@hotmail.com
 *
 * @file  f_ser.h
 *
 * @brief Provides functions for the student file serialization
 * 
 * @author (IS) Bsc. Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: 19 May 19, 18:02:25 WEST 2019 $
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