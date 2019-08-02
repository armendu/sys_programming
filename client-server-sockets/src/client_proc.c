/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  server_proc.c
 *
 * @brief Implements the functionality for communicating with message queues
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun21, Jul 21, 2019 23:35$
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>

#include "server_proc.h"
#include "nm_pipe.h"

void sig_handler(int signum);
FILE *fp = NULL;

/***************************************************************************/ /** 
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
int start_client(const char *f_name, const int n_secs)
{/*
	signal(SIGINT, sig_handler);*/
	printf("Client is running..\n");

	printf("qitu\n");
	int p_id;
	msq_elm_t message;
	nm_pipe_t nmp_obj;

	/* Get process id and create message */
	p_id = getpid();

	/* Set pipe name and message data */
	message.p_id = p_id;
	message.len = sizeof(message.msg);
	sprintf(message.msg, "/tmp/nmpiped_%d", p_id);

	/* Create pipe if it does not exist */
	if (nmp_init(&nmp_obj, message.msg) == -1)
	{
		perror("Client: npm_init");
		return -1;
	}

	struct sockaddr_un addr;
	int sfd;
	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sfd == -1)
	{
		perror("socket");
		return -1;
	}

	/* Create client socket */
	/* Construct server address, and make the connection */
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SERVER_SOCKET_PATH, sizeof(addr.sun_path) - 1);

	if (connect(sfd, (struct sockaddr *)&addr,
							sizeof(struct sockaddr_un)) == -1)
	{
		perror("connect");
		return -1;
	}

	if (write(sfd, &message, sizeof(msq_elm_t)) != sizeof(msq_elm_t))
	{
		perror("write");
		return -1;
	}

	printf("Client: Sent message: '%s'\n", message.msg);

	/* open a file */
	printf("\nClient: The file '%s' is opening ...\n", f_name);

	if ((fp = fopen(f_name, "r")) == NULL)
	{
		printf("\nError opening the file: '%s' [Error string: '%s']\n",
					 f_name, strerror(errno));
		return -1;
	}

	char buff[NMP_MSG_LEN];
	while (fgets(buff, NMP_MSG_LEN, fp) != NULL)
	{
		nmp_obj.elm.len = message.len;
		strcpy(nmp_obj.elm.msg, buff);

		/* Send message in named pipe */
		if (nmp_send(&nmp_obj) == -1)
		{
			return -1;
		}

		printf("\nMessage sent to named pipe. Now sleeping for '%d' seconds...\n", n_secs);
		nanosleep((const struct timespec[]){{n_secs, 0L}}, NULL);
	}

	/* No more rows to send */
	printf("File content sent successfully\n.");
	free(fp);
	nmp_free(&nmp_obj);

	return 0;
}

/***************************************************************************/ /** 
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
  free(fp);

	exit(-1);
}