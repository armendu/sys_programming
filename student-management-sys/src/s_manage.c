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

#include "s_manage.h"
#include "student.h"
#include "f_ser.h"

int get_student_info(student_t *s)
{
  char firstName[MAX];
  char lastName[MAX];
  char indexNumber[MAX];
  char age[10];
  char address[MAX];

  int s_len = 0;

  printf("\nPlease write the firstname of the student: ");
  if (fgets(firstName, MAX, stdin) != NULL)
  {
    s_len = str_len(firstName);
    firstName[s_len - 1] = '\0';
    s->firstname = (char *) malloc ((size_t) s_len + 1);
    if (s->firstname == NULL)
    {
      printf ("\nError allocating memory");
      return -1;
    }
    strcpy(s->firstname, firstName);
  }

  printf("\nPlease write the lastname of the student: ");
  if (fgets(lastName, MAX, stdin) != NULL)
  {
    s_len = str_len(lastName);
    lastName[s_len - 1] = '\0';
    s->lastname = (char *) malloc ((size_t) s_len + 1);
    
    if (s->lastname == NULL)
     {
       printf ("\nError allocating memory");
       return -1;
     }
    strcpy(s->lastname, lastName);
  }

  printf("\nPlease write the index number of the student: ");
  if (fgets(indexNumber, MAX, stdin) != NULL)
  {
    s_len = str_len(indexNumber);
    indexNumber[s_len - 1] = '\0';
    s->indexNumber = (char *) malloc ((size_t) s_len + 1);

    if (s->indexNumber == NULL)
    {
      printf ("\nError allocating memory");
      return -1;
    }
    strcpy(s->indexNumber, indexNumber);
  }

  printf("\nPlease write the age of the student: ");
  if (fgets(age, sizeof age, stdin) != NULL)
  {
    s->age = convert_to_int(age);
  }

  printf("\nPlease write the address of the student: ");
  if (fgets(address, MAX, stdin) != NULL)
  {
    s_len = str_len(address);
    address[s_len - 1] = '\0';
    s->address = (char *) malloc ((size_t) s_len + 1);

    if (s->address == NULL)
    {
      printf ("\nError allocating memory");
      return -1;
    }
    strcpy(s->address, address);
  }

  printf("\n%s", s->firstname);
  printf("\n%s", s->lastname);
  printf("\n%s", s->indexNumber);
  printf("\n%d", s->age);
  printf("\n%s", s->address);

  return 0;
}

int numberOfRegisteredStudents(FILE *fp)
{
  int status = 0;
  student_t s;
  int numberOfStudents = 0;

   while((status = fread (&s, (size_t) sizeof(s), (size_t) 1, fp) ) )
  {
    if (status == 0)
    {
      printf ("\nError reading from file");
      return status;
    }
    numberOfStudents ++;
  }

  return numberOfStudents;
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