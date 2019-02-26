/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:55:53 by pfragnou          #+#    #+#             */
/*   Updated: 2018/12/03 17:55:55 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Update the distance of the rooms adjacent to 'room'
** If the current room already has link to another room,
** it means it is already part of a path, so it cannot be used except to go
** back to the room linking to it.
** This "reverse flow" is used to reuse nodes to create new paths.
*/

static int		update_neighbors(t_lm *lm, t_room *cur)
{
	int		i;
	t_room	*tmp;
	int		ret;

	i = 0;
	ret = 0;
	while (i < cur->nb_link)
	{
		tmp = cur->links[i];
		if (lm->adjmat[cur->id][tmp->id] > 0 && tmp->dist > cur->dist + 1)
		{
			if (!(cur->status & CROSSROAD)
				|| (cur->status & CROSSROAD && tmp->next == cur))
			{
				ret = 1;
				tmp->dist = cur->dist + 1;
				if (tmp->status & SPT_MEMBER && tmp->next != cur)
					tmp->status |= CROSSROAD;
			}
		}
		++i;
	}
	return (ret);
}

/*
** Returns the non-visited room that is closest to the start.
*/

static t_room	*get_closest_room(t_lm *lm)
{
	int		i;
	int		dist;
	t_room	*tmp;

	i = 0;
	dist = INT_MAX;
	tmp = NULL;
	while (i < lm->nb_room)
	{
		if (lm->rooms[i]->dist < dist && !(lm->rooms[i]->status & VISITED))
		{
			dist = lm->rooms[i]->dist;
			tmp = lm->rooms[i];
		}
		++i;
	}
	return (tmp);
}

/*
** Goes through the path backward. Previous nodes are found using the distance.
** A temporary path is set using 'spt_path'.
*/

static void		update_path(t_lm *lm)
{
	int		i;
	t_room	*cur;

	cur = lm->end;
	while (cur != lm->start)
	{
		i = 0;
		while (cur->links[i]->dist != cur->dist - 1)
			++i;
		cur->links[i]->spt_next = cur;
		--lm->adjmat[cur->links[i]->id][cur->id];
		++lm->adjmat[cur->id][cur->links[i]->id];
		cur = cur->links[i];
	}
}

/*
** Resets rooms variables.
** Rooms distances are set to INT_MAX (virtually infinity),
*/

static void		init_rooms(t_lm *lm)
{
	int	i;

	i = 0;
	while (i < lm->nb_room)
	{
		lm->rooms[i]->status &= ~VISITED;
		lm->rooms[i]->status &= ~CROSSROAD;
		lm->rooms[i]->dist = INT_MAX;
		lm->rooms[i]->spt_next = NULL;
		++i;
	}
}

/*
** BFS algorithm with a few twists, searches for the shortest path available.
** Start's distance is initialized to 0 so it gets picked first.
** Returns a pointer to the first room of the path found (excluding start)
** or NULL if no path is found
*/

t_room			*lm_shortest_path(t_lm *lm)
{
	t_room	*cur;

	init_rooms(lm);
	lm->start->dist = 0;
	cur = NULL;
	while (cur != lm->end)
	{
		if (!(cur = get_closest_room(lm)))
			return (NULL);
		cur->status |= VISITED;
		if (!(update_neighbors(lm, cur)) && cur != lm->end)
		{
			cur->status &= ~(CROSSROAD | VISITED);
			cur->dist = INT_MAX;
		}
	}
	update_path(lm);
	return (lm->start->spt_next);
}
