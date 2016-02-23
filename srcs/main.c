/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:51:30 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/23 17:57:54 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <sys/sem.h>
#include <errno.h>
#include <string.h>

int							main(int ac, char *av[])
{
	t_env	e[1];


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
