/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ressources_life_shm_gameinfo.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 17:43:14 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 17:43:15 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <errno.h>
#include <signal.h>
#include <sys/shm.h>

int		li_shm_gameinfo_spawn(t_env e[1])
{
	struct s_shm_gameinfo	*map;

	if (e->param_nteam == -1)
		return (ERROR("nteam was not set in program parameters"));
	if (e->param_wboard == -1)
		return (ERROR("wboard was not set in program parameters"));
	e->shmid_gameinfo = shmget(
		e->key, sizeof(struct s_shm_gameinfo), IPC_CREAT | IPC_EXCL | 0666);
	if (e->shmid_gameinfo == -1)
		return (ERRORNO("shmget()"));
	map = shmat(e->shmid_gameinfo, NULL, 0);
	if (map == (void*)-1)
	{
		ERRORNOF("shmat()");
		if (shmctl(e->shmid_gameinfo, IPC_RMID, NULL))
			WARNNOF("shmctl()");
		return (1);
	}
	map->nteam = e->param_nteam;
	map->wboard = e->param_wboard;
	(void)shmdt(map);
	ft_printf("\t:yel:e->shmid_gameinfo spawned and set:eoc:\n");
	return (0);
}

int		li_shm_gameinfo_destroy(t_env e[1])
{
	if (shmctl(e->shmid_gameinfo, IPC_RMID, NULL))
		WARNNOF("shmctl()");
	else
		ft_printf("\t:yel:e->shmid_gameinfo destroyed:eoc:\n");
	return (0);
}

int		li_shm_gameinfo_read(t_env e[1])
{
	struct s_shm_gameinfo const		*map;

	e->shmid_gameinfo = shmget(e->key, sizeof(struct s_shm_gameinfo), 0);
	if (e->shmid_gameinfo == -1)
		return (ERRORNO("shmget()"));
	map = shmat(e->shmid_gameinfo, NULL, SHM_RDONLY);
	if (map == (void*)-1)
		return (ERRORNOF("shmat()"));
	if (e->param_nteam == -1)
		e->param_nteam = map->nteam;
	else if (map->nteam != e->param_nteam)
		return (ERRORF(
			"e->param_nteam does not match shm_gameinfo (%d vs %d)",
			e->param_nteam, map->nteam));
	if (e->param_wboard == -1)
		e->param_wboard = map->wboard;
	else if (map->wboard != e->param_wboard)
		return (ERRORF(
			"e->param_wboard does not match shm_gameinfo (%d vs %d)",
			e->param_wboard, map->wboard));
	(void)shmdt(map);
	ft_printf("\t:yel:e->shmid_gameinfo read and valid:eoc:\n");
	return (0);
}
