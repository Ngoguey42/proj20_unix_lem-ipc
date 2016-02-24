/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:52:08 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/24 14:16:39 by ngoguey          ###   ########.fr       */
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

/*
** BREAK(e, v) macro is used to pause the process until read returns
** useful to debug dead locks
** Parameters:
**		e	used to retreive current process brk identifier (./lemipc -b 42)
**		v	brk identifier to compare with e->brk
*/
# define BREAK(e,v) do{if(e->brk==v){_BREAK_MSG(v);_BREAK_PAUSE;}}while(0)
# define _BREAK_MSG(v) ERRORF("Break with value (%d), HIT ENTER !!!", v)
# define _BREAK_PAUSE read(0, (char[1]){0}, 1)

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
