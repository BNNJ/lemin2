/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 19:54:39 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/04 19:54:42 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	uint8_t	*mem;
	uint8_t	ch;

	ch = (uint8_t)c;
	mem = (uint8_t*)s;
	while (n--)
	{
		if (*mem == ch)
			return ((void*)mem);
		++s;
	}
	return (NULL);
}
