/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  server_proc.c
 *
 * @brief Provides functions for the record process
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun21, Jul 21, 2019 23:42$
 */

#ifndef _REC_PROC__H
#define _REC_PROC__H 1

#include <semaphore.h>

#include "sh_mem.h"

int handle_rec(const char *f_name, shm_elm_t *shm_ptr, sem_t *reader_sem);

#endif /* _REC_PROC__H */