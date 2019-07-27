/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  sh_sem.h
 *
 * @brief Provides functions for the semaphore functionality
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun, Jul 21, 2019 23:36$
 */

#ifndef _SH_SEM__H
#define _SH_SEM__H 1

static int sem_id;

union semun
{
	int semun_value;
};

int 	sem_set();
int 	p();
int 	v();
void 	sem_free();

#endif /* _SH_SEM__H */
