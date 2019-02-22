/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:04:04 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/03 20:13:29 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dest;

	len = 0;
	while (s1[len])
		++len;
	if (!(dest = (char*)malloc(len + 1)))
		return (NULL);
	while (*s1)
		*dest++ = *s1++;
	*dest = '\0';
	return (dest - len);
}
