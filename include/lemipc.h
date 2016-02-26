/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 15:52:08 by ngoguey           #+#    #+#             */
/*   Updated: 2016/02/26 19:41:43 by ngoguey          ###   ########.fr       */
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

/*
** Needed for breakpoints
*/
# include <unistd.h>

# define LEMIPC_KEY_PATH "/tmp"
# define LEMIPC_KEY_VAL 4224
# define LEMIPC_KEY_VALGAME 4225

# define SEQ_NFUNC 5

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

typedef struct s_env		t_env;

/*
** ************************************************************************** **
** Ressources life management
*/

/*
** Union required by some syscall
*/

union semun_t
{
	int				val;
	struct semid_ds	*buf;
	unsigned short	*array;
};

/*
** Self pid information, used to keep track of num processes alive regarding
**		ressources release
*/

struct s_msg_pid
{
	long			mtype;
	pid_t			pid;
};

/*
** Shared game info (consistency required among players)
**		Those informations are all set by ressources creator
*/

struct s_shm_gameinfo
{
	int				nteam;
	int				wboard;
};

/*
** ************************************************************************** **
** General message passed ingame
*/

/*
** Enemies positions snitching canal
*/

struct s_msg_foe
{
	pid_t			snitch;
	double			msgtime;
	int				teamid;
	t_vec2i			pos;
};

/*
** Self position information canal
*/

struct s_msg_ally
{
	pid_t			pid;
	double			lastactivity;
	t_vec2i			pos;
};

/*
** ************************************************************************** **
** Environment
*/

struct s_env
{
	key_t			key;
	key_t			keygame;

	int				param_nteam;
	int				param_wboard;
	int				param_brk;
	/* t_strategy		param_strat; */

	int				semid_reslife;
	int				msqid_pids;
	int				shmid_gameinfo;

	int				semid_game;
	int				shmid_board;
	int				*shm_board;
	/* t_ftvector		vec_msqids_foe; */
	/* t_ftvector		vec_msqids_ally; */

	t_vec2i			pos;
	int				team_id; //TODO: tid param or random / check consistency
	bool			leave_game;
};

/*
** ************************************************************************** **
** Prototypes
*/

/*
** Env singleton (for signals handling)
*/
t_env		*li_env(void);

/*
** Init Phase
** 		(li_[...]_destroy also used in exit phase)
*/
int			li_env_init(t_env e[1], int ac, char const * const *av);

int			li_set_signals(t_env e[1]);

int			li_res_spawn_or_read(t_env e[1]);

int			li_sem_reslife_spawn(t_env e[1]);
int			li_sem_reslife_destroy(t_env e[1]);
int			li_sem_reslife_read(t_env e[1]);

int			li_msq_pids_spawn(t_env e[1]);
int			li_msq_pids_destroy(t_env e[1]);
int			li_msq_pids_read(t_env e[1]);

int			li_shm_gameinfo_spawn(t_env e[1]);
int			li_shm_gameinfo_destroy(t_env e[1]);
int			li_shm_gameinfo_read(t_env e[1]);

int			li_sem_game_spawn(t_env e[1]);
int			li_sem_game_destroy(t_env e[1]);
int			li_sem_game_read(t_env e[1]);

int			li_shm_board_spawn(t_env e[1]);
int			li_shm_board_destroy(t_env e[1]);
int			li_shm_board_read(t_env e[1]);

/*
** Game Phase
*/

/*
** Exit Phase
*/
int			li_res_destroy_or_defect(t_env e[1]);
int			li_res_resend_msq(t_env e[1], int count[1]);

#endif
