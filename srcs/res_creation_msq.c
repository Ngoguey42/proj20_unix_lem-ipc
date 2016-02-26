/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_creation_msq.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 20:09:12 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 11:52:43 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <errno.h>
#include <signal.h>
#include <sys/msg.h>

/*
** This message queue contains all the active pid
**	this is used to keep track of alive processes
*/

static bool		sendable(struct s_msg_pid const buf[1])
{
	return (buf->pid != getpid() && !kill(buf->pid, 0));
}

static int		send(
	t_env e[1], struct s_msg_pid buf[1], long sndtype, int count[1])
{
	qprintf("\tResending\n");
	(*count)++;
	buf->mtype = sndtype;
	if (msgsnd(e->msqid_pids, buf, sizeof(pid_t), IPC_NOWAIT))
		return (ERRORNO("msgsnd()"));
	return (0);
}

int				li_res_resend_msq(t_env e[1], int count[1])
{
	long				rcvtype;
	struct s_msg_pid	m[1];
	int					err;

	if (msgrcv(e->msqid_pids, m, sizeof(pid_t), 0, IPC_NOWAIT) < 0)
		return (ERRORNO("msgrcv()"));
	rcvtype = m->mtype;
	*count = 0;
	qprintf("Dealing with pid=%d (self = %d) type=%d\n",
			m->pid, getpid(), m->mtype);
	if (sendable(m))
		if (send(e, m, rcvtype + 1, count))
			return (ERROR(""));
	while (1)
	{
		err = msgrcv(e->msqid_pids, m, sizeof(pid_t), rcvtype, IPC_NOWAIT);
		if (err == -1 && (errno == ENOMSG || errno == EAGAIN))
			break ;
		if (err == -1)
			return (ERRORNO("msgrcv()"));
		qprintf("Dealing with pid=%d (self = %d) type=%d\n",
				m->pid, getpid(), m->mtype);
		if (sendable(m))
			if (send(e, m, rcvtype + 1, count))
				return (ERROR(""));
	}
	return (0);
}
