/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:52:08 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/24 18:31:46 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIPC_H
# define LEMIPC_H

# include "libft.h"

# include "fterror.h"
# include <assert.h> //deb
# include "ft_debug.h" //deb

/*
** Needed for key_t
*/
# include <sys/ipc.h>

/*
** Needed for struct semid_ds
*/
# include <sys/sem.h>

# include <unistd.h> //for breakpoints


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
# define _BREAK_MSG(v) ERRORF("Pause with value (%d), HIT ENTER !!!", v)
# define _BREAK_PAUSE read(0, (char[1]){0}, 1)

typedef struct s_env		t_env;

union semun_t
{
	int				val;	/* Valeur pour SETVAL */
	struct semid_ds *buf;	/* Tampon pour IPC_STAT, IPC_SET */
	unsigned short	*array;	/* Tableau pour GETALL, SETALL */
};

struct s_env
{
	key_t					key;
	int						res_semid;
	int						brk;
};

t_env		*li_env(void);
int			li_env_init(t_env e[1], int ac, char const * const *av);
int			li_set_signals(t_env e[1]);
int			li_res_retrieve(t_env e[1]);
int			li_res_quit(t_env e[1]);

#endif
