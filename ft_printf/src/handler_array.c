/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 12:17:45 by pfragnou          #+#    #+#             */
/*   Updated: 2018/07/28 12:17:47 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ftpf_handle_int_array(t_par *p, va_list ap, t_buf *buf)
{
	size_t	size;
	size_t	i;
	int		*array;
	long	tmp;

	i = 0;
	array = va_arg(ap, int*);
	size = va_arg(ap, size_t);
	while (i < size)
	{
		p->precision = 1;
		tmp = (long)array[i];
		while (tmp /= 10)
			++p->precision;
		tmp = (long)array[i++];
		if (tmp < 0)
		{
			tmp *= -1;
			ftpf_buffer_fill(buf, '-', 1);
		}
		ftpf_umaxtoa_base(tmp, p->precision, p, buf);
		if (i < size)
			ftpf_buffer_literal(p->flags & F_HASH ? ", " : "\n", buf);
	}
	return (1);
}

int		ftpf_handle_str_array(t_par *p, va_list ap, t_buf *buf)
{
	size_t	size;
	size_t	i;
	char	**array;

	i = 0;
	array = va_arg(ap, char**);
	size = va_arg(ap, size_t);
	while (i < size && array[i])
	{
		ftpf_buffer_copy(array[i], buf, ftpf_strlen(array[i]));
		++i;
		if (i < size)
			ftpf_buffer_literal(p->flags & F_HASH ? ", " : "\n", buf);
	}
	return (1);
}
