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

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#include "sh_mem.h"
#include "f_ser.h"

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
int shm_write(shm_elm_t *shm_ptr, const char* message)
{
  int len = 0;
  len = str_len(message);

  strcpy(shm_ptr->msg, message);
  shm_ptr->len = len;
  shm_ptr->state = SHM_FULL;

  printf("Copying %d bytes\n", len);
  return 0;
}

/***************************************************************************/ /**
 * @brief Free the shared memory
 *
 * @param[in] shm_id - the shared memory id
 * @param[in] shm_obj - the shared memory object
 ******************************************************************************/
int shm_free()
{
  if (shm_unlink(SHM_NAME) == -1)
  {
    return -1;
  }

  return 0;
}