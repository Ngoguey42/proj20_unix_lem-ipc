/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 11:52:48 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/24 12:43:27 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void handler(int signum)
{
	t_env *const	e = li_env();


	T;
	qprintf("signum: %d\n", signum);

	_exit(EXIT_FAILURE);
}

int		li_set_signals(t_env e[1])
{
	struct sigaction	sa[1];

	sa->sa_handler = handler;
	if (sigemptyset(&sa->sa_mask))
		return (ERROR("sigemptyset()"));
	sa->sa_flags = SA_RESTART;
	if (sigaction(SIGINT, sa, NULL))
		return (ERROR("sigaction(SIGINT, ...)"));
	if (sigaction(SIGQUIT, sa, NULL))
		return (ERROR("sigaction(SIGQUIT, ...)"));



	return (0);
}
