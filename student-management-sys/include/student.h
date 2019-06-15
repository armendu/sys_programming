/**
 * Copyright (C) 2019 Bsc. Armend Ukehaxhaj. All rights reserved
 * Rr. Agim Ramadani pn., Prishtine, Kosovo. armendd.u@hotmail.com
 *
 * @file student.h
 *
 * @brief Defines a student structure
 * 
 * @author (IS) Bsc. Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: 19 May 19, 18:20:52 WEST 2019 $
 */

#ifndef _STUDENT_H
#define _STUDENT_H 1_

typedef struct student_t
{
  char          *firstname;
  char          *lastname;
  char          *indexNumber;
  int unsigned  age;
  char          *address;
} student_t;


#endif /* _STUDENT_H */