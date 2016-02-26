/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ressources_life_msq_pids.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 14:28:50 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 15:22:46 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <errno.h>
#include <sys/msg.h>

int			li_msq_pids_spawn(t_env e[1])
{
	struct s_msg_pid const	m[1] = {{1, getpid()}};

	e->msqid_pids = msgget(e->key, IPC_CREAT | IPC_EXCL | 0666);
	if (e->msqid_pids == -1)
		return (ERRORNO("msgget()"));
	if (msgsnd(e->msqid_pids, m, sizeof(pid_t), IPC_NOWAIT))
	{
		ERRORNO("msgsnd()");
		if (msgctl(e->msqid_pids, IPC_RMID, NULL))
			WARNNOF("msgctl()");
		return (1);
	}
	ft_printf("\t:yel:e->msqid_pids spawned and pid pushed:eoc:\n");
	return (0);
}

int			li_msq_pids_destroy(t_env e[1])
{
	if (msgctl(e->msqid_pids, IPC_RMID, NULL))
		WARNNOF("msgctl()");
	else
		ft_printf("\t:yel:e->msqid_pids destroyed:eoc:\n");
	return (0);
}

int			li_msq_pids_read(t_env e[1])
{
	struct s_msg_pid const	m[1] = {{1, getpid()}};

	e->msqid_pids = msgget(e->key, 0);
	if (e->msqid_pids == -1)
		return (ERRORNO("msgget()"));
	if (msgsnd(e->msqid_pids, m, sizeof(pid_t), IPC_NOWAIT))
		return (ERRORNO("msgsnd()"));
	ft_printf("\t:yel:e->msqid_pids read and pid pushed:eoc:\n");
	return (0);
}
