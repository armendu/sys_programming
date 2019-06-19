/**
 * Copyright (C) 2019 Bsc. Armend Ukehaxhaj. All rights reserved
 * Rr. Agim Ramadani pn., Prishtine, Kosovo. armendd.u@hotmail.com
 *
 * @file  opt_proc.h
 *
 * @brief Provides functions for the command line arguments.
 * 
 * @author (IS) Bsc. Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: 20 May 19, 22:40:07 WEST 2019 $
 */

#ifndef _OPT_PROC__H
#define _OPT_PROC__H 1_

void usage        (const char *app_name);
char set_mode     (int argc, char **argv, char** f_name);
void handle_sigint(int sig_num);

#endif /* _OPT_PROC__H */