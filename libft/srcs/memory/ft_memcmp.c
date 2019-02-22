/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 20:20:10 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/04 20:20:35 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	uint8_t	*mem1;
	uint8_t	*mem2;

	mem1 = (uint8_t*)s1;
	mem2 = (uint8_t*)s2;
	if (n == 0)
		return (0);
	while (*mem1 == *mem2 && --n)
	{
		++mem1;
		++mem2;
	}
	return (*mem1 - *mem2);
}
