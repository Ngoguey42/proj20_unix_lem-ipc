/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 20:09:04 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/24 20:09:04 by ngoguey          ###   ########.fr       */
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

#define DOWN(e, flg) semop(e->res_semid, SEMBUFF_ARR(0, -1, flg), 1)
#define UP(e, flg) semop(e->res_semid, SEMBUFF_ARR(0, 1, flg), 1)

/*
** Called if ressources do not exist
**	1. Set value to 1
**	2. Down semaphore
*/

static int		make_and_keep_controls(t_env e[1])
{
	union semun_t		su;

	BREAK(e, 1);
	su.val = 1;
	if (semctl(e->res_semid, 0, SETVAL, su) < 0)
		return (ERRORNO("semctl(..., SETVAL, ...)"));
	ft_printf(":yel:Ressources not found, up() for creation...:eoc:\n");
	if (DOWN(e, IPC_NOWAIT))
	{
		if (errno == EAGAIN)
			return (ERROR("down(IPC_NOWAIT) should not have waited"));
		else
			return (ERRORNO("down()"));
	}
	e->res_msqid = msgget(e->key, IPC_CREAT | IPC_EXCL | 0666);
	if (e->res_msqid == -1)
	{
		UP(e, 0);
		return (ERRORNO("msgget()"));
	}
	return (0);
}

/*
** Called if ressources already exist
**	1. Get res_semid
**	2. Loop until su.buf.sem_otime > 0 (Creator process doing semctl(SETVAL))
**	3. Down sepmaphore
*/

static int		acquire_controls(t_env e[1])
{
	union semun_t		su;
	struct semid_ds		data;

	e->res_semid = semget(e->key, 0, 0);
	if (e->res_semid == -1)
		return (ERRORNO("semget()"));
	ft_printf(":yel:Ressources found, checking its initialization...:eoc:\n");
	su.buf = &data;
	if (semctl(e->res_semid, 0, IPC_STAT, su) < 0)
		return (ERRORNO("semctl(..., IPC_STAT, ...)"));
	while (su.buf->sem_otime == 0)
	{
		ft_printf(":yel:Ressources found but not initialized, sleep...:eoc:\n");
		(void)usleep(500000);
		if (semctl(e->res_semid, 0, IPC_STAT, su) < 0)
			return (ERRORNO("semctl(..., IPC_STAT, ...)"));
	}
	ft_printf(":yel:Ressources found, up() for retreival...:eoc:\n");
	if (DOWN(e, 0))
		return (ERRORNO("down()"));
	e->res_msqid = msgget(e->key, 0);
	if (e->res_msqid == -1)
		return (UP(e, 0) + ERRORNO("msgget()"));
	return (0);
}

static int		common_operations(t_env e[1])
{
	struct s_msg_pid const	m[1] = {{1, getpid()}};

	if (msgsnd(e->res_msqid, m, sizeof(pid_t), IPC_NOWAIT))
		return (ERRORNO("msgsnd()"));
	return (0);
}

/*
** Called at program start
*/

int				li_res_retrieve(t_env e[1])
{
	int		err;

	e->res_semid = semget(e->key, 1, IPC_CREAT | IPC_EXCL | 0666);
	if (e->res_semid == -1 && errno != EEXIST)
		return (ERRORNO("semget(..., IPC_CREAT | IPC_EXCL, ...)"));
	if (e->res_semid == -1)
	{
		if (acquire_controls(e))
			return (ERROR(""));
	}
	else
	{
		if (make_and_keep_controls(e))
			return (ERROR(""));
	}
	BREAK(e, 1);
	err = common_operations(e);
	if (UP(e, 0))
		return (ERRORNO("up()"));
	return (err);
}

/*
** Called at program end
*/

int				li_res_quit(t_env e[1])
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
