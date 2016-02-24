/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 12:33:54 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/24 12:41:28 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"

#include <stdlib.h>

t_env	*li_env(void)
{
	static t_env	*e = NULL;

	if (e == NULL)
		e = malloc(sizeof(*e));
	return (e);
}


int		li_env_init(t_env e[1])
{
	ft_bzero(e, sizeof(*e));

	return (0);
}
