/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:51:30 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/29 11:32:06 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <sys/sem.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int		game_loop(t_env e[1])
{
	while (!e->leave_game)
	{
		if (li_game_down(e))
		{
			if (errno == EINTR)
				break ;
			else
				return (ERRORNO(""));
		}
		/* T; */
		if (li_game_up(e))
			return (ERROR(""));
	}
	return (0);
}

int		main(int ac, char *av[])
{
	t_env	*e;

	srand(time(NULL));
	e = li_env();
	if (e == NULL)
		return (ERROR(""));
	if (li_env_init(e, ac, (char const *const *)av))
		return (ERROR(""));
	if (li_set_signals(e))
		return (ERROR(""));
	if (li_res_spawn_or_read(e))
		return (ERROR(""));
	ft_printf(":gre:Ressources retrieval ok!:eoc:\n");

	/* qprintf("READ... HIT ENTER\n"); */
	/* char c; */
	/* read(0, &c, 1); */
	(void)game_loop(e);

	if (li_res_destroy_or_defect(e))
		return (ERROR(""));
	return (0);
}
