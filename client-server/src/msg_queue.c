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

#include "msg_queue.h"

/* Define constants */
#define SERVER_QUEUE_NAME "/server-mq"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

void sig_handler(int signum);

mqd_t mq_server;

int open_server_mq(FILE *log_file)
{
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
		}
	}

	return 0;
}

int open_client_mq(FILE *msg_file, int n_secs)
{
	printf("Client is running..\n");

	int p_id = getpid();
	msq_elm_t message;

	message.p_id = p_id;
	message.len = strlen(message.msg);
	sprintf(message.msg, "/tmp/nmpiped_%d", p_id);

	

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
	}
	return 0;
}

int open_msg_queue(int type)
{
	signal(SIGINT, sig_handler);

	msq_elm_t message;

	if (type == 0)
	{
		printf("Server is running..\n");

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

			printf("Received message from client: %s\n", message.msg);
		}
	}
	if (type == 1)
	{
		printf("Client is running..\n");

		int p_id = getpid();

		message.p_id = p_id;
		message.len = strlen(message.msg);
		sprintf(message.msg, "/tmp/nmpiped_%d", p_id);

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