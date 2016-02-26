/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ressources_life_shm_board.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 17:57:41 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 19:54:10 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <errno.h>
#include <sys/shm.h>
#include <time.h>
#include <stdlib.h>

static int	rejoin(t_env e[1], int ncells)
{
	int		cells_left;
	int		i;
	int		seed;
	int		j;

	cells_left = 0;
	i = 0;
	while (i < ncells)
		if (e->shm_board[i++] == -1)
			cells_left++;
	if (cells_left == 0)
		return (ERROR("Board is full"));
	seed = rand() % cells_left;
	i = 0;
	j = 0;
	while (i < ncells)
	{
		if (e->shm_board[i] == -1)
			if (j++ == seed)
			{
				e->shm_board[i] = e->team_id;
				e->pos = (t_vec2i){i % e->param_wboard, i / e->param_wboard};
				break ;
			}
		i++;
	}
	FT_ASSERT(i < ncells);
	return (0);
}

int		li_shm_board_spawn(t_env e[1])
{
	size_t const	nbytes = sizeof(int) * e->param_wboard * e->param_wboard;
	int				i;

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
	i = 0;
	while ((size_t)i < nbytes / sizeof(int))
		e->shm_board[i++] = -1;
	(void)rejoin(e, nbytes / sizeof(int));
	ft_printf("\t:yel:e->shmid_board spawned, mapped, initialized and rejoinded"
			  "at pos {%d, %d}:eoc:\n", e->pos.x, e->pos.y);
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
	e->shm_board = shmat(e->shmid_board, NULL, 0);
	if (e->shm_board == (void*)-1)
		return (ERRORNOF("shmat()"));
	if (rejoin(e, nbytes / sizeof(int)))
		return (ERROR(""));
	ft_printf("\t:yel:e->shmid_board read, mapped and rejoined"
			  "at pos {%d, %d}:eoc:\n", e->pos.x, e->pos.y);
	return (0);
}
