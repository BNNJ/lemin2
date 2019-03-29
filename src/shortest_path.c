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

typedef struct	s_queue
{
	t_room	*start;
	t_room	*end;
}				t_queue;

static void		enqueue(t_queue *q, t_room *r)
{
	r->q_next = NULL;
	if (q->end)
		q->end->q_next = r;
	else
		q->start = r;
	r->status |= QUEUED;
	q->end = r;
}

static t_room	*dequeue(t_queue *q)
{
	t_room	*r;

	r = q->start;
	if (q->start)
	{
		q->start = q->start->q_next;
		r->status &= ~QUEUED;
		r->q_next = NULL;
	}
	if (!q->start)
		q->end = NULL;
	return (r);
}
/*
static t_room	*update_path(t_lm *lm)
{
	int		i;
	t_room	*r;
	t_room	*prev;

	r = lm->end;
	while (r != lm->start)
	{
		i = 0;
		while (r->links[i]->dist != r->dist - 1)
			++i;
		prev = r->links[i];
		--lm->adjmat[prev->id][r->id];
		++lm->adjmat[r->id][prev->id];
		if (r->dist == 1)
		{
			ft_printf("%s\n", r->name);
			return (r);
		}
		r = prev;
	}
	return (NULL);
}
*/

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
		lm->rooms[i]->dist = INT_MAX;
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
		else
			r->status &= ~CROSSROAD;
	}
	return (r == lm->end ? update_path(lm) : NULL);
}
