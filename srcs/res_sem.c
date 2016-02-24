/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_sem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 14:32:34 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/24 16:36:55 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <errno.h>
#include <sys/sem.h>

/*
** res_sem (Ressources Semaphore) is used as a mutex for ressources
**		creation/destruction.
** *
** P() == DOWN() == DECREMENT == TAKE
** V() == UP() == INCREMENT == RELEASE
*/

static int		down(t_env e[1], short flg)
{
	struct sembuf	op[1];

	op->sem_num = 0;
	op->sem_op = -1;
	op->sem_flg = flg;
	return (semop(e->res_semid, op, 1));
}

static int		up(t_env e[1], short flg)
{
	struct sembuf	op[1];

	op->sem_num = 0;
	op->sem_op = 1;
	op->sem_flg = flg;
	return (semop(e->res_semid, op, 1));
}

/*
** Called if ressources do not exist
**	1. Set value to 1
**	2. Down sepmaphore
*/

static int		make_ressources(t_env e[1])
{
	union semun_t		su;

	BREAK(e, 1);
	su.val = 1;
	if (semctl(e->res_semid, 0, SETVAL, su) < 0)
		return (ERRORNO("semctl(..., SETVAL, ...)"));
	ft_printf(":yel:Ressources not found, up() for creation...:eoc:\n");
	if (down(e, IPC_NOWAIT))
	{
		if (errno == EAGAIN)
			return (ERROR("down(IPC_NOWAIT) should not have waited"));
		else
			return (ERRORNO("down()"));
	}
	return (0);
}

/*
** Called if ressources already exist
**	1. Get res_semid
**	2. Loop until su.buf.sem_otime > 0 (Creator process doing semctl(SETVAL))
**	3. Down sepmaphore
*/

static int		read_ressources(t_env e[1])
{
	union semun_t		su;
	struct semid_ds		data;

	e->res_semid = semget(e->key, 0, 0);
	if (e->res_semid == -1)
		return (ERRORNO("semget()"));
	ft_printf(":yel:Ressources found, checking its initialization...:eoc:\n");
	su.buf = &data;
	if (semctl(e->res_semid, 0, IPC_STAT, su) < 0)
		return (ERROR("semctl(..., IPC_STAT, ...)"));
	while (su.buf->sem_otime == 0)
	{
		ft_printf(":yel:Ressources found but not initialized, sleep...:eoc:\n");
		(void)usleep(500000);
		if (semctl(e->res_semid, 0, IPC_STAT, su) < 0)
			return (ERROR("semctl(..., IPC_STAT, ...)"));
	}
	ft_printf(":yel:Ressources found, up() for retreival...:eoc:\n");
	if (down(e, 0))
		return (ERRORNO("down()"));
	return (0);
}

int				li_res_retrieve(t_env e[1])
{
	e->key = ftok(LEMIPC_KEY_PATH, LEMIPC_KEY_VAL);
	if (e->key == -1)
		return (ERRORNO("ftok()"));
	e->res_semid = semget(e->key, 1, IPC_CREAT | IPC_EXCL | 0666);
	if (e->res_semid == -1 && errno != EEXIST)
		return (ERRORNO("semget(..., IPC_CREAT | IPC_EXCL, ...)"));
	if (e->res_semid == -1)
	{
		if (read_ressources(e))
			return (ERROR(""));
	}
	else
	{
		if (make_ressources(e))
			return (ERROR(""));
	}
	BREAK(e, 1);
	if (up(e, 0))
		return (ERRORNO("up()"));
	return (0);
}
