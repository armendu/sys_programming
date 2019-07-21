/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  opt_proc.h
 *
 * @brief 
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: 21, Jul 21, 2019 23:40$
 */

#ifndef _OPT_PROC__H
#define _OPT_PROC__H 1

void usage        ();
char set_mode     (int argc   , char **argv, char** f_name);
void handle_sigint(int sig_num);

#endif /* _OPT_PROC__H */
