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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <signal.h>

#include "msg_queue.h"

#define SERVER_QUEUE_NAME "/server-mq"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES      10
#define MAX_MSG_SIZE      256
#define MSG_BUFFER_SIZE   MAX_MSG_SIZE + 10

void sig_handler(int signum);

static mqd_t mq_server;

int main(int argc, char **argv)
{
  signal(SIGINT, sig_handler);
  printf("Server is running..\n");

  /* Set attributes for server queue */
  struct mq_attr attr;
  attr.mq_maxmsg  = MAX_MESSAGES;
  attr.mq_msgsize = MAX_MSG_SIZE;
  attr.mq_flags   = 0;
  attr.mq_curmsgs = 0;

  /* Open message queue */
  if ((mq_server = mq_open(SERVER_QUEUE_NAME, O_RDONLY | O_CREAT,
                    QUEUE_PERMISSIONS, &attr)) == -1)
  {
    perror("Server: mq_open (server)");
    exit(1);
  }

  msq_elm_t element;

  while (1)
  {
    /* Receive message in message queue */
    if (mq_receive(mq_server, (char *) &element, MSG_BUFFER_SIZE,
                    NULL) == -1)
    {
      perror("Server: mq_receive");
      exit(1);
    }

    printf("Received Message from client: %s\n", element.msg);
  }
}

void sig_handler(int signum)
{
  if (signum != SIGINT)
  {
    printf("Received invalid signum = %d in sig_handler()\n", signum);
  }

  printf("Received SIGINT. Exiting Application\n");
  mq_close(mq_server);
  mq_unlink(SERVER_QUEUE_NAME);

  exit(0);
}