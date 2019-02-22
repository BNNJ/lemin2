/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib_steps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 21:28:31 by pfragnou          #+#    #+#             */
/*   Updated: 2019/02/18 21:28:32 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Find the number of rooms included in the paths, not counting start
*/

int			get_total_len(t_path *paths, int nb_paths)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < nb_paths)
	{
		len += paths[i].len;
		++i;
	}
	return (len);
}

/*
** Find the length of the longest path.
*/

int			get_max_len(t_path *paths, int nb_paths)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < nb_paths)
	{
		if (paths[i].len > len)
			len = paths[i].len;
		++i;
	}
	return (len);
}

/*
** Calculates the number of steps required to solve a graph.
*/

int			number_of_steps(t_lm *lm, int nb_paths)
{
	int		big_len;
	int		nb_rooms;
	int		base_ant;
	int		extra_ant;
	int		nb_steps;

	big_len = get_max_len(lm->paths, nb_paths);
	nb_rooms = get_total_len(lm->paths, nb_paths);
	base_ant = ((big_len * nb_paths) - nb_rooms);
	if ((extra_ant = lm->nb_ant - base_ant) < 0)
		return (-1);
	nb_steps = big_len - 1 + extra_ant / nb_paths + (extra_ant % nb_paths != 0);
	if (lm->opt & OPT_DEBUG)
	{
		ft_printf("\n##################\n");
		ft_printf("big_len = %d\nnb_rooms = %d\n", big_len, nb_rooms);
		ft_printf("base_ant = %d\nextra_ant = %d\n", base_ant, extra_ant);
		ft_printf("nb_paths = %d\nnb_steps = %d\n", nb_paths, nb_steps);
		ft_printf("##################\n");
	}
	return (nb_steps);
}
