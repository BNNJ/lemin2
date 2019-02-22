/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 16:58:06 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/05 16:58:07 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
		str[len] = f(len, s[len]);
		++len;
	}
	return (str);
}
