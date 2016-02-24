/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_control_resend_msq.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 19:22:13 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/24 19:58:13 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <errno.h>
#include <signal.h>
#include <sys/msg.h>

static bool		sendable(struct s_msg_pid const buf[1])
{
	return (buf->pid != getpid() && !kill(buf->pid, 0));
}

static int		send(t_env e[1], struct s_msg_pid buf[1], long sndtype)
{
	qprintf("\tResending\n");
	buf->mtype = sndtype;
	if (msgsnd(e->res_msqid, buf, sizeof(pid_t), IPC_NOWAIT))
		return (ERRORNO("msgsnd()"));
	return (0);
}

int				li_res_resend_msq(t_env e[1], int count[1])
{
	long				rcvtype;
	struct s_msg_pid	m[1];
	int					err;

	if (msgrcv(e->res_msqid, m, sizeof(pid_t), 0, IPC_NOWAIT) < 0)
		return (ERRORNO("msgrcv()"));
	rcvtype = m->mtype;
	*count = 0;
	qprintf("Dealing with pid=%d (self = %d) type=%d\n",
			m->pid, getpid(), m->mtype);
	if (sendable(m))
	{
		(*count)++;
		if (send(e, m, rcvtype + 1))
			return (ERROR(""));
	}
	while (1)
	{
		err = msgrcv(e->res_msqid, m, sizeof(pid_t), rcvtype, IPC_NOWAIT);
		if (err == -1 && (errno == ENOMSG || errno == EAGAIN))
			break ;
		if (err == -1)
			return (ERRORNO("msgrcv()"));
		qprintf("Dealing with pid=%d (self = %d) type=%d\n",
				m->pid, getpid(), m->mtype);
		if (sendable(m))
		{
			(*count)++;
			if (send(e, m, rcvtype + 1))
				return (ERROR(""));
		}
	}
	return (0);
}
