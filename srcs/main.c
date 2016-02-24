/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:51:30 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/24 12:43:35 by ngoguey          ###   ########.fr       */
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
		return (ERROR("li_env()"));
	li_env_init(e);
	if (li_set_signals(e))
		return (ERROR(""));


	qprintf("READ...\n");
	char c;
	read(0, &c, 1);
	/* while (1); */

	return 0;

	assert(ac > 1);
	int const	id = ft_atoi(av[1]);

	qprintf("id: (%d)\n", id);

	e->key = ftok(LEMIPC_KEY_PATH, LEMIPC_KEY_VAL);

	if (e->key == -1)
		return (ERRORNO("ftok"));
	e->semid = semget(e->key, 1, IPC_CREAT | SEM_A | SEM_R);

	qprintf("key(%u) semgrp(%d)\n", e->key, e->semid);


	while(1);
	(void)ac;
	return (0);
}
