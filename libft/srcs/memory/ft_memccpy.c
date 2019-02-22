/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:54:43 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/05 15:54:49 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	uint8_t	*mem_dst;
	uint8_t	*mem_src;
	uint8_t	ch;

	mem_src = (uint8_t*)src;
	mem_dst = (uint8_t*)dst;
	ch = (uint8_t)c;
	while (n--)
	{
		*mem_dst = *mem_src;
		++mem_dst;
		if (*mem_src == ch)
			return (mem_dst);
		++mem_src;
	}
	return (NULL);
}
