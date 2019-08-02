/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  server_proc.c
 *
 * @brief Implements the functionality for the server process
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun21, Jul 21, 2019 23:35$
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <signal.h>
#include <errno.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "server_proc.h"
#include "nm_pipe.h"
#include "sh_mem.h"
#include "sh_sem.h"
#include "rec_proc.h"
#include "f_ser.h"

void 	sig_handler					(int signum);
int 	handle_sock_clients	(const int sfd);
void 	free_resources			();
int 	handle_nmp_msg			();

sem_t 			*writer_sem;
sem_t 			*reader_sem;
shm_elm_t 	*shm_ptr;
nm_pipe_t 	nmp_elem;

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

	int 								shm_fd;
	int 								sfd;
	pid_t 							r_pid;
	struct sockaddr_un 	addr;

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
		return -1;
	}

	if (listen(sfd, MAX_MESSAGES) == -1)
	{
		perror("listen");
		return -1;
	}

	free_resources();

	/* Semaphor and shared memory */
	writer_sem = sem_open(WRITER_SEM_NAME, O_RDWR | O_CREAT | SEM_PERMISSIONS, 0);
	reader_sem = sem_open(READER_SEM_NAME, O_RDWR | O_CREAT | SEM_PERMISSIONS, 0);

	if (sem_post(writer_sem) == -1)
	{
		perror("sem_post: writer_sem");
	}
	if (sem_post(reader_sem) == -1)
	{
		perror("sem_post: writer_sem");
	}

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
	shm_ptr = mmap(0, sizeof(shm_elm_t), PROT_READ | PROT_WRITE,
								 MAP_SHARED, shm_fd, 0);
	
	if (shm_ptr == MAP_FAILED)
	{
		perror("mmap");
		return -1;
	}
	shm_ptr->state = SHM_EMPTY;

	/* Create record process */
	r_pid = fork();

	if (r_pid < 0)
	{
		perror("fork");
		return -1;
	}

	if (r_pid == 0)
	{
		if (handle_rec(f_name, shm_ptr, reader_sem) == -1)
		{
			return -1;
		}
	}

	if (handle_sock_clients(sfd) == -1)
	{
		return -1;
	}

	return 0;
}

/***************************************************************************/ /** 
 * @brief Clears semaphore and shared memory resources
 *
 * @param[in] signum - The signal number
 ******************************************************************************/
void free_resources()
{
	sem_free();
	shm_free();
}

/***************************************************************************/ /** 
 * @brief Handles the sockets clients
 *
 * @retval -1 in case an error was occurred
 * @retval 	0 if no error occurred
 ******************************************************************************/
int handle_sock_clients(const int sfd)
{
	int cfd;
	msq_elm_t message;

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
		if (nmp_init(&nmp_elem, message.msg) == -1)
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
			if (handle_nmp_msg() == -1)
			{
				return -1;
			}
		}
	}

	return 0;
}

/***************************************************************************/ /** 
 * @brief Writes the information received from the named pipe in
 * the shared memory
 *
 * @retval -1 in case an error was occurred
 * @retval 	0 if no error occurred
 ******************************************************************************/
int handle_nmp_msg()
{
	printf("Connection handler process created...\n");

	while (1)
	{
		/* Receive information from pipe */
		if (nmp_recv(&nmp_elem) == -1)
		{
			perror("Failed to read from pipe.\n");
			return -1;
		}

		while (1)
		{
			if (shm_ptr->state == SHM_EMPTY)
			{
				/* Write to shared memory*/
				sem_wait(writer_sem);
				shm_write(shm_ptr, nmp_elem.elm.msg);
				sem_post(writer_sem);
				break;
			}
		}
	}

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
	sem_close(writer_sem);
	sem_close(reader_sem);
	sem_free();

	/* For the shared memory */
	shm_unlink(SHM_NAME);
	shm_free();

	exit(0);
}