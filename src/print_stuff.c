/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 21:28:57 by pfragnou          #+#    #+#             */
/*   Updated: 2019/02/18 21:28:57 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_ants_mat(t_lm *lm)
{
	int		i;
	int		j;

	ft_printf("number of ants : %d\nstart : %s\n", lm->nb_ant, lm->start->name);
	ft_printf("end : %s\nnumber of rooms : %d\n", lm->end->name, lm->nb_room);
	if (lm->adjmat)
	{
		i = 0;
		ft_printf("%{blue}matrix%{reset}\n");
		while (i < lm->nb_room)
		{
			j = 0;
			ft_printf("%d	", i + 1);
			while (j < lm->nb_room)
			{
				ft_printf(lm->adjmat[i][j] ? "%{bold:red}%d%{reset} " : "%d ",
					lm->adjmat[i][j]);
				++j;
			}
			ft_printf("\n");
			++i;
		}
	}
}

void	print_rooms(t_lm *lm)
{
	int		i;
	int		j;

	i = 0;
	while (i < lm->nb_room)
	{
		ft_printf("  room #%d\n  name : %s\n  link nb : %d\n  coords : %d,%d\n",
			i, lm->rooms[i]->name, lm->rooms[i]->nb_link,
			lm->rooms[i]->coord.x, lm->rooms[i]->coord.y);
		j = 0;
		while (j < lm->rooms[i]->nb_link)
		{
			ft_printf("	link %d : %s\n", j, lm->rooms[i]->links[j]->name);
			++j;
		}
		ft_printf("##############\n");
		++i;
	}
}

void	print_paths(t_lm *lm)
{
	int		i;
	t_room	*tmp;

	i = 0;
	while (i < lm->nb_path)
	{
		tmp = lm->paths[i].room;
		ft_printf("path %d :\n\t", i);
		while (tmp)
		{
			ft_printf("%s ", tmp->name);
			tmp = tmp->next;
		}
		ft_printf("\n\t");
		tmp = lm->paths[i].end;
		while (tmp)
		{
			ft_printf("%s ", tmp->name);
			tmp = tmp->prev;
		}
		ft_printf("\n\tlen : %d, end : %s\n", lm->paths[i].len,
			lm->paths[i].end->name);
		ft_printf("############\n");
		++i;
	}
}

void	print_stuff(t_lm *lm)
{
	ft_printf("\n###########################\n");
	print_ants_mat(lm);
	ft_printf("###########################\n");
	print_rooms(lm);
	ft_printf("###########################\n");
	print_paths(lm);
}
