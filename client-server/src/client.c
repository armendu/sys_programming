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
#include <signal.h>
#include <time.h>
#include <mqueue.h>
#include <unistd.h>

#include "msg_queue.h"
#include "f_ser.h"

#define MY_MQ_NAME "/my_mq"

static struct mq_attr my_mq_attr;
static mqd_t my_mq;
static msq_elm_t element;

void sig_handler(int signum);

int main()
{
  signal(SIGINT, sig_handler);

  int status;
  char message[element.len];

  my_mq_attr.mq_msgsize = sizeof(element.len);

  my_mq = mq_open(MY_MQ_NAME, O_CREAT | O_RDWR, 0666, &my_mq_attr);

  printf("Client has started. Execution period = %d seconds\n", 5);

  printf("\nPlease write the message: ");

  /* Read from the message from the file here */

  while (1)
  {
    /* Send "HELLO" as a message with priority 10, then close the queue.
      Note the size is 6 to include the null byte '\0'. */
    status = mq_send(my_mq, (const char *)&message, sizeof(message) + 1, 0);

    printf("Status is %d\n", status);
    if (status == 0)
    {
      printf("Sent message, now sleeping...");
    }

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