/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 14:50:06 by pfragnou          #+#    #+#             */
/*   Updated: 2018/07/01 14:50:08 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Returns the number of bytes to be written into the buffer.
** If a precision was given, make sure not to cut a multibyte char,
** by checking if the length of each character after conversion bring the total
** length above the precision.
** If the argument is NULL, sets the default precision to 6, unless a precision
** was given.
*/

static int		ftpf_wstrlen(wchar_t *str, t_par *p)
{
	int	len;
	int	wc_len;

	len = 0;
	if (str)
	{
		while (*str)
		{
			if (*str <= 0xff && MB_CUR_MAX == 1)
				wc_len = 1;
			else
				wc_len = 1 + (*str > 0x7f) + (*str > 0x7ff) + (*str > 0xffff);
			if (*str < -1 || *str > 0x10ffff
				|| (*str >= 0xd800 && *str <= 0xdfff)
				|| wc_len > MB_CUR_MAX)
				return (-1);
			if (p->flags & F_PRECI && len + wc_len > p->precision)
				return (len);
			len += wc_len;
			++str;
		}
		return (len);
	}
	else
		return (p->flags & F_PRECI && p->precision < 6 ? p->precision : 6);
}

static void		ftpf_buffer_wstr(wchar_t *str, t_par *p, t_buf *buf)
{
	char	tmp[5];
	size_t	i;
	char	char_len;

	i = 0;
	while (i < p->precision && *str)
	{
		ftpf_memset(tmp, 0, 5);
		ftpf_convert_wchar(*str, tmp);
		char_len = ftpf_wchar_len(*str);
		ftpf_buffer_copy(tmp, buf, char_len);
		i += char_len;
		++str;
	}
}

int				ftpf_handle_wstr(t_par *p, va_list ap, t_buf *buf)
{
	wchar_t	*str;
	int		len;

	str = va_arg(ap, wchar_t*);
	if ((len = ftpf_wstrlen(str, p)) < 0)
		return (0);
	p->precision = len;
	if (p->width > p->precision && !(p->flags & F_MINUS))
		ftpf_buffer_fill(buf, p->flags & F_ZERO ? '0' : ' ',
			p->width - p->precision);
	if (!str)
		ftpf_buffer_copy("(null)", buf, p->precision);
	else
		ftpf_buffer_wstr(str, p, buf);
	if (p->width > len && p->flags & F_MINUS)
		ftpf_buffer_fill(buf, ' ', p->width - p->precision);
	return (1);
}

int				ftpf_handle_str(t_par *p, va_list ap, t_buf *buf)
{
	char	*str;
	size_t	len;

	if (p->e_mod > NONE)
		return (ftpf_handle_wstr(p, ap, buf));
	str = va_arg(ap, char*);
	len = str ? ftpf_strlen(str) : 6;
	p->precision = p->flags & F_PRECI && p->precision < len
		? p->precision : len;
	if (p->width > p->precision && !(p->flags & F_MINUS))
		ftpf_buffer_fill(buf, p->flags & F_ZERO ? '0' : ' ',
			p->width - p->precision);
	ftpf_buffer_copy(str ? str : "(null)", buf, p->precision);
	if (p->width > p->precision && p->flags & F_MINUS)
		ftpf_buffer_fill(buf, ' ', p->width - p->precision);
	return (1);
}
