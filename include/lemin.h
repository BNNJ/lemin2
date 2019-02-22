/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:43:49 by pfragnou          #+#    #+#             */
/*   Updated: 2018/11/26 15:43:50 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"
# include "ft_printf.h"
# include "limits.h"
# include <errno.h>
# include "SDL.h"

# define DEBUG_VALUE 1024

# define WIDTH 1200
# define HEIGHT 800
# define NB_FRAME 64

# define ROOM_STD 0
# define ROOM_START 1
# define ROOM_END 2

# define VISITED 1
# define SPT_MEMBER 2
# define CROSSROAD 4

# define OPT_PRINT 1
# define OPT_DEBUG 2
# define OPT_STRICT 4
# define OPT_DISP 8
# define OPT_COLOR 16
# define OPT_ALT 32
# define OPT_VIEWER 64
# define OPT_ANT 512

typedef struct s_room	t_room;

typedef struct			s_ant
{
	int				id;
	int				color;
	t_room			*room;
	struct s_ant	*next;
	struct s_ant	*prev;
	t_point			coord;
}						t_ant;

typedef struct			s_path
{
	t_room			*room;
	t_room			*end;
	t_ant			*first_ant;
	t_ant			*last_ant;
	int				len;
	int				color;
	int				nb_ant;
	int				nb_step;
}						t_path;

struct					s_room
{
	char			*name;
	int				id;
	int				status;
	ssize_t			dist;
	t_point			coord;
	t_ant			*ant;
	int				ant_id;
	int				nb_link;
	t_room			**links;
	t_room			*next;
	t_room			*spt_next;
	t_room			*prev;
};

typedef struct			s_parser
{
	char			*error;
	int				next_type;
	char			*data;
	int				nb_ant;
	int				idx;
	int				x;
	int				y;
	char			*name;
}						t_parser;

typedef struct			s_lm
{
	t_room			**rooms;
	t_room			*start;
	t_room			*end;
	t_path			*paths;
	t_ant			*ants;
	int				nb_room;
	int				nb_path;
	int				required;
	int				**adjmat;
	int				**viewmat;
	int				opt;
	int				nb_ant;
	int				nb_step;
}						t_lm;

typedef struct			s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	int				state;
	int				delay;
}						t_sdl;

/*
** exit.c
*/

void					lm_exit(t_lm *lm, char *msg, int exit_status);
void					lm_exitparser(t_lm *lm, t_parser *p, char *msg,
	int exit_status);

/*
** algo
** shortest_path.c, augmenting_path.c, graph.c, send_ants.c
*/

void					ants(t_lm *lm);
int						lm_solver(t_lm *lm);
t_room					*lm_shortest_path(t_lm *lm);
void					move_forward(t_lm *lm, int *step);
void					move_backward(t_lm *lm, int *step);
void					print_move(t_lm *lm);
void					print_move_alt(t_lm *lm);

/*
** utility functions
** minilib.c, minilib_matrix.c, setup_links.c
*/

int						number_of_steps(t_lm *lm, int nb_paths);
int						get_max_len(t_path *paths, int nb_paths);
void					*free_matrix(int **matrix, int size);
int						**create_matrix(int size);
void					update_matrix(t_lm *lm, int **matrix);
void					lm_setup_links(t_lm *lm);

/*
** parsing :
** options.c, parser.c, parser_rooms.c, parser_links.c, handle_tubes.c
*/

int						lm_options(t_lm *lm, int argc, char **argv);
void					lm_parser(t_lm *lm);
void					lm_handle_link(t_lm *lm, t_parser *p);
void					lm_handle_room(t_lm *lm, t_parser *p);

/*
** print_stuff.c
*/

void					print_stuff(t_lm *lm);
void					print_ants_mat(t_lm *lm);
void					print_rooms(t_lm *lm);
void					print_paths(t_lm *lm);

/*
** viewer.c, viewer_map.c, viewer_control.c, viewer_ants.c
*/

void					viewer(t_lm *lm);
void					sdl_exit(t_lm *lm, t_sdl *sdl, int exit_status);
int						viewer_control(t_lm *lm, t_sdl *sdl, int *step);
int						indraw_control(t_lm *lm, t_sdl *sdl);
int						setup_map(t_lm *lm);
int						draw_map(t_lm *lm, t_sdl *sdl);
int						draw_ants(t_lm *lm, t_sdl *sdl, int k);

#endif
