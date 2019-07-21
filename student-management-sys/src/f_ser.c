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
#include <malloc.h>
#include <unistd.h>

int get_no_students(FILE *fp);

#include "f_ser.h"
#include "student.h"

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

/***************************************************************************/ /** 
 * @brief Writes a student into the file 
 *
 * @param[in,out] fp - file pointer
 * @param[in] student - the student to be written
 *
 * @retval 0  in case an error was occured
 * @retval >0 number of bytes written in the file
 ******************************************************************************/
int student_write(FILE *fp, const student_t student)
{
  int status = 0;

  int nr_students = get_no_students(fp);

  if (nr_students < MAX_NO_STUDENTS)
  {
    status = (int)fwrite(&student, sizeof(struct student_t), (size_t)1, fp);

    if (status == 0)
    {
      printf("\nAn error occurred while writing to file.");
    }
  }
  else
  {
    printf("\nThe maximum number of students are registered.");
    return 0;
  }

  printf("\nThe no. of students is: '%d'.", nr_students + 1);

  return status;
}

/***************************************************************************/ /** 
 * @brief Reads students from the file 
 *
 * @param[in,out] fp - file pointer
 *
 * @retval 0  in case an error was occured
 * @retval 1  in case the students where successfully read
 ******************************************************************************/
int student_read(FILE *fp)
{
  int status = 0;
  struct student_t student;

  while ((status = fread(&student, (size_t)sizeof(struct student_t), (size_t)1, fp)))
  {
    if (status == 0)
    {
      printf("\nError reading from file");
      return 0;
    }

    printf("\n\nFirstname:    \t\t%s", student.firstname);
    printf("\nLastname:       \t%s", student.lastname);
    printf("\nIndex number:   \t%s", student.indexNumber);
    printf("\nAge:            \t%d", student.age);
    printf("\nAddress:        \t%s", student.address);
  }

  return 1;
}

/***************************************************************************/ /** 
 * @brief Returns the no. of students in a file
 *
 * @param[in,out] fp - the file pointer
 * 
 * @retval  0  in case there are no students
 * @retval >0  in case there are more students registered
 ******************************************************************************/
int get_no_students(FILE *fp)
{
  int status = 0;
  int no_of_students = 0;

  struct student_t student;

  while ((status = fread(&student, (size_t)sizeof(struct student_t), (size_t)1, fp)))
  {
    if (status == 0)
    {
      printf("\nError reading from file");
      return status;
    }

    no_of_students = no_of_students + 1;
  }

  return no_of_students;
}
