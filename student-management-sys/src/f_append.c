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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int get_user_input(char **input);
unsigned int convert_to_int(char *st);

#include "f_append.h"
#include "student.h"
#include "f_ser.h"

int append_student(FILE **fp)
{
  student_t student;

  char firstName[MAX];
  char lastName[MAX];
  char indexNumber[MAX];
  char age[3];
  char address[MAX];

  int s_len = 0;

  printf("\nPlease write the firstname of the student: ");
  if (fgets(firstName, MAX, stdin) != NULL)
  {
    s_len = str_len(firstName);
    firstName[s_len - 1] = '\0';
    student.firstname = (char *) malloc ((size_t) s_len + 1);
    if (student.firstname == NULL)
    {
      printf ("\nError allocating memory");
      return -1;
    }
    strcpy(student.firstname, firstName);
  }

  printf("\nPlease write the lastname of the student: ");
  if (fgets(lastName, MAX, stdin) != NULL)
  {
    s_len = str_len(lastName);
    lastName[s_len - 1] = '\0';
    student.lastname = (char *) malloc ((size_t) s_len + 1);
    
    if (student.lastname == NULL)
     {
       printf ("\nError allocating memory");
       return -1;
     }
    strcpy(student.lastname, lastName);
  }

  printf("\nPlease write the index number of the student: ");
  if (fgets(indexNumber, MAX, stdin) != NULL)
  {
    s_len = str_len(indexNumber);
    indexNumber[s_len - 1] = '\0';
    student.indexNumber = (char *) malloc ((size_t) s_len + 1);

    if (student.indexNumber == NULL)
    {
      printf ("\nError allocating memory");
      return -1;
    }
    strcpy(student.indexNumber, indexNumber);
  }

  printf("\nPlease write the age of the student: ");
  if (fgets(age, sizeof age, stdin) != NULL)
  {
    student.age = convert_to_int(age);
  }

  printf("\nPlease write the address of the student: ");
  if (fgets(address, MAX, stdin) != NULL)
  {
    s_len = str_len(address);
    address[s_len - 1] = '\0';
    student.address = (char *) malloc ((size_t) s_len + 1);

    if (student.address == NULL)
    {
      printf ("\nError allocating memory");
      return -1;
    }
    strcpy(student.address, address);
  }

  printf("\n%s", student.firstname);
  printf("\n%s", student.lastname);
  printf("\n%s", student.indexNumber);
  printf("\n%d", student.age);
  printf("\n%s", student.address);

  char *r_str1 = NULL; /*@null@*/

  printf("\nThe first string is being read ... ");
  if (str_read(*fp, &r_str1) == 0)
  {
    return -1;
  }
  printf(" done [%s]", r_str1);

  return 0;
}

unsigned int convert_to_int(char *st)
{
  char *x;
  for (x = st; *x; x++)
  {
    if (!isdigit(*x))
    {
      return 0L;
    }
  }

  return (strtoul(st, 0L, 10));
}