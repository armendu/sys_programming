/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  client.c
 *
 * @brief Implements the funtionality for the client
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun, Jul 21, 2019 23:32$
 */

#include <stdio.h>
#include <stdlib.h>

#include "msg_queue.h"
#include "opt_proc.h"

int main(int argc, char **argv)
{
  char *f_name 	= NULL;
	
	/* set the mode and retrieve the file name */
	int n_secs = get_client_args(argc, argv, &f_name);

  if (n_secs == -1)
  {
    return -1;
  }

  return open_client_mq(f_name, n_secs);
}