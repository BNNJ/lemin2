/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:37:52 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/05 16:37:53 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	len;
	char	*str;

	len = 0;
	if (!s)
		return (NULL);
	while (s[len])
		++len;
	if (!(str = ft_strdup(s)))
		return (NULL);
	len = 0;
	while (str[len])
	{
		str[len] = f(s[len]);
		++len;
	}
	return (str);
}
