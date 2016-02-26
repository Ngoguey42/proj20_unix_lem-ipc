/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ressources_life_sem_game.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 17:44:15 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 17:57:47 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <errno.h>
#include <sys/sem.h>

int		li_sem_game_spawn(t_env e[1])
{
	union semun_t		su;

	e->semid_game = semget(e->keygame, 1, IPC_CREAT | IPC_EXCL | 0666);
	if (e->semid_game == -1)
		return (ERRORNO("semget(..., IPC_CREAT | IPC_EXCL, ...)"));
	su.val = 1;
	if (semctl(e->semid_game, 0, SETVAL, su) < 0)
		return (ERRORNO("semctl(..., SETVAL, ...)"));
	ft_printf("\t:yel:e->semid_game spawned and set:eoc:\n");
	return (0);
}

int		li_sem_game_destroy(t_env e[1])
{
	if (semctl(e->semid_game, 0, IPC_RMID, NULL))
		WARNNOF("semctl()");
	else
		ft_printf("\t:yel:e->semid_game destroyed:eoc:\n");
	return (0);
}

int		li_sem_game_read(t_env e[1])
{
	e->semid_game = semget(e->keygame, 0, 0);
	if (e->semid_game == -1)
		return (ERRORNO("semget()"));
	ft_printf("\t:yel:e->semid_game read:eoc:\n");
	return (0);
}
