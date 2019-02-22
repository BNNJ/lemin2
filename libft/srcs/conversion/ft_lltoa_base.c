/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 13:22:45 by pfragnou          #+#    #+#             */
/*   Updated: 2018/05/24 13:22:47 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lltoa_base(long long n, char base_len, char opt, int pad)
{
	char	*str;
	char	*base;
	int		i;
	char	sign;
	int		tmp;

	i = pad < 65 ? 65 : pad + 1;
	tmp = i;
	sign = n >= 0 ? '0' : '-';
	if (!(str = ft_strnew(i))
		|| !(base = ft_strdup(opt == 1
			? "0123456789ABCDEF" : "0123456789abcdef")))
		return (NULL);
	while (n)
	{
		str[i] = n >= 0 ? base[n % base_len] : base[-(n % base_len)];
		n /= base_len;
		--i;
	}
	while (tmp - i < pad)
		str[i--] = '0';
	str[i] = sign;
	ft_strdel(&base);
	return (ft_strsub_f(str, sign == '0' ? i + 1 : i,
		sign == '0' ? tmp - i : tmp - i + 1));
}
