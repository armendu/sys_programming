/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  server.c
 *
 * @brief 
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun, Jul 21, 2019 23:34$
 */

#include <signal.h>
#include <errno.h>

#include "opt_proc.h"

int main(int argc, char *argv[])
{
  signal(SIGINT, handle_sigint);
}