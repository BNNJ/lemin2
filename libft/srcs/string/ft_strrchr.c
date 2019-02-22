/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 20:37:12 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/04 20:37:14 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = 0;
	while (s[len])
		++len;
	while (len && s[len] != (char)c)
		--len;
	if (s[len] == (char)c)
		return (((char*)(s + len)));
	return (NULL);
}
