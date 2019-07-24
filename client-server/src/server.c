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
#include <errno.h>

#include "msg_queue.h"

#define MAX_MSG 10
#define MY_MQ_NAME "/my_mq1"

static struct mq_attr my_mq_attr;
static mqd_t my_mq;

void sig_handler(int signum);

int main()
{
  signal(SIGINT, sig_handler);

  int status;
  msq_elm_t element;
  void *buffer;

  my_mq_attr.mq_maxmsg = sizeof(msq_elm_t);
  my_mq_attr.mq_msgsize = sizeof(msq_elm_t);

  buffer = malloc(my_mq_attr.mq_msgsize);

  my_mq = mq_open(MY_MQ_NAME, O_CREAT | O_RDWR, 0666, &my_mq_attr);
  unsigned int priority = 0;

  while (1)
  {
    /*printf("Waiting for a message...\n");*/
    status = mq_receive(my_mq, (char *) &buffer, sizeof(buffer), &priority);

    if (status == -1)
    { 
      printf("Value of errno: %d\n", errno);
    }
    else
    {
      printf("Received the following message: \n");
      break;
    }

    /* nanosleep(exec_period_usecs); 
    nanosleep((const struct timespec[]){{1, 0L}}, NULL);*/
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