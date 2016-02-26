O_FILES :=	obj/srcs/call_sequence.o obj/srcs/env.o obj/srcs/main.o \
			obj/srcs/res_creation_msq.o obj/srcs/res_game.o \
			obj/srcs/ressources_life.o obj/srcs/ressources_life_msq_pids.o \
			obj/srcs/ressources_life_read.o \
			obj/srcs/ressources_life_shm_nteam.o \
			obj/srcs/ressources_life_spawn.o obj/srcs/signals.o

LIBS_DEPEND := libft/libft.a

libs:
	make -C libft
.PHONY: libs



MAX_SOURCE_LEN := 32
obj/srcs/call_sequence.o: srcs/call_sequence.c libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/libft.h | obj/srcs/
obj/srcs/env.o: srcs/env.c include/lemipc.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/ft_vector.h \
	libft/include/fterror.h libft/include/libft.h libft/include/ft_arg.h \
	| obj/srcs/
obj/srcs/main.o: srcs/main.c include/lemipc.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/ft_vector.h \
	libft/include/fterror.h libft/include/libft.h | obj/srcs/
obj/srcs/res_creation_msq.o: srcs/res_creation_msq.c include/lemipc.h \
	libft/include/ft_ctype.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/ft_vector.h libft/include/fterror.h libft/include/libft.h \
	| obj/srcs/
obj/srcs/res_game.o: srcs/res_game.c include/lemipc.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/ft_vector.h \
	libft/include/fterror.h libft/include/libft.h | obj/srcs/
obj/srcs/ressources_life.o: srcs/ressources_life.c include/lemipc.h \
	libft/include/ft_ctype.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/ft_vector.h libft/include/fterror.h libft/include/libft.h \
	| obj/srcs/
obj/srcs/ressources_life_msq_pids.o: srcs/ressources_life_msq_pids.c \
	include/lemipc.h libft/include/ft_ctype.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/ft_vector.h libft/include/fterror.h libft/include/libft.h \
	| obj/srcs/
obj/srcs/ressources_life_read.o: srcs/ressources_life_read.c include/lemipc.h \
	libft/include/ft_ctype.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/ft_vector.h libft/include/fterror.h libft/include/libft.h \
	| obj/srcs/
obj/srcs/ressources_life_shm_nteam.o: srcs/ressources_life_shm_nteam.c \
	include/lemipc.h libft/include/ft_ctype.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/ft_vector.h libft/include/fterror.h libft/include/libft.h \
	| obj/srcs/
obj/srcs/ressources_life_spawn.o: srcs/ressources_life_spawn.c \
	include/lemipc.h libft/include/ft_ctype.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/ft_vector.h libft/include/fterror.h libft/include/libft.h \
	| obj/srcs/
obj/srcs/signals.o: srcs/signals.c include/lemipc.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/ft_vector.h \
	libft/include/fterror.h libft/include/libft.h | obj/srcs/
