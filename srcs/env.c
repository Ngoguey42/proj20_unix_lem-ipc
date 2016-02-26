/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 12:33:54 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 16:50:25 by ngoguey          ###   ########.fr       */
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

#define BAD_OPTION "./lemipc option -%c unknown"
#define BAD_EXPECT "./lemipc option -%c takes an argument of type %s"
#define MISSING_EXPECT "./lemipc missing argument after option -%c"

static int	handle_option(
	t_env e[1], t_arg_parser p[1], char awaiting[1], enum e_arg expect[1])
{
	if (p->c == 'b')
	{
		*expect = FTARG_INT;
		*awaiting = 'b';
		return (0);
	}
	else if (p->c == 'c')
	{
		*expect = FTARG_INT;
		*awaiting = 'c';
		return (0);
	}
	else if (p->c == 'w')
	{
		*expect = FTARG_INT;
		*awaiting = 'w';
		return (0);
	}
	(void)e;
	return (1);
}

static int	handle_awaited(t_env e[1], t_arg_parser p[1], char awaiting[1])
{
	if (*awaiting == 'b')
	{
		e->param_brk = p->i;
		ft_printf("Break val parameter = %d\n", e->param_brk);
	}
	else if (*awaiting == 'c')
	{
		if (p->i < 2)
			return (ERROR("Num team too low"));
		e->param_nteam = p->i;
		ft_printf("Num team parameter = %d\n", e->param_nteam);
	}
	else if (*awaiting == 'w')
	{
		if (p->i < 4)
			return (ERROR("Board size too low"));
		e->param_wboard = p->i;
		ft_printf("Board size parameter = %d\n", e->param_nteam);
	}
	return (0);
}

static int	args(t_env e[1], t_arg_parser p[1])
{
	enum e_arg	a;
	enum e_arg	expect[1];
	char		awaiting[1];

	*expect = FTARG_NONE;
	*awaiting = '\0';
	while ((a = ft_arg_next(p, *expect)) != FTARG_NONE)
	{
		if (*awaiting != '\0' && a != *expect)
			return (ERRORF(BAD_EXPECT, *awaiting, ft_arg_name(*expect)));
		else if (*awaiting != '\0')
		{
			if (handle_awaited(e, p, awaiting))
				return (ERROR(""));
		}
		*awaiting = '\0';
		*expect = FTARG_NONE;
		if (a == FTARG_OPTION)
			if (handle_option(e, p, awaiting, expect))
				return (ERRORF(BAD_OPTION, p->c));
	}
	if (*awaiting != '\0')
		return (ERRORF(MISSING_EXPECT, *awaiting));
	return (0);
}

int			li_env_init(t_env e[1], int ac, char const *const *av)
{
	ft_bzero(e, sizeof(*e));
	e->param_brk = -1;
	e->param_nteam = -1;
	e->param_wboard = -1;
	if (args(e, (t_arg_parser[1]){ft_arg_create(ac, av)}))
		return (1);
	return (0);
}
