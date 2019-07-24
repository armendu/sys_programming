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
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <signal.h>

#include "msg_queue.h"

/* Define constants */
#define SERVER_QUEUE_NAME "/server-mq"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES      10
#define MAX_MSG_SIZE      256
#define MSG_BUFFER_SIZE   MAX_MSG_SIZE + 10

void sig_handler(int signum);

mqd_t mq_server;

int main(int argc, char **argv)
{
  signal(SIGINT, sig_handler);
  int p_id = getpid();
  msq_elm_t message = { .p_id = p_id };

  sprintf(message.msg, "/tmp/nmpiped_%d", p_id);
  message.len = strlen(message.msg);

  if ((mq_server = mq_open(SERVER_QUEUE_NAME, O_WRONLY)) == -1)
  {
    perror("Client: mq_open (server)");
    exit(1);
  }

  if (mq_send(mq_server, (const char *) &message, sizeof(message) + 1,
              0) == -1)
  {
    perror("Client: Not able to send message to server");
  }

  printf("Sent message: '%s'\n", message.msg);

  exit(0);
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