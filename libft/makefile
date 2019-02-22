.PHONY: all clean fclean re

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)

SRC_DIR 	=	SRC_DISP	\
				SRC_CONV	\
				SRC_MEM		\
				SRC_LIST	\
				SRC_STR		\
				SRC_TSTR	\
				SRC_MISC	\
				SRC_MATH 


SRC = 			$(addprefix $(DIR_DISP), $(SRC_DISP)) 	\
				$(addprefix $(DIR_CONV), $(SRC_CONV))	\
				$(addprefix $(DIR_STR), $(SRC_STR))		\
				$(addprefix $(DIR_TSTR), $(SRC_TSTR))	\
				$(addprefix $(DIR_MEM), $(SRC_MEM))		\
				$(addprefix $(DIR_LIST), $(SRC_LIST))	\
				$(addprefix $(DIR_MISC), $(SRC_MISC))	\
				$(addprefix $(DIR_MATH), $(SRC_MATH))

SRCS 		=	$(addprefix ./srcs/, $(SRC))


DIR_DISP	=	display/
SRC_DISP	=	ft_putchar.c		\
				ft_putchar_fd.c		\
				ft_putendl.c		\
				ft_putendl_fd.c		\
				ft_putnbr.c			\
				ft_putnbr_fd.c		\
				ft_putstr.c			\
				ft_putstr_fd.c

DIR_CONV	=	conversion/
SRC_CONV	=	ft_atoi.c			\
				ft_strtoi.c			\
				ft_itoa.c			\
				ft_lltoa_base.c		\
				ft_ulltoa_base.c

DIR_STR		=	string/
SRC_STR		=	ft_strdup.c			\
				ft_strdup_s.c		\
				ft_strcat.c			\
				ft_strcmp.c			\
				ft_strcpy.c			\
				ft_strlcat.c		\
				ft_strlen.c			\
				ft_strlen_s.c		\
				ft_strncat.c		\
				ft_strncmp.c		\
				ft_strncpy.c		\
				ft_strnstr.c		\
				ft_strrchr.c		\
				ft_strstr.c			\
				ft_strclr.c			\
				ft_strdel.c			\
				ft_strequ.c			\
				ft_striter.c		\
				ft_striteri.c		\
				ft_strjoin.c		\
				ft_strjoin_f.c		\
				ft_strmap.c			\
				ft_strmapi.c		\
				ft_strnequ.c		\
				ft_strnew.c			\
				ft_strsplit.c		\
				ft_strsub.c			\
				ft_strsub_f.c		\
				ft_strtrim.c		\
				ft_strchr.c			\
				ft_findchar.c		\
				ft_strchrs.c		\
				ft_strchrsp.c

DIR_MEM		=	memory/
SRC_MEM		=	ft_memchr.c			\
				ft_memcmp.c			\
				ft_memcpy.c			\
				ft_memmove.c		\
				ft_memset.c			\
				ft_memalloc.c		\
				ft_memdel.c			\
				ft_memccpy.c		\
				ft_bzero.c

DIR_TSTR	=	tstr/
SRC_TSTR	=	ft_tstr_new.c		\
				ft_tstr_del.c		\
				ft_tstr_clr.c		\
				ft_tstr_dup.c		\
				ft_tstr_clr.c		\
				ft_tstr_sub.c		\
				ft_tstr_join.c		\
				ft_tstr_print.c		\
				ft_tstr_to_str.c	\
				ft_tstr_findchar.c	\
				ft_tstr_cmp.c		\
				ft_tstr_eq.c

DIR_LIST	=	list/
SRC_LIST	=	ft_lstnew.c			\
				ft_lstadd.c			\
				ft_lstdelone.c		\
				ft_lstdel.c			\
				ft_lstiter.c		\
				ft_lstmap.c			\
				ft_print_addr.c

DIR_MISC	=	misc/
SRC_MISC	=	ft_isalnum.c		\
				ft_isalpha.c		\
				ft_isascii.c		\
				ft_isdigit.c		\
				ft_isprint.c		\
				ft_tolower.c		\
				ft_toupper.c		\
				get_next_line.c		\
				ft_get_stdin.c

DIR_MATH	=	math/
SRC_MATH	=	ft_mat4_rotx.c		\
				ft_mat4_roty.c		\
				ft_mat4_rotz.c		\
				ft_mat4_scale.c		\
				ft_mat4_trslt.c		\
				ft_qtr_add.c		\
				ft_qtr_by_scalar.c	\
				ft_qtr_conj.c		\
				ft_qtr_invert.c		\
				ft_qtr_len.c		\
				ft_qtr_mult.c		\
				ft_qtr_new.c		\
				ft_qtr_norm.c		\
				ft_qtr_rotate.c		\
				ft_qtr_scalprod.c	\
				ft_qtr_sub.c		\
				ft_vec3_add.c		\
				ft_vec3_angle.c		\
				ft_vec3_by_scalar.c	\
				ft_vec3_crossprod.c	\
				ft_vec3_len.c		\
				ft_vec3_new.c		\
				ft_vec3_norm.c		\
				ft_vec3_scalprod.c	\
				ft_vec3_sub.c		\
				ft_vec3_to_qtr.c	\
				ft_vec4_by_mat4.c	\
				ft_vec4_by_scalar.c	\
				ft_vec4_len.c		\
				ft_vec4_scalprod.c


OBJ_DIR		=	./obj/
OBJ			=	$(SRC_CONV:.c=.o)	\
				$(SRC_DISP:.c=.o)	\
				$(SRC_TSTR:.c=.o)	\
				$(SRC_STR:.c=.o)	\
				$(SRC_LIST:.c=.o)	\
				$(SRC_MISC:.c=.o)	\
				$(SRC_MEM:.c=.o) 	\
				$(SRC_MATH:.c=.o)


OBJS		=	$(addprefix $(OBJ_DIR), $(OBJ))


INC_DIR		=	./includes/
INCS		=	$(addprefix $(INC_DIR), $(INC))
INC			=	libft.h

all: $(NAME)

$(NAME): message $(OBJ_DIR) $(OBJS) $(INCS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(OBJ_DIR)%.o:	./srcs/$(DIR_MISC)%.c $(INCS)
	@$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)%.o:	./srcs/$(DIR_LIST)%.c $(INCS)
	@$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)%.o:	./srcs/$(DIR_TSTR)%.c $(INCS)
	@$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)%.o:	./srcs/$(DIR_STR)%.c $(INCS)
	@$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)%.o:	./srcs/$(DIR_MEM)%.c $(INCS)
	@$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)%.o:	./srcs/$(DIR_DISP)%.c $(INCS)
	@$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)%.o:	./srcs/$(DIR_CONV)%.c $(INCS)
	@$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)%.o:	./srcs/$(DIR_MATH)%.c $(INCS)
	@$(CC) $(CFLAGS) -c $< -o $@

message:
	@echo compiling libft...

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@echo cleaning libft objects

fclean: clean
	@rm -f $(NAME)
	@echo cleaning libft binary

re: fclean all
