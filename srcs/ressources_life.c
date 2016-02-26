/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ressources_life.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 12:16:27 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 15:33:49 by ngoguey          ###   ########.fr       */
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

static int (*const g_spawn_seq[])() = {
	&li_shm_reslife_spawn,
	&li_msq_pids_spawn,
	&li_shm_nteam_spawn,
};

static int (*const g_destroy_seq[])() = {
	&li_shm_reslife_destroy,
	&li_msq_pids_destroy,
	&li_shm_nteam_destroy,
};

static int (*const g_read_seq[])() = {
	&li_shm_reslife_read,
	&li_msq_pids_read,
	&li_shm_nteam_read,
};

# define ASSERT1 (SEQ_NFUNC == SIZE_ARRAY(g_destroy_seq))
static char         g_assert1[1 - (ASSERT1 ? 0 : 1) * 2];
# define ASSERT2 (SEQ_NFUNC == SIZE_ARRAY(g_read_seq))
static char         g_assert2[1 - (ASSERT2 ? 0 : 1) * 2];
# define ASSERT3 (SEQ_NFUNC == SIZE_ARRAY(g_spawn_seq))
static char         g_assert3[1 - (ASSERT3 ? 0 : 1) * 2];
# define ASSERT4 (SEQ_NFUNC > 0)
static char         g_assert4[1 - (ASSERT4 ? 0 : 1) * 2];

# define BOUNDS (size_t const[2]){0, SEQ_NFUNC - 1}

static int		spawn_seq(t_env e[1])
{
    size_t		faulty_index[1];

    if (ft_call_sequence(g_spawn_seq, BOUNDS, faulty_index, e))
	{
		ERRORF("Spawn sequence failed at step %d", *faulty_index);
		ft_call_sequence(g_destroy_seq, (size_t const[2]){*faulty_index, 0},
						 faulty_index, e);
		return (1);
	}
	(void)g_assert1;
	(void)g_assert2;
	(void)g_assert3;
	(void)g_assert4;
	return (0);
}

static int		read_seq(t_env e[1])
{
    size_t		faulty_index[1];

    if (ft_call_sequence(g_read_seq, BOUNDS, faulty_index, e))
	{
		ERRORF("Read sequence failed at step %d", *faulty_index);
		return (1);
	}
	return (0);
}

/*
** Called at program start
*/

int				li_res_spawn_or_read(t_env e[1])
{
	e->key = ftok(LEMIPC_KEY_PATH, LEMIPC_KEY_VAL);
	if (e->key == -1)
		return (ERRORNO("ftok()"));
	e->semid_reslife = semget(e->key, 1, IPC_CREAT | IPC_EXCL | 0666);
	if (e->semid_reslife == -1 && errno != EEXIST)
		return (ERRORNO("semget(..., IPC_CREAT | IPC_EXCL, ...)"));
	if (e->semid_reslife == -1)
	{
		if (read_seq(e))
			return (ERROR(""));
	}
	else
	{
		if (spawn_seq(e))
			return (ERROR(""));
	}
	WARNF("Waiting before lock release");
	BREAK(e, 1);
	if (UP(e, 0))
		return (ERRORNO("up()"));
	return (0);
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
