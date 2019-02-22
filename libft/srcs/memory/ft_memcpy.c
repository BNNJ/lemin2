/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 18:35:31 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/04 18:35:34 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	uint8_t	*mem_dst;
	uint8_t	*mem_src;

	mem_src = (uint8_t*)src;
	mem_dst = (uint8_t*)dst;
	while (n)
	{
		*mem_dst = *mem_src;
		++mem_src;
		++mem_dst;
		--n;
	}
	return (dst);
}
