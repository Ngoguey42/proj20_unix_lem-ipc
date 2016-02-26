/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ressources_life_spawn.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 12:10:25 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 12:12:19 by ngoguey          ###   ########.fr       */
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

/*
** Called if ressources do not exist
**	1. Set value to 1
**	2. Down semaphore
*/

int			li_res_spawn(t_env e[1], key_t key)
{
	union semun_t		su;

	BREAK(e, 1);
	su.val = 1;
	if (semctl(e->semid_reslife, 0, SETVAL, su) < 0)
		return (ERRORNO("semctl(..., SETVAL, ...)"));
	ft_printf(":yel:Ressources not found, up() for creation...:eoc:\n");
	if (DOWN(e, IPC_NOWAIT))
	{
		if (errno == EAGAIN)
			return (ERROR("down(IPC_NOWAIT) should not have waited"));
		else
			return (ERRORNO("down()"));
	}
	e->msqid_pids = msgget(key, IPC_CREAT | IPC_EXCL | 0666);
	if (e->msqid_pids == -1)
	{
		UP(e, 0);
		return (ERRORNO("msgget()"));
	}
	return (0);
}
