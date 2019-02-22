/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorted_list_merge.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 03:02:34 by pfragnou          #+#    #+#             */
/*   Updated: 2018/08/23 03:02:35 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	add_node(t_list *link, t_list *list)
{
	if (*list)
	{
		while ((*list)->next)
			list = (*list)->next;
		(*list)->next = link;
		(*link)->next = NULL;
	}
	else
		*list = link;
}

void	ft_sorted_list_merge(t_list **begin_list1,
	t_list *begin_list2, int (*cmp)())
{
	t_list	*new_list;
	t_list	*tmp;

	while (begin_list1 && begin_list2)
	{
		if (cmp(*begin_list1, begin_list2) > 0)
		{
			tmp = (*begin_list1)->next;
			add_node(*begin_list1, new_list);
			*begin_list1 = tmp;
		}
		else
		{
			tmp = begin_list2->next;
			add_node(begin_list2, new_list);
			begin_list2 = tmp;
		}
	}
	begin_list1 = &new_list;
}
