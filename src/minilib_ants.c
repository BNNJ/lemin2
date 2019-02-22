/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib_ants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 21:28:22 by pfragnou          #+#    #+#             */
/*   Updated: 2019/02/18 21:28:24 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Move the ants to the next room.
*/

void			move_forward(t_lm *lm, int *step)
{
	int		i;
	t_ant	*ant;

	i = 0;
	while (i < lm->nb_path)
	{
		ant = lm->paths[i].first_ant;
		while (ant && (ant->room != lm->start || ant->room->next == lm->end))
		{
			if (ant->room)
				ant->room = ant->room->next;
			ant = ant->next;
		}
		if (ant && ant->room == lm->start)
			ant->room = lm->paths[i].room;
		++i;
	}
	++*step;
}

/*
** Move the ants to the previous room.
** If they're in lm->end, the end room of the path is used to send them back
** on the right track.
*/

void			move_backward(t_lm *lm, int *step)
{
	int		i;
	t_ant	*ant;

	i = 0;
	while (i < lm->nb_path)
	{
		ant = lm->paths[i].first_ant;
		while (ant)
		{
			if (ant->room == NULL && (!ant->next || ant->next->room == lm->end))
				ant->room = lm->end;
			else if (ant->room == lm->end)
				ant->room = lm->paths[i].end;
			else if (ant->room && ant->room != lm->start)
				ant->room = ant->room->prev;
			ant = ant->next;
		}
		++i;
	}
	--*step;
}

/*
** Prints the position of the ants in order.
** Ants in the starting room are not printed.
*/

void			print_move(t_lm *lm)
{
	int		i;

	i = 0;
	while (i < lm->nb_ant && lm->ants[i].room == NULL)
		++i;
	while (i < lm->nb_ant && lm->ants[i].room != lm->start)
	{
		if (lm->ants[i].room)
		{
			if (lm->opt & OPT_COLOR)
				ft_printf("\e[9%dmL%d\e[m-%s", lm->ants[i].color,
					lm->ants[i].id, lm->ants[i].room->name);
			else
				ft_printf("L%d-%s", lm->ants[i].id, lm->ants[i].room->name);
			if (i + 1 < lm->nb_ant && lm->ants[i + 1].room != lm->start)
				ft_printf(" ");
		}
		++i;
	}
	ft_printf("\n");
}

/*
** Prints the position of ants,
** separating them depending on the path they're on.
** Ants in the starting room are not printed.
*/

void			print_move_alt(t_lm *lm)
{
	int		i;
	t_ant	*ant;

	i = -1;
	while (++i < lm->nb_path)
	{
		ant = lm->paths[i].first_ant;
		while (ant)
		{
			if (ant->room && ant->room != lm->start)
			{
				if (lm->opt & OPT_COLOR)
					ft_printf("\e[9%dmL%d\e[m-%s", ant->color,
						ant->id, ant->room->name);
				else
					ft_printf("L%d-%s", ant->id, ant->room->name);
				if (ant->next && ant->next->room != lm->start)
					ft_printf(" ");
			}
			ant = ant->next;
		}
		ft_printf(i + 1 == lm->nb_path ? "\n" : " | ");
	}
}
