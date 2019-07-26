/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  sh_sem.h
 *
 * @brief 
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun, Jul 21, 2019 23:36$
 */

#ifndef _SH_SEM__H
#define _SH_SEM__H 1

static int sem_id;

union semun
{
	int val;
};

int set_semaphore_value();
void delete_semaphore();
int p();
int v();

#endif /* _SH_SEM__H */
