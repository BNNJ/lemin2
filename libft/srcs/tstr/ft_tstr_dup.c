/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tstr_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 01:13:53 by pfragnou          #+#    #+#             */
/*   Updated: 2018/05/17 01:13:58 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_string	*ft_tstr_dup(t_string *s1)
{
	size_t		i;
	t_string	*new;

	i = 0;
	if (!s1)
		return (0);
	if (!(new = ft_tstr_new(s1->len)))
		return (0);
	while (i < s1->len)
	{
		new->content[i] = s1->content[i];
		++i;
	}
	new->len = s1->len;
	return (new);
}
