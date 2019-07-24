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
#include <errno.h>
#include <unistd.h>

#include "msg_queue.h"
#include "f_ser.h"

#define MY_MQ_NAME "/my_mq1"

static struct mq_attr my_mq_attr;
static mqd_t my_mq;

void sig_handler(int signum);

int main()
{
  signal(SIGINT, sig_handler);

  int status;
  /*pid_t pid = getpid();*/

  msq_elm_t element = { .msg = "/tmp/nmpiped_100", .len = 123, .p_id = 456 };
  /*element.msg[element.len] = ;*/
/*
  my_mq_attr.mq_maxmsg = sizeof(msq_elm_t);
  my_mq_attr.mq_msgsize = sizeof(msq_elm_t);
  */


  my_mq = mq_open(MY_MQ_NAME, O_CREAT | O_RDWR, 0666, NULL);

  printf("Client has started\n");

  /* Read from the message from the file here */

  while (1)
  {
    /* Send "HELLO" as a message with priority 10, then close the queue.
      Note the size is 6 to include the null byte '\0'. */
    status = mq_send(my_mq, (const char *) &element, sizeof(element), 0);

    printf("Value of errno: %d\n ", errno);
    
    printf("Status is %d\n", status);
    if (status == 0)
    {
      printf("Sent message, now sleeping...\n");
      break;
    }

    nanosleep((const struct timespec[]){{1, 0L}}, NULL);
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