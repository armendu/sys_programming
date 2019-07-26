/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  sh_mem.c
 *
 * @brief 
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun, Jul 21, 2019 23:35$
 */

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "sh_mem.h"

int shm_init(shm_elm_t *shm_obj)
{
  key_t shmkey;
  int shmid;

  shmkey = ftok(".", 'x');
  shmid = shmget(shmkey, sizeof(shm_elm_t), IPC_CREAT | 0666);

  if (shmid < 0)
  {
    return -1;
  }

  /* Attach to the segment to get a pointer to it.*/
  shmat(shmid, &shm_obj, 0);
  if ((void *)shm_obj == -1)
  {
    return 1;
  }

  return shmid;
}

void shm_free(int shmid, shm_elm_t *const shm_obj)
{
  shmdt((void *)shm_obj);
  shmctl(shmid, IPC_RMID, NULL);
}

int shm_write(int shmid, shm_elm_t *shmseg, const char* text)
{
  /* struct shmseg *shmp; */
  char *bufptr;

  if (shmid == -1)
  {
    perror("shm_write");
    return -1;
  }

  /* Transfer blocks of data from buffer to shared memory */
  bufptr = shmseg->msg;
  shmseg->len = strlen(shmseg->msg);
  shmseg->state = SHM_EMPTY;
  strcpy(bufptr, text);

  shmseg->state = SHM_FULL;

  printf("\nshm_write: Wrote: %s\n", shmseg->msg);
  printf("\nshm_write: Writing Process Complete\n");
  return 0;
}

int shm_read(int shmid, shm_elm_t *shmp, char* msg)
{
  if (shmid == -1)
  {
    perror("Shared memory");
    return -1;
  }

  printf("shmp->state %d\n", shmp->state);
  printf("shmp->len %d\n", shmp->len);
  printf("shmp->msg %s\n", shmp->msg);
  /* Transfer blocks of data from shared memory to stdout*/
  if (shmp->state != SHM_EMPTY)
  {
    if (shmp->len == -1)
    {
      perror("read");
      return -1;
    }

    if(shmp->len == 0)
    {
      shmp->state = SHM_EMPTY;
      return -1;
    }

    strcpy(&msg, shmp->msg);
    printf("After strcpy\n");
    printf("shmp->state %d\n", shmp->state);
  printf("shmp->len %d\n", shmp->len);
  printf("shmp->msg %s\n", shmp->msg);

    printf("shm_read Process: Shared Memory: Read %d bytes\n", shmp->len);
    shmp->state = SHM_EMPTY;
  }
  else
  {
    return -1;
  }  

  printf("shm_read Process: Complete\n");
  return 0;
}