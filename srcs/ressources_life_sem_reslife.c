/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ressources_life_sem_reslife.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 15:28:17 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 16:27:41 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <errno.h>
#include <signal.h>
#include <sys/shm.h>

/*
** res_sem (Ressources Semaphore) is used as a mutex for ressources
**      creation/destruction.
** *
** P() == DOWN() == DECREMENT == TAKE
** V() == UP() == INCREMENT == RELEASE
*/

#define _SEMBUFF_ARR(A,B,C) {.sem_num=(A),.sem_op=(B),.sem_flg=(C)}
#define SEMBUFF_ARR(A,B,C) (struct sembuf[]){_SEMBUFF_ARR(A,B,C)}

#define DOWN(e, flg) semop(e->semid_reslife, SEMBUFF_ARR(0, -1, flg), 1)
#define UP(e, flg) semop(e->semid_reslife, SEMBUFF_ARR(0, 1, flg), 1)

int		li_sem_reslife_spawn(t_env e[1])
{
	union semun_t		su;

	BREAK(e, 1);
	su.val = 1;
	ft_printf(":yel:Ressources not found, spawning them:eoc:\n");
	if (semctl(e->semid_reslife, 0, SETVAL, su) < 0)
		return (ERRORNO("semctl(..., SETVAL, ...)"));
	ft_printf("\t:yel:e->semid_reslife spawned & set (acquiring lock):eoc:\n");
	if (DOWN(e, IPC_NOWAIT))
	{
		if (errno == EAGAIN)
			return (ERROR("down(IPC_NOWAIT) should not have waited"));
		else
			return (ERRORNO("down()"));
	}
	return (0);
}

int		li_sem_reslife_destroy(t_env e[1])
{
	if (semctl(e->semid_reslife, 0, IPC_RMID, NULL))
		WARNNOF("semctl()");
	else
		ft_printf("\t:yel:e->semid_reslife destroyed:eoc:\n");
	return (0);
}

int		li_sem_reslife_read(t_env e[1])
{
	union semun_t		su;
	struct semid_ds		data;

	e->semid_reslife = semget(e->key, 0, 0);
	if (e->semid_reslife == -1)
		return (ERRORNO("semget()"));
	ft_printf(":yel:Ressources found, checking its initialization...:eoc:\n");
	su.buf = &data;
	while (1)
	{
		if (semctl(e->semid_reslife, 0, IPC_STAT, su) < 0)
			return (ERRORNO("semctl(..., IPC_STAT, ...)"));
		if (su.buf->sem_otime != 0)
			break ;
		ft_printf(":yel:Ressources found but not initialized, sleep...:eoc:\n");
		(void)usleep(500000);
	}
	ft_printf("\t:yel:e->semid_reslife ready, (acquiring lock):eoc:\n");
	if (DOWN(e, 0))
		return (ERRORNO("down()"));
	return (0);
}
