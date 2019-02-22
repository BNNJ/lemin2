/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:38:37 by pfragnou          #+#    #+#             */
/*   Updated: 2018/11/26 15:38:38 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		lm_exitparser(t_lm *lm, t_parser *p, char *msg, int exit_status)
{
	ft_strdel(&p->error);
	ft_strdel(&p->data);
	get_next_line(0, NULL);
	lm_exit(lm, msg, exit_status);
}

static void	lm_free_rooms(t_lm *lm)
{
	int		i;
	t_room	*tmp;

	i = 0;
	while (i < lm->nb_room)
	{
		tmp = lm->rooms[i];
		free(tmp->name);
		if (tmp->links)
			free(tmp->links);
		free(tmp);
		++i;
	}
	free(lm->rooms);
}

static void	lm_free_adjmat(t_lm *lm)
{
	int	i;

	i = 0;
	while (i < lm->nb_room)
	{
		free(lm->adjmat[i]);
		++i;
	}
	free(lm->adjmat);
}

void		lm_exit(t_lm *lm, char *msg, int exit_status)
{
	if (msg)
		ft_dprintf(2, "%{red}Error : %s%{eoc}\n", msg);
	if (lm->adjmat)
		lm_free_adjmat(lm);
	if (lm->rooms)
		lm_free_rooms(lm);
	if (lm->paths)
		free(lm->paths);
	if (lm->ants)
		free(lm->ants);
	exit(exit_status);
}
