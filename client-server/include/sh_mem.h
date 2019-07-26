/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  sh_mem.h
 *
 * @brief 
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun, Jul 21, 2019 23:36$
 */

#ifndef _SH_MEM__H
#define _SH_MEM__H 1

#define SHM_MSG_LEN (int)512
#define SHM_FULL (char)0x01
#define SHM_EMPTY (char)0x02
#define BUF_SIZE 1024
#define SHM_KEY 0x1234

typedef struct _shm_elm
{
  char state;
  int len;
  char msg[SHM_MSG_LEN];
} shm_elm_t;

int shm_read(int shmid, shm_elm_t *shmp, char* msg);
int shm_write(int shmid, shm_elm_t *shmseg, const char* text);
int shm_init(shm_elm_t *shm_obj);
void shm_free(int shmid, shm_elm_t *const shm_obj);

#endif /* _SH_MEM__H */
