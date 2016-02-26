/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ressources_life.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 12:16:27 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 12:37:23 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <errno.h>
#include <signal.h>
#include <sys/sem.h>
#include <sys/msg.h>

/*
** res_sem (Ressources Semaphore) is used as a mutex for ressources
**		creation/destruction.
** *
** P() == DOWN() == DECREMENT == TAKE
** V() == UP() == INCREMENT == RELEASE
*/

#define _SEMBUFF_ARR(A,B,C) {.sem_num=(A),.sem_op=(B),.sem_flg=(C)}
#define SEMBUFF_ARR(A,B,C) (struct sembuf[]){_SEMBUFF_ARR(A,B,C)}

#define DOWN(e, flg) semop(e->semid_reslife, SEMBUFF_ARR(0, -1, flg), 1)
#define UP(e, flg) semop(e->semid_reslife, SEMBUFF_ARR(0, 1, flg), 1)

static int		shared_operations(t_env e[1])
{
	struct s_msg_pid const	m[1] = {{1, getpid()}};

	if (msgsnd(e->msqid_pids, m, sizeof(pid_t), IPC_NOWAIT))
		return (ERRORNO("msgsnd()"));
	return (0);
}

/*
** Called at program start
*/

int				li_res_spawn_or_read(t_env e[1])
{
	int			err;
	key_t const	key = ftok(LEMIPC_KEY_PATH, LEMIPC_KEY_VAL);

	if (key == -1)
		return (ERRORNO("ftok()"));
	e->semid_reslife = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
	if (e->semid_reslife == -1 && errno != EEXIST)
		return (ERRORNO("semget(..., IPC_CREAT | IPC_EXCL, ...)"));
	if (e->semid_reslife == -1)
	{
		if (li_res_read_keeplock(e, key))
			return (ERROR(""));
	}
	else
	{
		if (li_res_spawn_keeplock(e, key))
			return (ERROR(""));
	}
	BREAK(e, 1);
	err = shared_operations(e);
	if (UP(e, 0))
		return (ERRORNO("up()"));
	return (err);
}

/*
** Called at program end
*/

int				li_res_destroy_or_defect(t_env e[1])
{
	int					count[1];
	int					err;

	if (DOWN(e, 0))
		return (ERRORNO("down()"));
	err = li_res_resend_msq(e, count);
	if (*count == 0)
	{
	}
	if (UP(e, 0))
		return (ERRORNO("up()"));
	return (err);
}
