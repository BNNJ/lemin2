/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:39:06 by pfragnou          #+#    #+#             */
/*   Updated: 2018/11/26 15:39:08 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Gets the coordinates and name of the room and stores them in the
** parser structure.
** Returns 1 if the coordinates are valid, 0 otherwise.
*/

static int		lm_get_data(t_lm *lm, t_parser *p)
{
	char	*data;

	if (!(p->name = ft_strsub(p->data, 0, p->idx)))
		lm_exitparser(lm, p, "alloc error", EXIT_FAILURE);
	data = p->data + p->idx + 1;
	if ((p->x = ft_strtoi(&data)) < 0
		|| (p->y = ft_strtoi(&data)) < 0)
		return (0);
	return (*data == 0);
}

/*
** Checks if the name and coordinates stored in the parser structure
** have already been used.
*/

static int		lm_check_duplicate(t_lm *lm, t_parser *p)
{
	int	i;

	i = lm->nb_room;
	while (--i >= 0)
	{
		if (ft_strequ(lm->rooms[i]->name, p->name))
		{
			if (!(p->error = ft_strdup("room name already used")))
				lm_exitparser(lm, p, "alloc error", EXIT_FAILURE);
			return (0);
		}
		else if (lm->rooms[i]->coord.x == p->x && lm->rooms[i]->coord.y == p->y
			&& ~lm->opt & OPT_STRICT)
		{
			if (!(p->error = ft_strdup("room coordinates already used")))
				lm_exitparser(lm, p, "alloc error", EXIT_FAILURE);
			return (0);
		}
	}
	return (1);
}

/*
** Add a room to the lm->rooms array with the data stored in the parser struct.
*/

static t_room	*lm_add_room(t_lm *lm, t_parser *p)
{
	t_room		*new_room;
	t_room		**rooms;
	int			i;

	if (!(new_room = ft_memalloc(sizeof(t_room))))
		lm_exitparser(lm, p, "alloc error", EXIT_FAILURE);
	if (!(rooms = ft_memalloc(sizeof(t_room*) * (lm->nb_room + 2))))
		lm_exitparser(lm, p, "alloc error", EXIT_FAILURE);
	i = lm->nb_room;
	new_room->coord.x = p->x;
	new_room->coord.y = p->y;
	new_room->dist = INT_MAX;
	new_room->name = p->name;
	new_room->status = 0;
	p->name = NULL;
	rooms[i] = new_room;
	new_room->id = i;
	while (--i >= 0)
		rooms[i] = lm->rooms[i];
	free(lm->rooms);
	lm->rooms = rooms;
	++lm->nb_room;
	return (new_room);
}

/*
** First checks if room parsing is already finished by checking
** if the adjacency matrix already exists,
** then retrieves the data, checks if it has already been used,
** and finally creates a new room with it.
** If it has been previously established that this room should be
** a starting or ending room, the pointer is stored.
*/

void			lm_handle_room(t_lm *lm, t_parser *p)
{
	t_room	*room;

	if (lm->adjmat)
	{
		if (!(p->error = ft_strdup("It's too late for room declaration !")))
			lm_exitparser(lm, p, "alloc error", EXIT_FAILURE);
	}
	else if (!lm_get_data(lm, p) || *p->name == 'L')
	{
		if (!p->error && !(p->error = ft_strdup("Invalid or missing data")))
			lm_exitparser(lm, p, "alloc error", EXIT_FAILURE);
	}
	else if (lm_check_duplicate(lm, p))
	{
		room = lm_add_room(lm, p);
		if (p->next_type & ROOM_START)
			lm->start = room;
		if (p->next_type & ROOM_END)
			lm->end = room;
		p->next_type = ROOM_STD;
	}
}
