/**
 * Copyright (C) 2019 Bsc. Armend Ukehaxhaj. All rights reserved
 * Rr. Agim Ramadani pn., Prishtine, Kosovo. armendd.u@hotmail.com
 *
 * @file  main.c
 *
 * @brief Implements the main function
 * 
 * @author (IS) Bsc. Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: 19 May 19, 18:20:52 WEST 2019 $
 */

#ifndef _OPT_PROC__H
#define _OPT_PROC__H 1_

void usage        (const char *app_name);
char set_mode     (int argc, char **argv, char** f_name);
void handle_sigint(int sig_num);

#endif /* _OPT_PROC__H */