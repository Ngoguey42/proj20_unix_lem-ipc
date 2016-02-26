/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ressources_life_spawn.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 12:10:25 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 14:33:04 by ngoguey          ###   ########.fr       */
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

static int (*const g_spawn_seq[])() = {
	&li_msq_pids_spawn,
	&li_shm_nteam_spawn,
};

static int (*const g_destroy_seq[])() = {
	&li_msq_pids_destroy,
	&li_shm_nteam_destroy,
};

static int (*const g_read_seq[])() = {
	&li_msq_pids_read,
	&li_shm_nteam_read,
};

# define ASSERT1 (SIZE_ARRAY(g_spawn_seq) == SIZE_ARRAY(g_destroy_seq))
static char			g_assert1[1 - (ASSERT1 ? 0 : 1) * 2];
# define ASSERT2 (SIZE_ARRAY(g_spawn_seq) == SIZE_ARRAY(g_read_seq))
static char			g_assert2[1 - (ASSERT2 ? 0 : 1) * 2];
# define ASSERT3 (SIZE_ARRAY(g_spawn_seq) > 0)
static char			g_assert3[1 - (ASSERT3 ? 0 : 1) * 2];

# define NFUN SIZE_ARRAY(g_spawn_seq)
# define BOUNDS (size_t const[2]){0, NFUN - 1}

int			li_res_spawn_keeplock(t_env e[1])
{
	union semun_t		su;
	size_t				faulty_index[1];

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
	if (ft_call_sequence(g_spawn_seq, BOUNDS, faulty_index, e))
	{
		ft_call_sequence(g_destroy_seq, (size_t const[2]){*faulty_index, 0},
						 faulty_index, e);
		return (ERROR(""));
	}
	(void)g_assert1;
	(void)g_assert2;
	(void)g_assert3;
	return (0);
}
