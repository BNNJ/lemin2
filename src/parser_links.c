/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:38:58 by pfragnou          #+#    #+#             */
/*   Updated: 2018/11/26 15:38:59 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Creates the adjacency matrix.
*/

static void	create_mat(t_lm *lm, t_parser *p)
{
	int	i;

	i = 0;
	if (!(lm->adjmat = ft_memalloc(sizeof(int*) * lm->nb_room)))
		lm_exitparser(lm, p, "matrix error", EXIT_FAILURE);
	while (i < lm->nb_room)
	{
		if (!(lm->adjmat[i] = ft_memalloc(sizeof(int) * lm->nb_room)))
			lm_exitparser(lm, p, "matrix error", EXIT_FAILURE);
		++i;
	}
}

/*
** Goes through the rooms names until it finds a match, and returns
** the id of the matching room.
** If none is found, -1 is returned.
*/

static int	get_room_id(t_lm *lm, t_parser *p)
{
	int		i;

	i = lm->nb_room;
	while (--i >= 0)
	{
		if (ft_strequ(lm->rooms[i]->name, p->name))
			return (i);
	}
	return (-1);
}

/*
** Adds the link in the adjacency matrix.
*/

static void	add_link(t_lm *lm, t_parser *p)
{
	if (p->x == p->y)
	{
		if (~lm->opt & OPT_STRICT && !(p->error = ft_strdup("invalid link")))
			lm_exitparser(lm, p, "alloc error", EXIT_FAILURE);
	}
	else
	{
		if (lm->adjmat[p->x][p->y] == 0)
		{
			++lm->rooms[p->x]->nb_link;
			++lm->rooms[p->y]->nb_link;
			lm->adjmat[p->x][p->y] = 1;
			lm->adjmat[p->y][p->x] = 1;
		}
		else if (~lm->opt & OPT_STRICT)
		{
			if (!(p->error = ft_strdup("rooms already linked")))
				lm_exitparser(lm, p, "alloc error", EXIT_FAILURE);
		}
	}
}

/*
** First creates the adjacency matrix if it doesn't already exist,
** then gets the id of both rooms and adds the link in the matrix
** if it is valid.
*/

void		lm_handle_link(t_lm *lm, t_parser *p)
{
	if (p->next_type != 0)
	{
		p->error = ft_strdup("Can't apply instruction");
		return ;
	}
	if (!lm->adjmat)
		create_mat(lm, p);
	if (!(p->name = ft_strsub(p->data, 0, p->idx)))
		lm_exitparser(lm, p, "alloc error", EXIT_FAILURE);
	p->x = get_room_id(lm, p);
	ft_strdel(&p->name);
	if (!(p->name = ft_strdup(p->data + p->idx + 1)))
		lm_exitparser(lm, p, "alloc error", EXIT_FAILURE);
	p->y = get_room_id(lm, p);
	ft_strdel(&p->name);
	if (p->y >= 0 && p->x >= 0)
		add_link(lm, p);
	else if (!(p->error = ft_strdup("invalid link")))
		lm_exitparser(lm, p, "alloc error", EXIT_FAILURE);
}
