/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tstr_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 01:14:53 by pfragnou          #+#    #+#             */
/*   Updated: 2018/05/17 01:14:56 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_tstr_to_str(t_string *str)
{
	char	*new;
	size_t	i;

	i = 0;
	if (!(new = ft_strnew(str->len)))
		return (NULL);
	while (i < str->len)
	{
		new[i] = str->content[i];
		++i;
	}
	return (new);
}
