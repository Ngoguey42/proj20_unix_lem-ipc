/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 13:49:38 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 15:31:27 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** *
** Wrapper for sequencial calls
*/

int			ft_call_sequence(
	int (*const seqs[])(), size_t const bounds[2],
	size_t faulty_index[1], void *ext)
{
	int const	delta = (bounds[1] >= bounds[0]) ? 1 : 0;
	int			i;
	int			err;

	i = bounds[0];
	while (1)
	{
		err = seqs[i](ext);
		if (err != 0)
		{
			if (faulty_index != NULL)
				*faulty_index = i;
			return (err);
		}
		if (i == (int)bounds[1])
			break ;
		i += delta;
	}
	return (0);
}
