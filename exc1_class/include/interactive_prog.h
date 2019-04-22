/** 
 * Copyright (C) 2003-2019 Dipl.Ing. Dr. techn. Idriz Smaili. All rights reserved
 * Siebenbuergerstrasse 16-26/26/17, A--1220 Wien, Austria. smaili.idriz@gmail.com
 *
 * @file  interactive_prog.h
 *
 * @brief Provides functions for processing of the command line options
 * 
 * @author (IS) Dr.techn. Dipl.-Ing. Idriz Smaili (smaili.idriz@gmail.com)
 * @date   $Date: Fri Apr 19, 15:27:59 WEST 2019 $
 */

#ifndef _INTERACTIVE_PROG__H
#define _INTERACTIVE_PROG__H 1

#define INTERACTIVE_QUIT "quit"
#define INTERACTIVE_APPEND "append"
#define INTERACTIVE_LIST "list"

int enter_interactive_mode ();
void terminate(int);

#endif /* _INTERACTIVE_PROG__H */
