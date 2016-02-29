/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_reslife_lock.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 11:37:30 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/29 11:37:43 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <sys/sem.h>
#include <errno.h>

/*
** P() == DOWN() == DECREMENT == TAKE
** V() == UP() == INCREMENT == RELEASE
*/

#define _SEMBUFF_ARR(A,B,C) {.sem_num=(A),.sem_op=(B),.sem_flg=(C)}
#define SEMBUFF_ARR(A,B,C) (struct sembuf[]){_SEMBUFF_ARR(A,B,C)}

#define DOWN(e, flg) semop(e->semid_reslife, SEMBUFF_ARR(0, -1, flg), 1)
#define UP(e, flg) semop(e->semid_reslife, SEMBUFF_ARR(0, 1, flg), 1)

int			li_reslife_down(t_env e[1])
{
	if (DOWN(e, 0))
	{
		if (errno == EINTR)
			return (1);
		else
			return (ERRORNO("down()"));
	}
	return (0);
}

int			li_reslife_down_loop(t_env e[1])
{
	int		i;

	i = 0;
	while (1)
	{
		if (DOWN(e, 0))
		{
			if (errno == EINTR && i++ < 3)
				continue ;
			else if (errno == EINTR)
				return (ERRORNO("Abording down() after 3 attempts"));
			else
				return (ERRORNO("down()"));
		}
		else
			break ;
	}
	return (0);
}

int			li_reslife_up(t_env e[1])
{
	return (UP(e, 0));
}
