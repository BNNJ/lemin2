CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g

NAME		=	lem-in

SRC_DIR		=	./src

SRC			=	$(addprefix $(SRC_DIR)/,$(SRCS))

SRCS		=	lemin.c				\
				parser.c			\
				parser_rooms.c		\
				parser_links.c		\
				options.c			\
				setup_links.c		\
				augmenting_paths.c	\
				minilib_steps.c		\
				ants.c				\
				minilib_ants.c		\
				shortest_path.c		\
				minilib_queue.c		\
				minilib_matrix.c	\
				print_stuff.c		\
				viewer.c			\
				viewer_map.c		\
				viewer_ants.c		\
				viewer_control.c	\
				exit.c

OBJ_DIR		=	./obj

OBJ			=	$(addprefix $(OBJ_DIR)/,$(OBJS))
OBJS		=	$(SRCS:.c=.o)

INC_DIR		=	./include
INC			=	$(INC_DIR)/lemin.h

LIBFT_DIR	=	./libft
LIBFT		=	$(LIBFT_DIR)/libft.a
LIBFT_INC	=	$(LIBFT_DIR)/includes

FTPF_DIR	=	./ft_printf
FTPF		=	$(FTPF_DIR)/libftprintf.a
FTPF_INC	=	$(FTPF_DIR)/include

SDL_ROOT	=	./sdl2
SDL_BUILD	=	$(SDL_ROOT)/build
SDL_SRC		=	$(SDL_ROOT)/src
SDL_DIR		=	$(SDL_ROOT)/lib
SDL_LIB		=	$(SDL_DIR)/libSDL2.a
SDL_INC		=	$(SDL_ROOT)/include/SDL2

INC_FLAGS	=	-I$(INC_DIR) -I$(LIBFT_INC) -I$(FTPF_INC) -I$(SDL_INC)
LINK_FLAGS	=	-L$(LIBFT_DIR) -L$(FTPF_DIR) \
				-L$(SDL_DIR) -lSDL2 -lft -lftprintf 

all:			$(NAME)

$(NAME):		$(SDL_LIB) $(OBJ_DIR) $(OBJ) $(LIBFT) $(FTPF)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LINK_FLAGS)

message:
	@echo compiling $(NAME)...

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(INC)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC_FLAGS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(SDL_LIB):
	mkdir -p $(SDL_BUILD) && cd $(SDL_BUILD) && ../configure --prefix=$$PWD/../
	$(MAKE) -C $(SDL_BUILD)
	$(MAKE) -C $(SDL_BUILD) install

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(FTPF):
	@$(MAKE) -C $(FTPF_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(FTPF_DIR) clean
	@echo cleaning objects...
	@rm -rf $(OBJ_DIR)

cleansdl:
	@$(MAKE) -C $(SDL_BUILD) clean && $(MAKE) -C $(SDL_BUILD) uninstall

fclean:
	@$(MAKE) clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(FTPF_DIR) fclean
	@echo cleaning binaries...
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY:			all clean fclean re
