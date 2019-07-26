/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  msg_queue.c
 *
 * @brief Implements the functionality for 
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
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#include "msg_queue.h"
#include "nm_pipe.h"
#include "f_ser.h"

/* Define constants */
#define SERVER_QUEUE_NAME "/server-mq"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE 512

void sig_handler(int signum);

mqd_t mq_server;

/***************************************************************************//** 
 * @brief Starts main server process
 * 
 * Starts main server process, creates message queue, connections 
 * handlers for each client, and a record process 
 *
 * @param[in] f_name - file name
 *
 * @retval -1 in case an error was occurred
 * @retval 	0 if no error occurred
 ******************************************************************************/
int open_server_mq(const char *f_name)
{
	signal(SIGINT, sig_handler);
	printf("Server is running. Waiting for clients...\n");
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
		perror("Server: mq_open");
		exit(1);
	}

	/* semaphori edhe shared memory */
	int semaphor_id;
	int shm_id;

	pid_t r_pid;
	r_pid = fork();

	if (r_pid < 0)
	{
		perror("fork");
		return -1;
	}

	if (r_pid == 0)
	{
		/* Record child process */
		FILE *fp;
		if ((fp = fopen(f_name, "a+")) == NULL)
		{
			printf("\nError opening the file: '%s' [Error string: '%s']\n",
						 f_name, strerror(errno));
			return -1;
		}

		while (1)
		{
			/*
			if (str_write(fp, shmem) > 0)
			{
				printf("Wrote all content to file.\n");
				break;
			}
			 */
		}
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

				while (1)
				{
					/* Receive information from pipe */
					if(nmp_recv(&nmp_obj) == -1)
					{
						perror("Failed to read from pipe.\n");
						return -1;
					}
					
					printf("\nSuccessfully read from pipe.\n");
				}
			}
		}
	}

	return 0;
}

/***************************************************************************//** 
 * @brief Starts main client process
 * 
 * Starts main client process, creates message queue, and named pipe
 * to communicate with a connection handler. 
 *
 * @param[in] f_name - file name
 * @param[in] n_secs - the number of seconds the client sleeps
 *
 * @retval -1 in case an error was occurred
 * @retval 	0 if no error occurred
 ******************************************************************************/
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
		perror("Client: mq_open");
		exit(1);
	}

	if (mq_send(mq_server, (const char *)&message, sizeof(message) + 1,
							0) == -1)
	{
		perror("Client: Not able to send message to server");
	}
	else
	{
		printf("Client: Sent message: '%s'\n", message.msg);

		/* open a file */
		printf("\nClient: The file '%s' is opening ...\n", f_name);

		FILE *fp;
		if ((fp = fopen(f_name, "r")) == NULL)
		{
			printf("\nError opening the file: '%s' [Error string: '%s']\n",
						 f_name, strerror(errno));
			return -1;
		}

		char buff[NMP_MSG_LEN];
		while (fgets(buff, NMP_MSG_LEN, fp) != NULL)
		{
			int s_len = str_len(buff);

			if (buff[s_len - 1] == '\n')
			{
				buff[s_len - 1] = '\0';
			}
    	
			nmp_obj.elm.len = message.len;
			strcpy(nmp_obj.elm.msg, buff);

			printf("Successfully got message '%s'\n", buff);

			/* Send message in named pipe */
			int result = nmp_send(&nmp_obj);

			if (result == -1)
			{
				return -1;
			}

			printf("\nMessage sent to named pipe. Now sleeping...\n");

			nanosleep((const struct timespec[]){{n_secs, 0L}}, NULL);
		}

		/* No more rows to send */
		printf("File content sent successfully\n.");
		free(fp);
		nmp_free(&nmp_obj);
	}
	return 0;
}

/***************************************************************************//** 
 * @brief Handles the CTRL+C signal.
 *
 * @param[in] signum - The signal number
 ******************************************************************************/
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