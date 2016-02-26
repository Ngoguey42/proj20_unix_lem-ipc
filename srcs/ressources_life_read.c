/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ressources_life_read.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 12:10:27 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 12:44:35 by ngoguey          ###   ########.fr       */
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
** Called if ressources already exist
**	1. Get semid_reslife
**	2. Loop until su.buf.sem_otime > 0 (Creator process doing semctl(SETVAL))
**	3. Down sepmaphore
*/

int			li_res_read_keeplock(t_env e[1], key_t key)
{
	union semun_t		su;
	struct semid_ds		data;

	e->semid_reslife = semget(key, 0, 0);
	if (e->semid_reslife == -1)
		return (ERRORNO("semget()"));
	ft_printf(":yel:Ressources found, checking its initialization...:eoc:\n");
	su.buf = &data;
	if (semctl(e->semid_reslife, 0, IPC_STAT, su) < 0)
		return (ERRORNO("semctl(..., IPC_STAT, ...)"));
	while (su.buf->sem_otime == 0)
	{
		ft_printf(":yel:Ressources found but not initialized, sleep...:eoc:\n");
		(void)usleep(500000);
		if (semctl(e->semid_reslife, 0, IPC_STAT, su) < 0)
			return (ERRORNO("semctl(..., IPC_STAT, ...)"));
	}
	ft_printf(":yel:Ressources found, up() for retreival...:eoc:\n");
	if (DOWN(e, 0))
		return (ERRORNO("down()"));
	e->msqid_pids = msgget(key, 0);
	if (e->msqid_pids == -1)
		return (UP(e, 0) + ERRORNO("msgget()"));
	return (0);
}
