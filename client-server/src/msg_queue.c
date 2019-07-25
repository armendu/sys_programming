/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  msg_queue.c
 *
 * @brief 
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun21, Jul 21, 2019 23:35$
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
#include <errno.h>
#include <time.h>

#include "msg_queue.h"
#include "nm_pipe.h"
#include "f_ser.h"

/* Define constants */
#define SERVER_QUEUE_NAME "/server-mq"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

void sig_handler(int signum);

mqd_t mq_server;

int open_server_mq(const char *f_name)
{
	signal(SIGINT, sig_handler);
	printf("Server is running..\n");
	msq_elm_t message;

	/* Set attributes for server queue */
	struct mq_attr attr;
	attr.mq_maxmsg = MAX_MESSAGES;
	attr.mq_msgsize = MAX_MSG_SIZE;
	attr.mq_flags = 0;
	attr.mq_curmsgs = 0;

	/* Open message queue */
	if ((mq_server = mq_open(SERVER_QUEUE_NAME, O_RDONLY | O_CREAT,
													 QUEUE_PERMISSIONS, &attr)) == -1)
	{
		perror("Server: mq_open (server)");
		exit(1);
	}

	while (1)
	{
		/* Receive message in message queue */
		if (mq_receive(mq_server, (char *)&message, MSG_BUFFER_SIZE,
									 NULL) == -1)
		{
			perror("Server: mq_receive");
			exit(1);
		}
		else
		{
			printf("Received message from client: %s\n", message.msg);

			nm_pipe_t nmp_obj;

			/* Create pipe if it does not exist */
			int result = nmp_init(&nmp_obj, message.msg);
			printf("init result is %d\n", result);

			if (result == -1)
			{
				printf("Failed to create pipe\n");
				return -1;
			}

			pid_t pid;
			pid = fork();

			if (pid < 0)
			{
				perror("fork");
				return -1;
			}

			if (pid == 0)
			{
				printf("Child process created...\n");

				/* Receive information from pipe */
				int rcvresult = nmp_recv(&nmp_obj);
				printf("after receive result is %d\n", rcvresult);

				printf("Message in server: %s\n", nmp_obj.elm.msg);

				if (rcvresult == -1)
				{
					printf("FAILED TO READ FROM PIPE\n");
				}
				else
				{
					printf("SUCCESS");
				}
			}
			else
			{
				/* Parent process */
			}
		}
	}

	return 0;
}

int open_client_mq(const char *f_name, int n_secs)
{
	signal(SIGINT, sig_handler);
	printf("Client is running..\n");

	/* Get process id and create message */
	int p_id = getpid();
	msq_elm_t message;

	/* Set pipe name and message data */
	message.p_id = p_id;
	message.len = sizeof(message.msg);
	sprintf(message.msg, "/tmp/nmpiped_%d", p_id);

	/* Create pipe if it does not exist */
	nm_pipe_t nmp_obj;
	int result = nmp_init(&nmp_obj, message.msg);

	if (result == -1)
	{
		return -1;
	}

	if ((mq_server = mq_open(SERVER_QUEUE_NAME, O_WRONLY)) == -1)
	{
		perror("Client: mq_open (server)");
		exit(1);
	}

	if (mq_send(mq_server, (const char *)&message, sizeof(message) + 1,
							0) == -1)
	{
		perror("Not able to send message to server\n");
	}
	else
	{
		printf("Sent message: '%s'\n", message.msg);

		/* open a file */
		printf("\nThe file '%s' is opening ...\n", f_name);

		FILE *fp;
		if ((fp = fopen(f_name, "r")) == NULL)
		{
			printf("\nError opening the file: '%s' [Error string: '%s']",
						 f_name, strerror(errno));
			return -1;
		}

		char buff[NMP_MSG_LEN];
		while (1)
		{
			fgets(buff, NMP_MSG_LEN - 1, fp);
			printf("3: %s\n", buff);

			nmp_obj.elm.len = message.len;
			strcpy(nmp_obj.elm.msg, buff);

			printf("The read text is: '%s'", buff);

			/* Send message in named pipe */
			int result = nmp_send(&nmp_obj);

			if (result == -1)
			{
				return -1;
			}
			/* reset the file pointer at the file begin  */
  		(void)fseek(fp, 0, SEEK_SET);

			printf("Success sending message in pipe.\n");

			nanosleep((const struct timespec[]){{5, 0L}}, NULL);
		}
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
	mq_close(mq_server);
	mq_unlink(SERVER_QUEUE_NAME);

	exit(0);
}