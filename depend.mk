MKGEN_SRCSBIN_DEFAULT :=\
	obj/srcs/call_sequence.o\
	obj/srcs/env.o\
	obj/srcs/res_creation_msq.o\
	obj/srcs/ressources_life.o\
	obj/srcs/ressources_life_msq_pids.o\
	obj/srcs/ressources_life_sem_game.o\
	obj/srcs/ressources_life_sem_reslife.o\
	obj/srcs/ressources_life_shm_board.o\
	obj/srcs/ressources_life_shm_gameinfo.o\
	obj/srcs/sem_game_lock.o\
	obj/srcs/sem_reslife_lock.o\
	obj/srcs/signals.o\
	obj/srcs_default/main.o
MKGEN_SRCSBIN_GUI :=\
	obj/srcs/call_sequence.o\
	obj/srcs/env.o\
	obj/srcs/res_creation_msq.o\
	obj/srcs/ressources_life.o\
	obj/srcs/ressources_life_msq_pids.o\
	obj/srcs/ressources_life_sem_game.o\
	obj/srcs/ressources_life_sem_reslife.o\
	obj/srcs/ressources_life_shm_board.o\
	obj/srcs/ressources_life_shm_gameinfo.o\
	obj/srcs/sem_game_lock.o\
	obj/srcs/sem_reslife_lock.o\
	obj/srcs/signals.o\
	obj/srcs_gui/main.o
obj/srcs/call_sequence.o: libft/include/ft_stdio.h libft/include/ft_typedefs.h libft/include/ft_string.h libft/include/ft_stdlib.h libft/include/libft.h libft/include/ft_macroes.h srcs/call_sequence.c libft/include/ft_arithmetic.h libft/include/ft_ctype.h | obj/srcs/
obj/srcs/env.o: libft/include/ft_vector.h libft/include/ft_typedefs.h srcs/env.c libft/include/ft_stdlib.h include/lemipc.h libft/include/fterror.h libft/include/ft_debug.h libft/include/ft_arithmetic.h libft/include/ft_ctype.h libft/include/ft_stdio.h libft/include/ft_string.h libft/include/ft_arg.h libft/include/libft.h libft/include/ft_macroes.h | obj/srcs/
obj/srcs/res_creation_msq.o: libft/include/ft_stdio.h libft/include/ft_vector.h libft/include/ft_typedefs.h libft/include/ft_string.h libft/include/ft_stdlib.h libft/include/fterror.h libft/include/libft.h include/lemipc.h srcs/res_creation_msq.c libft/include/ft_macroes.h libft/include/ft_debug.h libft/include/ft_arithmetic.h libft/include/ft_ctype.h | obj/srcs/
obj/srcs/ressources_life.o: libft/include/ft_stdio.h libft/include/ft_vector.h libft/include/ft_typedefs.h libft/include/ft_string.h libft/include/ft_stdlib.h libft/include/fterror.h libft/include/libft.h srcs/ressources_life.c include/lemipc.h libft/include/ft_macroes.h libft/include/ft_debug.h libft/include/ft_arithmetic.h libft/include/ft_ctype.h | obj/srcs/
obj/srcs/ressources_life_msq_pids.o: libft/include/ft_stdio.h libft/include/ft_vector.h libft/include/ft_typedefs.h libft/include/ft_string.h libft/include/ft_stdlib.h libft/include/libft.h include/lemipc.h libft/include/ft_macroes.h libft/include/fterror.h libft/include/ft_debug.h srcs/ressources_life_msq_pids.c libft/include/ft_arithmetic.h libft/include/ft_ctype.h | obj/srcs/
obj/srcs/ressources_life_sem_game.o: libft/include/ft_stdio.h libft/include/ft_vector.h libft/include/ft_typedefs.h libft/include/ft_string.h libft/include/ft_stdlib.h libft/include/fterror.h libft/include/libft.h include/lemipc.h srcs/ressources_life_sem_game.c libft/include/ft_macroes.h libft/include/ft_debug.h libft/include/ft_arithmetic.h libft/include/ft_ctype.h | obj/srcs/
obj/srcs/ressources_life_sem_reslife.o: libft/include/ft_stdio.h libft/include/ft_vector.h libft/include/ft_typedefs.h libft/include/ft_string.h libft/include/ft_stdlib.h libft/include/fterror.h libft/include/libft.h include/lemipc.h libft/include/ft_macroes.h srcs/ressources_life_sem_reslife.c libft/include/ft_debug.h libft/include/ft_arithmetic.h libft/include/ft_ctype.h | obj/srcs/
obj/srcs/ressources_life_shm_board.o: libft/include/ft_stdio.h libft/include/ft_vector.h libft/include/ft_typedefs.h libft/include/ft_string.h libft/include/ft_stdlib.h libft/include/libft.h srcs/ressources_life_shm_board.c include/lemipc.h libft/include/ft_macroes.h libft/include/fterror.h libft/include/ft_debug.h libft/include/ft_arithmetic.h libft/include/ft_ctype.h | obj/srcs/
obj/srcs/ressources_life_shm_gameinfo.o: libft/include/ft_stdio.h libft/include/ft_vector.h libft/include/ft_typedefs.h libft/include/ft_string.h srcs/ressources_life_shm_gameinfo.c libft/include/ft_stdlib.h libft/include/libft.h include/lemipc.h libft/include/ft_macroes.h libft/include/fterror.h libft/include/ft_debug.h libft/include/ft_arithmetic.h libft/include/ft_ctype.h | obj/srcs/
obj/srcs/sem_game_lock.o: libft/include/ft_stdio.h libft/include/ft_vector.h libft/include/ft_typedefs.h libft/include/ft_string.h libft/include/ft_stdlib.h libft/include/libft.h srcs/sem_game_lock.c include/lemipc.h libft/include/ft_macroes.h libft/include/fterror.h libft/include/ft_debug.h libft/include/ft_arithmetic.h libft/include/ft_ctype.h | obj/srcs/
obj/srcs/sem_reslife_lock.o: libft/include/ft_stdio.h libft/include/ft_vector.h srcs/sem_reslife_lock.c libft/include/ft_typedefs.h libft/include/ft_string.h libft/include/ft_stdlib.h libft/include/libft.h include/lemipc.h libft/include/ft_macroes.h libft/include/fterror.h libft/include/ft_debug.h libft/include/ft_arithmetic.h libft/include/ft_ctype.h | obj/srcs/
obj/srcs/signals.o: libft/include/ft_stdio.h libft/include/ft_vector.h srcs/signals.c libft/include/ft_typedefs.h libft/include/ft_string.h libft/include/ft_stdlib.h libft/include/libft.h include/lemipc.h libft/include/ft_macroes.h libft/include/fterror.h libft/include/ft_debug.h libft/include/ft_arithmetic.h libft/include/ft_ctype.h | obj/srcs/
obj/srcs_gui/main.o: include/Main.hpp include/config_window.hpp srcs_gui/main.cpp | obj/srcs_gui/
obj/srcs_default/main.o: libft/include/ft_stdio.h libft/include/ft_vector.h libft/include/ft_typedefs.h srcs_default/main.c libft/include/ft_string.h libft/include/ft_stdlib.h libft/include/libft.h include/lemipc.h libft/include/ft_macroes.h libft/include/fterror.h libft/include/ft_debug.h libft/include/ft_arithmetic.h libft/include/ft_ctype.h | obj/srcs_default/
