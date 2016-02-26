/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ressources_life_spawn.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 12:10:25 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 14:34:45 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <errno.h>
#include <signal.h>
#include <sys/shm.h>

int		li_shm_nteam_spawn(t_env e[1])
{
	e->shmid_nteam = shmget(e->key, sizeof(bool), IPC_CREAT | IPC_EXCL | 0666);
	if (e->shmid_nteam == -1)
		return (ERRORNO("shmget()"));
	ft_printf("\t:yel:e->shmid_nteam spawned:eoc:\n");
	return (0);
}

int		li_shm_nteam_destroy(t_env e[1])
{
	if (shmctl(e->shmid_nteam, IPC_RMID, NULL))
		ERRORNO("shmctl()");
	else
		ft_printf("\t:yel:e->shmid_nteam destroyed:eoc:\n");
	return (0);
}

int		li_shm_nteam_read(t_env e[1])
{
	(void)e;
	return (0);
}
