/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tstr_findchar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 01:14:09 by pfragnou          #+#    #+#             */
/*   Updated: 2018/05/17 01:14:11 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tstr_findchar(t_string *str, char c)
{
	size_t	i;

	i = 0;
	if (!str || !str->content)
		return (-1);
	while (i < str->len)
	{
		if (str->content[i] == c)
			return (i);
		++i;
	}
	return (-1);
}
