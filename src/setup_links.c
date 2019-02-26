/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 18:07:44 by pfragnou          #+#    #+#             */
/*   Updated: 2018/12/03 18:07:45 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** For each room, create an array of pointers to the rooms it is linked to
*/

void		lm_setup_links(t_lm *lm)
{
	int		i;
	int		j;
	int		k;
	t_room	*tmp;

	i = 0;
	while (i < lm->nb_room)
	{
		tmp = lm->rooms[i];
		if (!(tmp->links = ft_memalloc(sizeof(t_room*) * tmp->nb_link)))
			lm_exit(lm, "alloc error", EXIT_FAILURE);
		j = 0;
		k = 0;
		while (j < lm->nb_room)
		{
			if (lm->adjmat[i][j] == 1)
			{
				tmp->links[k] = lm->rooms[j];
				++k;
			}
			++j;
		}
		++i;
	}
}
