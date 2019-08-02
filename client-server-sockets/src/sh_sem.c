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

#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "sh_sem.h"

/***************************************************************************/ /**
 * @brief Free the resource of the semaphore
 *
 * @param[in] 		f_name  - the file name
 * @param[in,out]	shm_ptr - The shared memory pointer
 *
 * @retval -1 - If an error occurred
 * @retval  0 - If the operation was successful
 ******************************************************************************/
int sem_free()
{
  if (sem_unlink(WRITER_SEM_NAME) == -1)
	{
    return -1;
  }

  if (sem_unlink(READER_SEM_NAME) == -1)
  {
    return -1;
  }

  return 0;
}