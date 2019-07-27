/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  sh_sem.c
 *
 * @brief Implements the functionality for the semaphore
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun, Jul 21, 2019 23:34$
 */

#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include "sh_sem.h"

int create_named_sem(sem_t *sem)
{
	sem = sem_open(SEM_NAME, O_CREAT | SEM_PERMISSIONS);
	
  if (sem == SEM_FAILED)
  {
    perror("create_named_sem");
    return -1;
  }

  return 0;
}