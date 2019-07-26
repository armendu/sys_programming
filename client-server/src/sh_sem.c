/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  sh_sem.c
 *
 * @brief 
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun, Jul 21, 2019 23:34$
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include "sh_sem.h"

int set_semaphore_value()
{
  union semun sem_un;

  sem_un.val = 1;

  return semctl(sem_id, 0, SETVAL, sem_un);
}

void delete_semaphore()
{
  union semun sem_un;

  if (semctl(sem_id, 0, IPC_RMID, sem_un) == -1)
  {
    printf("Semaphore not deleted... \n");
    exit(EXIT_FAILURE);
  }

  else
  {
    printf("Semaphore deleted successfully... \n");
  }
}

int p()
{
  struct sembuf sem_buf;

  sem_buf.sem_num = 0;
  sem_buf.sem_op = -1;
  sem_buf.sem_flg = SEM_UNDO;

  if (semop(sem_id, &sem_buf, 1) == -1)
  {
    printf("Semaphore p function failed... \n");
    return -1;
  }

  return 0;
}

int v()
{
  struct sembuf sem_buf;

  sem_buf.sem_num = 0;
  sem_buf.sem_op = 1;
  sem_buf.sem_flg = SEM_UNDO;

  if (semop(sem_id, &sem_buf, 1) == -1)
  {
    printf("Semaphore v function failed... \n");
    return -1;
  }

  return 0;
}