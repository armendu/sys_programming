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

#include "s_manage.h"
#include "f_ser.h"

void get_student_info(student_t *s)
{
  char firstName  [FIRSTNAME_LENGTH];
  char lastName   [LASTNAME_LENGTH];
  char indexNumber[INDEX_LENGTH];
  char age        [10];
  char address    [ADDRESS_LENGTH];

  int s_len = 0;

  printf("\nPlease write all the information for the student.");
  printf("\nStudent Firstname: ");
  if (fgets(firstName, FIRSTNAME_LENGTH, stdin) != NULL)
  {
    s_len = str_len(firstName);
    firstName[s_len - 1] = '\0';
    
    strcpy(s->firstname, firstName);
  }

  printf("\nStudent Lastname: ");
  if (fgets(lastName, LASTNAME_LENGTH, stdin) != NULL)
  {
    s_len = str_len(lastName);
    lastName[s_len - 1] = '\0';
    
    strcpy(s->lastname, lastName);
  }

  printf("\nStudent Index number: ");
  if (fgets(indexNumber, INDEX_LENGTH, stdin) != NULL)
  {
    s_len = str_len(indexNumber);
    indexNumber[s_len - 1] = '\0';

    strcpy(s->indexNumber, indexNumber);
  }

  printf("\nStudent age: ");
  if (fgets(age, sizeof age, stdin) != NULL)
  {
    s_len = str_len(age);
    age[s_len - 1] = '\0';
    s->age = atoi(age);
  }

  printf("\nStudent Address: ");
  if (fgets(address, ADDRESS_LENGTH, stdin) != NULL)
  {
    s_len = str_len(address);
    address[s_len - 1] = '\0';
    
    strcpy(s->address, address);
  }

  return;
}

int get_no_students(FILE *fp)
{
  int status = 0;
  int internal_status = 0;
  student_t student;

    while( (internal_status = fread (&student, (size_t) sizeof(student), (size_t) 1, fp) ) )
    {
        if (internal_status == 0)
        {
            printf ("\nError reading from file");
            return internal_status;
        }

        /*
        printf ("\n\nStudent First Name: %s", student.FirstName);
        printf ("\nStudent Last Name: %s", student.LastName);
        printf ("\nStudent Id: %ld", student.IndexNumber);
        printf ("\nStudent Age: %d", student.Age);
        printf ("\nStudent Address: %s", student.Address);
         */
        status = internal_status;
    }

    return status;
}