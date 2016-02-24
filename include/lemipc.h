/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:52:08 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/24 14:09:56 by ngoguey          ###   ########.fr       */
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

# define BREAK_MSG(v) ERRORF("Break with value (%d)", v)
# define BREAK(e,v) do{if(e->brk==v){BREAK_MSG(v);while(1);}}while(0)

typedef struct s_env		t_env;

struct s_env
{
	key_t					key;
	int						semid;
	int						brk;
};

t_env		*li_env(void);
int			li_env_init(t_env e[1], int ac, char const * const *av);
int			li_set_signals(t_env e[1]);

#endif
