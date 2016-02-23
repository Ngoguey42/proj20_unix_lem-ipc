/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:52:08 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/23 17:48:00 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIPC_H
# define LEMIPC_H

# include "libft.h"

# include "fterror.h"
# include <assert.h> //deb
# include "ft_debug.h" //deb

# include <sys/ipc.h>

# define LEMIPC_KEY_PATH "/tmp"
# define LEMIPC_KEY_VAL 4224

typedef struct s_env		t_env;

struct s_env
{
	key_t					key;
	int						semid;
};

#endif
