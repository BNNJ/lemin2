/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 16:53:27 by pfragnou          #+#    #+#             */
/*   Updated: 2018/06/28 16:53:29 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ftpf_atoi(const char *str)
{
	short				sign;
	unsigned long long	result;

	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		++str;
	sign = (*str == '-' || *str == '+') ? -(*str++ - 44) : 1;
	while (*str && *str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	return (result * sign);
}

void	*ftpf_memset(void *b, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char*)(b + i) = (unsigned char)c;
		++i;
	}
	return (b);
}

int		ftpf_strlen(const char *str)
{
	int	len;

	len = 0;
	if (str)
		while (str[len])
			++len;
	return (len);
}

int		ftpf_findchar(const char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

void	*ftpf_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (src)
		while (i < n)
		{
			*(unsigned char*)(dst + i) = *(unsigned char*)(src + i);
			++i;
		}
	return (dst);
}
