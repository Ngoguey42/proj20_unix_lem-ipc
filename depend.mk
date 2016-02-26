O_FILES :=	obj/srcs/call_sequence.o obj/srcs/env.o obj/srcs/main.o \
			obj/srcs/res_creation_msq.o obj/srcs/ressources_life.o \
			obj/srcs/ressources_life_msq_pids.o \
			obj/srcs/ressources_life_sem_game.o \
			obj/srcs/ressources_life_sem_reslife.o \
			obj/srcs/ressources_life_shm_board.o \
			obj/srcs/ressources_life_shm_gameinfo.o obj/srcs/signals.o

LIBS_DEPEND := libft/libft.a

libs:
	make -C libft
.PHONY: libs



MAX_SOURCE_LEN := 35
obj/srcs/call_sequence.o: srcs/call_sequence.c libft/include/ft_arithmetic.h \
	libft/include/ft_ctype.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/libft.h | obj/srcs/
obj/srcs/env.o: srcs/env.c include/lemipc.h libft/include/ft_arithmetic.h \
	libft/include/ft_ctype.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/ft_vector.h libft/include/fterror.h libft/include/libft.h \
	libft/include/ft_arg.h | obj/srcs/
obj/srcs/main.o: srcs/main.c include/lemipc.h libft/include/ft_arithmetic.h \
	libft/include/ft_ctype.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/ft_vector.h libft/include/fterror.h libft/include/libft.h \
	| obj/srcs/
obj/srcs/res_creation_msq.o: srcs/res_creation_msq.c include/lemipc.h \
	libft/include/ft_arithmetic.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/ft_vector.h \
	libft/include/fterror.h libft/include/libft.h | obj/srcs/
obj/srcs/ressources_life.o: srcs/ressources_life.c include/lemipc.h \
	libft/include/ft_arithmetic.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/ft_vector.h \
	libft/include/fterror.h libft/include/libft.h | obj/srcs/
obj/srcs/ressources_life_msq_pids.o: srcs/ressources_life_msq_pids.c \
	include/lemipc.h libft/include/ft_arithmetic.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/ft_vector.h \
	libft/include/fterror.h libft/include/libft.h | obj/srcs/
obj/srcs/ressources_life_sem_game.o: srcs/ressources_life_sem_game.c \
	include/lemipc.h libft/include/ft_arithmetic.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/ft_vector.h \
	libft/include/fterror.h libft/include/libft.h | obj/srcs/
obj/srcs/ressources_life_sem_reslife.o: srcs/ressources_life_sem_reslife.c \
	include/lemipc.h libft/include/ft_arithmetic.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/ft_vector.h \
	libft/include/fterror.h libft/include/libft.h | obj/srcs/
obj/srcs/ressources_life_shm_board.o: srcs/ressources_life_shm_board.c \
	include/lemipc.h libft/include/ft_arithmetic.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/ft_vector.h \
	libft/include/fterror.h libft/include/libft.h | obj/srcs/
obj/srcs/ressources_life_shm_gameinfo.o: srcs/ressources_life_shm_gameinfo.c \
	include/lemipc.h libft/include/ft_arithmetic.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/ft_vector.h \
	libft/include/fterror.h libft/include/libft.h | obj/srcs/
obj/srcs/signals.o: srcs/signals.c include/lemipc.h \
	libft/include/ft_arithmetic.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/ft_vector.h \
	libft/include/fterror.h libft/include/libft.h | obj/srcs/
