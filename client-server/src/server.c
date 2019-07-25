/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  server.c
 *
 * @brief Implements the functionality for the server
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun, Jul 21, 2019 23:34$
 */

#include <stdlib.h>
#include <stdio.h>

#include "msg_queue.h"
#include "opt_proc.h"

int main(int argc, char **argv)
{
  char *f_name 	= NULL;
	
	/* set the mode and retrieve the file name */
	int result = get_server_args(argc, argv, &f_name);

  if (result == -1)
  {
    return -1;
  }

  return open_server_mq(f_name);
}