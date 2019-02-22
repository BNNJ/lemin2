/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 13:56:32 by pfragnou          #+#    #+#             */
/*   Updated: 2018/05/23 13:56:35 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ulltoa_base(unsigned long long n, char base_len, char opt, int pad)
{
	char	*str;
	int		i;
	char	*base;
	int		tmp;

	i = pad < 65 ? 65 : pad;
	tmp = i;
	if (!(str = ft_strnew(i))
		|| !(base = ft_strdup(opt == 1
			? "0123456789ABCDEF" : "0123456789abcdef")))
		return (NULL);
	while (n)
	{
		str[i] = base[n % base_len];
		n /= base_len;
		--i;
	}
	while (tmp - i < pad)
		str[i--] = '0';
	ft_strdel(&base);
	return (ft_strsub_f(str, i + 1, tmp - i));
}
