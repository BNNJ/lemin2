/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tstr_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 01:14:40 by pfragnou          #+#    #+#             */
/*   Updated: 2018/05/17 01:14:43 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_string	*ft_tstr_sub(t_string *s, size_t start, size_t len, int f)
{
	t_string		*substr;
	size_t			i;

	i = 0;
	if (!s)
		return (NULL);
	if (!(substr = ft_tstr_new(len)))
		return (0);
	while (i < len && i < s->len)
	{
		substr->content[i] = s->content[start + i];
		++i;
	}
	substr->len = i;
	if (f == 1)
		ft_tstr_del(&s);
	return (substr);
}
