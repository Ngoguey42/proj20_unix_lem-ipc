/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ressources_life_shm_board.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 17:57:41 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 18:05:31 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <errno.h>
#include <sys/shm.h>

int		li_shm_board_spawn(t_env e[1])
{
	size_t const nbytes = sizeof(int) * e->param_wboard * e->param_wboard;

	e->shmid_board = shmget(e->keygame, nbytes, IPC_CREAT | IPC_EXCL | 0666);
	if (e->shmid_board == -1)
		return (ERRORNO("shmget()"));
	e->shm_board = shmat(e->shmid_board, NULL, 0);
	if (e->shm_board == (void*)-1)
	{
		ERRORNOF("shmat()");
		if (shmctl(e->shmid_board, IPC_RMID, NULL))
			WARNNOF("shmctl()");
		return (1);
	}
	ft_printf("\t:yel:e->shmid_board spawned and mapped:eoc:\n");
	return (0);
}

int		li_shm_board_destroy(t_env e[1])
{
	if (shmctl(e->shmid_board, IPC_RMID, NULL))
		WARNNOF("shmctl()");
	else
		ft_printf("\t:yel:e->shmid_board destroyed:eoc:\n");
	return (0);
}

int		li_shm_board_read(t_env e[1])
{
	size_t const nbytes = sizeof(int) * e->param_wboard * e->param_wboard;

	e->shmid_board = shmget(e->keygame, nbytes, 0);
	if (e->shmid_board == -1)
		return (ERRORNO("shmget()"));
	if (e->shm_board == (void*)-1)
		return (ERRORNOF("shmat()"));
	ft_printf("\t:yel:e->shmid_board read:eoc:\n");
	return (0);
}
