/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 21:22:06 by pfragnou          #+#    #+#             */
/*   Updated: 2019/02/18 21:22:07 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Pushes ant to the end of a path's ant list.
*/

static void		add_ant(t_ant *ant, t_path *path)
{
	if (!path->first_ant)
	{
		path->first_ant = ant;
		path->last_ant = ant;
	}
	else
	{
		path->last_ant->next = ant;
		ant->prev = path->last_ant;
		path->last_ant = ant;
	}
	++path->nb_ant;
}

/*
** Assigns each ant to a path, depending on the path's length
** and the pre-calculated number of steps.
*/

static t_ant	*setup_ants(t_lm *lm)
{
	int		i;
	int		j;
	t_ant	*ants;

	if (!(ants = ft_memalloc(lm->nb_ant * sizeof(t_ant))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < lm->nb_ant)
	{
		if (j >= lm->nb_path)
			j = 0;
		if (lm->paths[j].nb_ant + lm->paths[j].len <= lm->nb_step
			|| lm->start->next == lm->end)
		{
			ants[i].id = i + 1;
			ants[i].color = i % 7 + 1;
			ants[i].room = lm->start;
			add_ant(&ants[i], &lm->paths[j]);
			++i;
		}
		++j;
	}
	return (ants);
}

/*
** Iterates on a pre-calculated number of steps, and at each iteration sends
** the ants one room further on their path, then prints their position.
*/

static void		send_ants(t_lm *lm)
{
	int		step;

	step = 0;
	if (~lm->opt & OPT_PRINT)
		ft_printf("\n");
	while (step < lm->nb_step)
	{
		move_forward(lm, &step);
		lm->opt & OPT_DISP ? print_move_alt(lm) : print_move(lm);
	}
	ft_printf("\n");
	ft_dprintf(2, "%d ant%ssent through %d path%sin %d step%s",
		lm->nb_ant, lm->nb_ant > 1 ? "s " : " ",
		lm->nb_path, lm->nb_path > 1 ? "s " : " ",
		lm->nb_step, lm->nb_step > 1 ? "s\n" : "\n");
	if (lm->required)
		ft_dprintf(2, "required : %d\n", lm->required);
}

/*
** Handles the ants :
** first creates and sets up the ants array,
** then redirects to the proper handling function depending on wether or not
** the viewer option has been enabled
*/

void			ants(t_lm *lm)
{
	if ((lm->ants = setup_ants(lm)))
	{
		if (lm->opt & OPT_VIEWER)
			viewer(lm);
		else
			send_ants(lm);
	}
	else
		lm_exit(lm, "alloc error", EXIT_FAILURE);
}
