/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:51:30 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 11:51:58 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <sys/sem.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int		main(int ac, char *av[])
{
	t_env	*e;

	e = li_env();
	if (e == NULL)
		return (ERROR(""));
	if (li_env_init(e, ac, (char const *const *)av))
		return (ERROR(""));
	/* BREAK(e, 1); */
	if (li_set_signals(e))
		return (ERROR(""));
	if (li_res_spawn_or_read(e))
		return (ERROR(""));
	ft_printf(":gre:Ressources retrieval ok!:eoc:\n");


	qprintf("READ... HIT ENTER\n");
	char c;
	read(0, &c, 1);

	if (li_res_destroy_or_defect(e))
		return (ERROR(""));
	return (0);
}
