/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 12:33:54 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/24 17:18:12 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "ft_arg.h"

#include <stdlib.h>

t_env		*li_env(void)
{
	static t_env	*e = NULL;

	if (e == NULL)
		e = malloc(sizeof(*e));
	return (e);
}

#define BAD_EXPECT "./lemipc option -%c takes an argument of type %s"
#define MISSING_EXPECT "./lemipc missing argument after option -%c"

static int	args(t_env e[1], t_arg_parser p[1])
{
	enum e_arg	a;
	enum e_arg	expect;
	char		awaiting;

	expect = FTARG_NONE;
	awaiting = '\0';
	while ((a = ft_arg_next(p, expect)) != FTARG_NONE)
	{
		if (awaiting != '\0' && a != expect)
			return (ERRORF(BAD_EXPECT, awaiting, ft_arg_name(expect)));
		if (awaiting == 'b')
		{
			awaiting = '\0';
			e->brk = p->i;
			ft_printf("BreakVal set to (%d)\n", e->brk);
		}
		if (a == FTARG_OPTION)
		{
			if (p->c == 'b')
			{
				expect = FTARG_INT;
				awaiting = 'b';
			}

		}
	}
	if (awaiting != '\0')
		return (ERRORF(MISSING_EXPECT, awaiting));
	return (0);
}

int			li_env_init(t_env e[1], int ac, char const * const *av)
{
	ft_bzero(e, sizeof(*e));

	e->brk = -1;
	if (args(e, (t_arg_parser[1]){ft_arg_create(ac, av)}))
		return (1);
	e->key = ftok(LEMIPC_KEY_PATH, LEMIPC_KEY_VAL);
	if (e->key == -1)
		return (ERRORNO("ftok()"));
	return (0);
}
