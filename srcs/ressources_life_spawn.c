/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ressources_life_spawn.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 12:10:25 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 12:49:35 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <errno.h>
#include <signal.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/shm.h>

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

/*
** Called if ressources do not exist
**	1. Set value to 1
**	2. Down semaphore
*/

static int	spawn_phase3(t_env e[1], key_t key)
{
	e->shmid_nteam = shmget(key, sizeof(bool), IPC_CREAT | IPC_EXCL);
	if (e->shmid_nteam == -1)
		return (ERRORNO("shmget()"));
	ft_printf("\t:yel:e->shmid_nteam spawned:eoc:\n");
	if (0)
	{
		if (shmctl(e->shmid_nteam, IPC_RMID, NULL))
			ERRORNO("shmctl()");
		return (ERROR(""));
	}
	(void)e;
	(void)key;
	return (0);
}

static int	spawn_phase2(t_env e[1], key_t key)
{
	e->msqid_pids = msgget(key, IPC_CREAT | IPC_EXCL | 0666);
	if (e->msqid_pids == -1)
		return (ERRORNO("msgget()"));
	ft_printf("\t:yel:e->msqid_pids spawned:eoc:\n");
	if (spawn_phase3(e, key))
	{
		if (msgctl(e->msqid_pids, IPC_RMID, NULL))
			ERRORNO("msgctl()");
		return (ERROR(""));
	}
	return (0);
}

int			li_res_spawn_keeplock(t_env e[1], key_t key)
{
	union semun_t		su;

	BREAK(e, 1);
	su.val = 1;
	ft_printf(":yel:Ressources not found, spawning them:eoc:\n");
	if (semctl(e->semid_reslife, 0, SETVAL, su) < 0)
		return (ERRORNO("semctl(..., SETVAL, ...)"));
	ft_printf("\t:yel:e->semid_reslife spawned (acquiring lock):eoc:\n");
	if (DOWN(e, IPC_NOWAIT))
	{
		if (errno == EAGAIN)
			return (ERROR("down(IPC_NOWAIT) should not have waited"));
		else
			return (ERRORNO("down()"));
	}
	if (spawn_phase2(e, key))
	{
		UP(e, 0);
		return (ERROR(""));
	}
	return (0);
}
