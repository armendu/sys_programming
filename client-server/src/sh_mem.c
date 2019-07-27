/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  sh_mem.c
 *
 * @brief Implements the functionality for the shared memory
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

/***************************************************************************/ /**
 * @brief Initializes the shared memory
 *
 * @param[in] shm_elm_t - the shared memory object
 *
 * @retval -1 - If an error occurred
 * @retval >0 - The id of the shared memory
 ******************************************************************************/
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

  shmat(shmid, &shm_obj, 0);
  if (shm_obj == NULL)
  {
    return -1;
  }

  return shmid;
}

/***************************************************************************/ /**
 * @brief Free the shared memory
 *
 * @param[in] shm_id - the shared memory id
 * @param[in] shm_obj - the shared memory object
 ******************************************************************************/
void shm_free(int shm_id, shm_elm_t *const shm_obj)
{
  shmdt((void *)shm_obj);
  shmctl(shm_id, IPC_RMID, NULL);
}

/***************************************************************************/ /**
 * @brief Write to the shared memory
 *
 * @param[in] shm_id - the shared memory id
 * @param[in] shm_seg - the shared memory object
 * @param[in,out] text - The text set from the shared memory
 *
 * @retval -1 - If an error occurred
 * @retval 0 - If success
 ******************************************************************************/
int shm_write(int shm_id, shm_elm_t *shm_seg, const char *text)
{
  char *bufptr;

  if (shm_id == -1)
  {
    perror("shm_write");
    return -1;
  }

  /* Transfer blocks of data from buffer to shared memory */
  bufptr = shm_seg->msg;
  shm_seg->len = strlen(shm_seg->msg);
  shm_seg->state = SHM_EMPTY;
  strcpy(bufptr, text);

  shm_seg->state = SHM_FULL;

  printf("\nshm_write: Wrote: %s\n", shm_seg->msg);
  return 0;
}

/***************************************************************************/ /**
 * @brief Read from the shared memory
 *
 * @param[in] shm_id - the shared memory id
 * @param[in] shmp - the shared memory object
 * @param[in,out] msg - The text set from the shared memory
 *
 * @retval -1 - If an error occurred
 * @retval 0 - If success
 ******************************************************************************/
int shm_read(int shm_id, shm_elm_t *shmp, char *msg)
{
  if (shm_id == -1)
  {
    perror("shm_read");
    return -1;
  }

  if (shmp->state == SHM_FULL)
  {
    if (shmp->len == -1)
    {
      perror("shm_read");
      return -1;
    }

    if (shmp->len == 0)
    {
      shmp->state = SHM_EMPTY;
      return -1;
    }

    strcpy(msg, shmp->msg);

    printf("shm_read: Shared Memory: Read %d bytes\n", shmp->len);
    shmp->state = SHM_EMPTY;

    printf("shm_read: Complete\n");
    return 0;
  }

  return -1;
}