/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  sh_mem.h
 *
 * @brief Provides functions for the shared memory functionality
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun, Jul 21, 2019 23:36$
 */

#ifndef _SH_MEM__H
#define _SH_MEM__H 1

#define SHM_MSG_LEN     (int)512
#define SHM_FULL        (char)0x01
#define SHM_EMPTY       (char)0x02
#define SHM_PERMISSIONS (int)0666
#define SHM_NAME        "shared_memory"
#define SHM_SIZE        (int)4096

typedef struct _shm_elm
{
  char state;
  int len;
  char msg[SHM_MSG_LEN];
} shm_elm_t;

int shm_init(void* shm_ptr);
int   shm_read  (int shm_id, shm_elm_t *shmp, char* msg);
int shm_write(void* shm_ptr, const shm_elm_t shm_element);
void  shm_free (int shm_id, shm_elm_t *const shm_obj);

#endif /* _SH_MEM__H */
