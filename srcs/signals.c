/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 12:03:40 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 20:01:23 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void handler(int signum)
{
	t_env *const	e = li_env();

	qprintf("signum: %d\n", signum);
	e->leave_game = true;
	/* _exit(EXIT_FAILURE); //TODO : remove */
	return ;
}

int		li_set_signals(t_env e[1])
{
	struct sigaction	sa[1];

	(void)e;
	sa->sa_handler = handler;
	if (sigemptyset(&sa->sa_mask))
		return (ERROR("sigemptyset()"));
	sa->sa_flags = SA_RESTART;
	/* BREAK(e, 1); */
	if (sigaction(SIGINT, sa, NULL))
		return (ERROR("sigaction(SIGINT, ...)"));
	if (sigaction(SIGQUIT, sa, NULL))
		return (ERROR("sigaction(SIGQUIT, ...)"));
	return (0);
}
