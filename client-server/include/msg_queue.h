/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  msg_queue.h
 *
 * @brief Provides functions for the message queue communication
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun, Jul 21, 2019 23:36$
 */

#ifndef _MSG_QUEUE__H
#define _MSG_QUEUE__H 1

#define MSQ_LEN 30
#define QUEUE_PERMISSIONS 0666

typedef struct _msq_elm
{
    int     p_id;           /* client's process id              */
    int     len;            /* length in bytes of the msg       */
    char    msg[MSQ_LEN];   /* the message, i.e. pipe's name    */
} msq_elm_t;

int start_server(const char *f_name);
int start_client(const char *f_name, const int n_secs);

#endif /* _MSG_QUEUE__H */
