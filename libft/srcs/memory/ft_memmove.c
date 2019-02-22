/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 18:51:41 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/04 18:51:46 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	uint8_t	*mem_dst;
	uint8_t	*mem_src;

	mem_dst = (uint8_t*)dst;
	mem_src = (uint8_t*)src;
	if (dst > src)
		while (n--)
			*(mem_dst + n) = *(mem_src + n);
	else if (dst < src)
		ft_memcpy(dst, src, n);
	return (dst);
}
