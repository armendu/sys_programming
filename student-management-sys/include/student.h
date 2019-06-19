/**
 * Copyright (C) 2019 Bsc. Armend Ukehaxhaj. All rights reserved
 * Rr. Agim Ramadani pn., Prishtine, Kosovo. armendd.u@hotmail.com
 *
 * @file student.h
 *
 * @brief Defines a student structure
 * 
 * @author (IS) Bsc. Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: 19 May 19, 19:20:12 WEST 2019 $
 */

#ifndef _STUDENT_H
#define _STUDENT_H 1_

#define FIRSTNAME_LENGTH 50
#define LASTNAME_LENGTH  50
#define INDEX_LENGTH     50
#define ADDRESS_LENGTH   50

typedef struct student_t
{
  char          firstname   [FIRSTNAME_LENGTH];
  char          lastname    [LASTNAME_LENGTH];
  char          indexNumber [INDEX_LENGTH];
  char          address     [ADDRESS_LENGTH];
  int unsigned  age;
} student_t;


#endif /* _STUDENT_H */