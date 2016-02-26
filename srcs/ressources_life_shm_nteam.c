/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ressources_life_shm_nteam.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 14:52:45 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 15:39:14 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <errno.h>
#include <signal.h>
#include <sys/shm.h>

int		li_shm_nteam_spawn(t_env e[1])
{
	int		*map;

	e->shmid_nteam = shmget(e->key, sizeof(int), IPC_CREAT | IPC_EXCL | 0666);
	if (e->shmid_nteam == -1)
		return (ERRORNO("shmget()"));
	map = shmat(e->shmid_nteam, NULL, 0);
	if (map == (void*)-1)
	{
		ERRORNOF("shmat()");
		if (shmctl(e->shmid_nteam, IPC_RMID, NULL))
			WARNNOF("shmctl()");
		return (1);
	}
	*map = e->param_nteam;
	(void)shmdt(map);
	ft_printf("\t:yel:e->shmid_nteam spawned and set:eoc:\n");
	return (0);
}

int		li_shm_nteam_destroy(t_env e[1])
{
	if (shmctl(e->shmid_nteam, IPC_RMID, NULL))
		WARNNOF("shmctl()");
	else
		ft_printf("\t:yel:e->shmid_nteam destroyed:eoc:\n");
	return (0);
}

int		li_shm_nteam_read(t_env e[1])
{
	int const		*map;

	e->shmid_nteam = shmget(e->key, sizeof(int), 0);
	if (e->shmid_nteam == -1)
		return (ERRORNO("shmget()"));
	map = shmat(e->shmid_nteam, NULL, SHM_RDONLY);
	if (map == (void*)-1)
		return (ERRORNOF("shmat()"));
	if (*map != e->param_nteam)
		return (ERRORF("e->param_nteam does not match shm_nteam (%d vs %d)",
					  e->param_nteam, *map));
	(void)shmdt(map);
	ft_printf("\t:yel:e->shmid_nteam read and valid:eoc:\n");
	return (0);
}
