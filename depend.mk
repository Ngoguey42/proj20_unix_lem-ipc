O_FILES :=	obj/srcs/env.o obj/srcs/exit.o obj/srcs/main.o \
			obj/srcs/res_control.o

LIBS_DEPEND := libft/libft.a

libs:
	make -C libft
.PHONY: libs



MAX_SOURCE_LEN := 18
obj/srcs/env.o: srcs/env.c include/lemipc.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	libft/include/ft_arg.h | obj/srcs/
obj/srcs/exit.o: srcs/exit.c include/lemipc.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	| obj/srcs/
obj/srcs/main.o: srcs/main.c include/lemipc.h libft/include/ft_ctype.h \
	libft/include/ft_macroes.h libft/include/ft_stdio.h \
	libft/include/ft_stdlib.h libft/include/ft_string.h \
	libft/include/ft_typedefs.h libft/include/fterror.h libft/include/libft.h \
	| obj/srcs/
obj/srcs/res_control.o: srcs/res_control.c include/lemipc.h \
	libft/include/ft_ctype.h libft/include/ft_macroes.h \
	libft/include/ft_stdio.h libft/include/ft_stdlib.h \
	libft/include/ft_string.h libft/include/ft_typedefs.h \
	libft/include/fterror.h libft/include/libft.h | obj/srcs/
