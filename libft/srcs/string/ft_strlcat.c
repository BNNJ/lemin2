/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 17:38:32 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/04 17:38:34 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len + 1 < size)
	{
		i = 0;
		while (i < size - 1 - dst_len && src[i])
		{
			dst[dst_len + i] = src[i];
			++i;
		}
		dst[dst_len + i] = '\0';
	}
	return (dst_len > size ? src_len + size : src_len + dst_len);
}
