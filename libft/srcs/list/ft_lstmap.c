/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 05:53:17 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/07 05:53:18 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;

	new = NULL;
	if (lst != NULL)
	{
		new = ft_lstnew(lst->content, lst->content_size);
		new = f(new);
		new->next = ft_lstmap(lst->next, f);
		return (new);
	}
	else
	{
		free(new);
		return (NULL);
	}
}
