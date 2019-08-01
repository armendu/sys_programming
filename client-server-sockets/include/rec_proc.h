/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  server_comm.c
 *
 * @brief Implements the functionality for communicating with message queues
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun21, Jul 21, 2019 23:42$
 */

#ifndef _REC_PROC__H
#define _REC_PROC__H 1

#include "sh_mem.h"

int handle_rec(const char *f_name, shm_elm_t *shm_ptr);

#endif /* _REC_PROC__H */