/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tstr_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 01:14:19 by pfragnou          #+#    #+#             */
/*   Updated: 2018/05/17 01:14:23 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_string	*help(t_string *s1, t_string *s2)
{
	t_string	*str;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!(str = ft_tstr_new(s1->len + s2->len)))
		return (NULL);
	while (i < s1->len)
	{
		str->content[i] = s1->content[i];
		++i;
	}
	while (j < s2->len)
	{
		str->content[i + j] = s2->content[j];
		++j;
	}
	return (str);
}

t_string	*ft_tstr_join(t_string *s1, t_string *s2, int opt)
{
	t_string	*str;

	if (!s1 && !s2)
		return (NULL);
	else if (s1 && !s2)
		return (opt == 1 || opt == 3 ? s1 : ft_tstr_dup(s1));
	else if (!s1 && s2)
		return (opt == 2 || opt == 3 ? s2 : ft_tstr_dup(s2));
	str = help(s1, s2);
	str->len = s1->len + s2->len;
	if (opt == 1 || opt == 3)
		ft_tstr_del(&s1);
	if (opt == 2 || opt == 3)
		ft_tstr_del(&s2);
	return (str);
}
