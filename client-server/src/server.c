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

int main(int argc, char **argv)
{
  FILE *fp = NULL;
  /* open_msg_queue(0); */
  open_server_mq(fp);
  
  return 0;
}