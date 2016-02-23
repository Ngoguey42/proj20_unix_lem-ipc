O_FILES :=	obj/srcs/main.o

LIBS_DEPEND := libft/libft.a

libs:
	make -C libft
.PHONY: libs



MAX_SOURCE_LEN := 11
obj/srcs/main.o: srcs/main.c | obj/srcs/
