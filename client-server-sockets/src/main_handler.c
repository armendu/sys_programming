/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  main_handler.c
 *
 * @brief Implements the functionality for communicating with message queues
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun21, Jul 21, 2019 23:35$
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/un.h>
#include <sys/socket.h>

#include "main_handler.h"
#include "nm_pipe.h"
#include "sh_mem.h"
#include "sh_sem.h"
#include "rec_handler.h"
#include "f_ser.h"

void sig_handler(int signum);

sem_t *sem;
shm_elm_t *shm_ptr;

/***************************************************************************/ /** 
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
int start_server(const char *f_name)
{
	signal(SIGINT, sig_handler);
	printf("Server is running. Waiting for clients...\n");

	msq_elm_t 					message;
	nm_pipe_t 					nmp_obj;
	struct sockaddr_un 	addr;

	int shm_fd;
	int sfd;
	int cfd;

	sfd = socket(AF_UNIX, SOCK_STREAM, 0);

	/* Construct server socket address, bind socket to it,
	and make this a listening socket */
	if (remove(SERVER_SOCKET_PATH) == -1 && errno != ENOENT)
	{
		return -1;
	}

	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SERVER_SOCKET_PATH, sizeof(addr.sun_path) - 1);

	if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
	{
		perror("bind");
	}

	if (listen(sfd, MAX_MESSAGES) == -1)
	{
		perror("listen");
	}

	/* Clear semaphore and shared memory */
	sem_free();
	shm_free();

	/* Semaphor and shared memory */
	sem = sem_open(SEM_NAME, O_RDWR | O_CREAT | SEM_PERMISSIONS, 0);

	shm_fd = shm_open(SHM_NAME, O_RDWR | O_CREAT | SHM_PERMISSIONS, 0);

	if (shm_fd == -1)
	{
		perror("shm_open");
		return -1;
	}

	/* configure the size of the shared memory object */
	if (ftruncate(shm_fd, sizeof(shm_elm_t)) == -1)
	{
		perror("ftruncate");
		return -1;
	}

	/* memory map the shared memory object */
	shm_ptr = mmap(0, sizeof(shm_elm_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	
	if (shm_ptr == MAP_FAILED)
	{
		perror("mmap");
		return -1;
	}
	shm_ptr->state = SHM_EMPTY;

	/* Create record process */
	pid_t r_pid;
	r_pid = fork();

	if (r_pid < 0)
	{
		perror("fork");
		return -1;
	}

	if (r_pid == 0)
	{
		if (handle_recording(f_name, shm_ptr) == -1)
		{
			return -1;
		}
	}

	while (1)
	{
		cfd = accept(sfd, NULL, NULL);
		if (cfd == -1)
		{
			perror("accept");
		}

		/* Transfer data from connected socket to stdout until EOF */
		if (read(cfd, &message, sizeof(msq_elm_t)) <= 0)
		{
			perror("read");
			return -1;
		}

		/* Create pipe if it does not exist */
		if (nmp_init(&nmp_obj, message.msg) == -1)
		{
			printf("Failed to create pipe\n");
			return -1;
		}

		/* Create connection handler process */
		pid_t pid;
		pid = fork();

		if (pid < 0)
		{
			perror("fork");
			return -1;
		}

		if (pid == 0)
		{
			printf("Connection handler process created...\n");

			while (1)
			{
				/* Receive information from pipe */
				if (nmp_recv(&nmp_obj) == -1)
				{
					perror("Failed to read from pipe.\n");
					return -1;
				}

				/* Write to shared memory*/
				sem_post(sem);
				if (shm_ptr->state == SHM_EMPTY)
				{
					shm_write(shm_ptr, nmp_obj.elm.msg);
				}
				/**/
				sem_wait(sem);
			}
		}
	}

	return 0;
}

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
{
	signal(SIGINT, sig_handler);
	printf("Client is running..\n");

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
		nmp_obj.elm.len = message.len;
		strcpy(nmp_obj.elm.msg, buff);

		printf("Successfully got message '%s'\n", buff);

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
	fflush(stdout);

	/* For the semaphore */
	sem_close(sem);
	sem_free();

	/* For the shared memory */
	shm_unlink(SHM_NAME);
	shm_free();

	exit(0);
}