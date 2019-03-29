/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib_queue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:55:53 by pfragnou          #+#    #+#             */
/*   Updated: 2018/12/03 17:55:55 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		enqueue(t_queue *q, t_room *r)
{
	r->q_next = NULL;
	if (q->end)
		q->end->q_next = r;
	else
		q->start = r;
	r->status |= QUEUED;
	q->end = r;
}

t_room		*dequeue(t_queue *q)
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
