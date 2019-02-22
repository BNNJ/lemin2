/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 18:10:33 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/04 18:10:36 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	uint8_t	*mem;
	uint8_t	ch;

	mem = (uint8_t*)b;
	ch = (uint8_t)c;
	while (n)
	{
		*mem = ch;
		++mem;
		--n;
	}
	return (b);
}
