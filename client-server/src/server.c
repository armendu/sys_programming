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
#include <signal.h>
#include <mqueue.h>
#include <time.h>

#include "msg_queue.h"

#define MAX_MSG 10
#define MY_MQ_NAME "/my_mq"

static struct mq_attr my_mq_attr;
static mqd_t my_mq;
static msq_elm_t element;

void sig_handler(int signum);

int main()
{
  signal(SIGINT, sig_handler);

  int status;

  my_mq_attr.mq_maxmsg = MAX_MSG;
  my_mq_attr.mq_msgsize = sizeof(element.len);

  my_mq = mq_open(MY_MQ_NAME, O_CREAT | O_RDWR, 0666, &my_mq_attr);

  /* unsigned int exec_period_usecs = 10000;  */
  char *buffer = calloc (my_mq_attr.mq_msgsize, 1);
  unsigned int priority = 0;

  while (1)
  {
    printf("Waiting for a message...\n");
    status = mq_receive(my_mq, buffer, my_mq_attr.mq_msgsize, &priority);

    if (status == -1)
    {
      printf ("Failed to receive message\n");
    }
    else
    {
      printf("Received the following message: %s\n", buffer);
    }

    /* nanosleep(exec_period_usecs); */
    nanosleep((const struct timespec[]){{5, 0L}}, NULL);
  }

  return 0;
}

void sig_handler(int signum)
{
  if (signum != SIGINT)
  {
    printf("Received invalid signum = %d in sig_handler()\n", signum);
  }

  printf("Received SIGINT. Exiting Application\n");

  mq_close(my_mq);
  mq_unlink(MY_MQ_NAME);

  exit(0);
}