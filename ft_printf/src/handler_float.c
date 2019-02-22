/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 03:40:52 by pfragnou          #+#    #+#             */
/*   Updated: 2018/07/02 03:40:54 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static double		ftpf_pow10(int pow)
{
	int		i;
	double	result;
	double	nb;

	i = 1;
	result = 1.0;
	nb = 10.0;
	if (pow < 0)
		return (0);
	while (i <= pow)
	{
		result = result * nb;
		++i;
	}
	return (result);
}

/*
** Converts the floating part to an int.
*/

static uintmax_t	ftpf_dectoi(double f, t_par *p)
{
	uintmax_t	n;
	size_t		i;
	uintmax_t	tmp;

	f -= (double)(long)f;
	i = 1;
	n = 0;
	while (i <= p->precision)
	{
		n = n * 10 + ((uintmax_t)(f * ftpf_pow10(i)) % 10);
		++i;
	}
	tmp = (uintmax_t)(f * ftpf_pow10(i));
	if (tmp % 10 > 5)
		++n;
	else if (tmp % 10 == 5)
	{
		tmp = (uintmax_t)(f * ftpf_pow10(i + 2));
		if (tmp % 100 > 0)
			++n;
	}
	return (n);
}

/*
** Split the float into two ints, treated separately.
*/

static void			ftpf_ftoa(double f, size_t len, t_par *p, t_buf *buf)
{
	uintmax_t	dec;
	size_t		tmp;

	tmp = p->precision;
	p->precision = len;
	f = f < 0 ? -f : f;
	ftpf_umaxtoa_base((uintmax_t)f, len, p, buf);
	p->precision = tmp;
	if (p->precision > 0 || p->flags & F_HASH)
		ftpf_buffer_fill(buf, '.', 1);
	dec = ftpf_dectoi(f, p);
	ftpf_umaxtoa_base(dec, p->precision, p, buf);
}

static size_t		ftpf_setup_float(double f, t_par *p)
{
	size_t		len;
	uintmax_t	tmp;
	char		minus;
	char		dot;

	tmp = f < 0 ? (uintmax_t)-f : (uintmax_t)f;
	len = 1;
	while (tmp /= 10)
		++len;
	p->precision = p->flags & F_PRECI ? p->precision : 6;
	dot = p->precision > 0 || p->flags & F_HASH;
	minus = f < 0;
	p->width = p->width > len + p->precision + minus + dot
		? p->width - len - p->precision - minus - dot : 0;
	return (len);
}

int					ftpf_handle_float(t_par *p, va_list ap, t_buf *buf)
{
	double	f;
	size_t	len;

	f = va_arg(ap, double);
	if (p->flags & F_BIN)
	{
		return (p->type == 'F'
			? ftpf_handle_bin(&f, p, buf)
			: ftpf_handle_bin((float*)&f, p, buf));
	}
	len = ftpf_setup_float(f, p);
	if (p->flags & F_WIDTH)
		ftpf_buffer_fill(buf, ' ', p->width);
	if (f < 0)
		ftpf_buffer_fill(buf, '-', 1);
	if (p->flags & F_ZERO)
		ftpf_buffer_fill(buf, '0', p->width);
	ftpf_ftoa(f, len, p, buf);
	if (p->flags & F_MINUS)
		ftpf_buffer_fill(buf, ' ', p->width);
	return (1);
}
