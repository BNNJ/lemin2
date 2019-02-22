NAME			=	libftprintf.a

CC				=	gcc
CFLAGS			=	-I$(INC_DIR)

SRC_DIR			=	./src/
SRCS			=	$(addprefix $(SRC_DIR), $(SRC))
SRC				=	ft_printf.c			\
					ft_sprintf.c		\
					handler_array.c		\
					handler_binflag.c	\
					handler_buffer.c	\
					handler_char.c		\
					handler_display.c	\
					handler_file.c		\
					handler_float.c		\
					handler_int.c		\
					handler_ptr.c		\
					handler_str.c		\
					minilibft.c			\
					parser.c			\
					parser_flags.c

OBJ_DIR			=	./obj/
OBJS			=	$(addprefix $(OBJ_DIR), $(OBJ))
OBJ				=	$(SRC:.c=.o)

INC_DIR			=	./include/
INCS			=	$(addprefix $(INC_DIR), $(INC))
INC				=	ft_printf.h

.PHONY: all clean fclean re

all:				$(NAME)

$(NAME):			message $(OBJ_DIR) $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c $(INCS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

message:
	@echo compiling ft_printf...

clean:
	@echo cleaning ft_printf objects...
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)

fclean:
	@echo cleaning ft_printf binary...
	@make clean
	@rm -f $(NAME)

re:
	@make fclean
	@make all
