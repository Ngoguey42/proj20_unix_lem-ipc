/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:52:08 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 16:39:46 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIPC_H
# define LEMIPC_H

# include "libft.h"
# include "fterror.h"
# include "ft_vector.h"

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
# define LEMIPC_KEY_VALGAME 4225

/*
** BREAK(e, v) macro is used to pause the process until read returns
** useful to debug dead locks
** Parameters:
**		e	used to retreive current process brk identifier (./lemipc -b 42)
**		v	brk identifier to compare with e->parma_brk
*/
# define BREAK(e,v) do{if(e->param_brk==v){_BREAK_MSG(v);_BREAK_PAUSE;}}while(0)
# define _BREAK_MSG(v) ERRORF("Pause with value (%d), HIT ENTER !!!", v)
# define _BREAK_PAUSE read(0, (char[1]){0}, 1)

# define SEQ_NFUNC 3

typedef struct s_env		t_env;

union semun_t
{
	int				val;
	struct semid_ds	*buf;
	unsigned short	*array;
};

struct s_msg_pid
{
	long			mtype;
	pid_t			pid;
};

struct s_shm_gameinfo
{
	int				nteam;
	int				wboard;
};

struct s_env
{
	key_t			key;

	int				param_nteam;
	int				param_brk;

	int				semid_reslife;
	int				msqid_pids;
	int				shmid_gameinfo;

	int				semid_game;
	int				shmid_board;
	void			*shm_board;
	t_ftvector		vec_msqids_team;

	int				team_id;
	bool			leave_game;
};

t_env		*li_env(void);
int			li_env_init(t_env e[1], int ac, char const * const *av);

int			li_set_signals(t_env e[1]);

int			li_res_spawn_or_read(t_env e[1]);
int			li_res_spawn_keeplock(t_env e[1]);
int			li_res_read_keeplock(t_env e[1]);

int			li_sem_reslife_spawn(t_env e[1]);
int			li_sem_reslife_destroy(t_env e[1]);
int			li_sem_reslife_read(t_env e[1]);

int			li_msq_pids_spawn(t_env e[1]);
int			li_msq_pids_destroy(t_env e[1]);
int			li_msq_pids_read(t_env e[1]);

int			li_shm_gameinfo_spawn(t_env e[1]);
int			li_shm_gameinfo_destroy(t_env e[1]);
int			li_shm_gameinfo_read(t_env e[1]);


int			li_res_destroy_or_defect(t_env e[1]);
int			li_res_resend_msq(t_env e[1], int count[1]);



#endif
