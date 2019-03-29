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

static t_room	*update_path(t_lm *lm)
{
	t_room	*r;
	t_room	*prev;

	r = lm->end;
	while (r != lm->start)
	{
		prev = r->prev;
		--lm->adjmat[prev->id][r->id];
		++lm->adjmat[r->id][prev->id];
		if (prev == lm->start)
			return (r);
		r = prev;
	}
	return (NULL);
}

static void		init_rooms(t_lm *lm)
{
	int		i;

	i = 0;
	while (i < lm->nb_room)
	{
		lm->rooms[i]->status &= ~(VISITED | QUEUED | CROSSROAD);
		lm->rooms[i]->q_next = NULL;
		lm->rooms[i]->prev = NULL;
		++i;
	}
}

static int		visit_room(t_lm *lm, t_room *r, t_queue *q)
{
	int		i;
	t_room	*tmp;
	int		ret;

	i = 0;
	ret = 0;
	while (i < r->nb_link)
	{
		tmp = r->links[i];
		if (lm->adjmat[r->id][tmp->id] > 0 && ~tmp->status & VISITED)
		{
			if (~tmp->status & QUEUED
				&& (~r->status & CROSSROAD || tmp->next == r))
			{
				enqueue(q, tmp);
				tmp->prev = r;
				ret = 1;
				if (tmp->status & SPT_MEMBER && tmp->next != r)
					tmp->status |= CROSSROAD;
			}
			else if (tmp->status & QUEUED && tmp->status & CROSSROAD)
			{
				ret = 1;
				tmp->prev = r;
				tmp->status &= ~CROSSROAD;
			}
		}
		++i;
	}
	return (ret);
}

static void		reset_room(t_room *r)
{
	while (~r->status & CROSSROAD)
		r = r->prev;
	r->status &= ~(CROSSROAD | VISITED);
}

t_room			*lm_shortest_path(t_lm *lm)
{
	t_queue	q;
	t_room	*r;

	q = (t_queue){NULL, NULL};
	init_rooms(lm);
	enqueue(&q, lm->start);
	while (q.start && r != lm->end)
	{
		r = dequeue(&q);
		if (visit_room(lm, r, &q))
			r->status |= VISITED;
		else if (r->status & SPT_MEMBER)
			reset_room(r);
	}
	return (r == lm->end ? update_path(lm) : NULL);
}
