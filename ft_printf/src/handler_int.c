/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 14:10:12 by pfragnou          #+#    #+#             */
/*   Updated: 2018/06/29 14:10:14 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Directly from int to buffer, makes things a bit simpler and faster.
** The precision is handled there.
** UCBASE : Upper case base, 0123456789ABCDEF
** LCBASE : Lower case base, 0123456789abcdef
*/

void				ftpf_umaxtoa_base(uintmax_t nb, size_t len,
	t_par *p, t_buf *buf)
{
	int			i;
	char		buffer[UINTMAX_WIDTH];
	char		base[16];

	i = UINTMAX_WIDTH;
	ftpf_memcpy(base, p->type >= 'A' && p->type <= 'Z' ? UCBASE : LCBASE, 16);
	if (p->precision > len)
	{
		ftpf_buffer_fill(buf, '0', p->precision - len);
		p->precision -= (p->precision - len);
	}
	while (p->precision)
	{
		buffer[--i] = base[nb % p->base];
		nb /= p->base;
		--p->precision;
	}
	ftpf_buffer_copy(buffer + i, buf, UINTMAX_WIDTH - i);
}

static uintmax_t	ftpf_convert_int(t_par *p, va_list ap)
{
	intmax_t	nb;
	uintmax_t	unb;

	nb = 0;
	if (p->e_mod == HH)
		nb = (char)va_arg(ap, int);
	else if (p->e_mod == H)
		nb = (short)va_arg(ap, int);
	else if (p->e_mod == NONE)
		nb = va_arg(ap, int);
	else if (p->e_mod == L)
		nb = (long)va_arg(ap, intmax_t);
	else if (p->e_mod == LL)
		nb = (long long)va_arg(ap, intmax_t);
	else if (p->e_mod == Z)
		nb = (ssize_t)va_arg(ap, intmax_t);
	else if (p->e_mod == J)
		nb = va_arg(ap, intmax_t);
	unb = (nb >= 0) ? nb : -nb;
	p->prefix[0] = nb < 0 ? '-' : p->prefix[0];
	return (unb);
}

static uintmax_t	ftpf_convert_unsigned(t_par *p, va_list ap)
{
	uintmax_t	nb;

	nb = 0;
	if (p->e_mod == HH)
		nb = (unsigned char)va_arg(ap, unsigned int);
	else if (p->e_mod == H)
		nb = (unsigned short)va_arg(ap, unsigned int);
	else if (p->e_mod == NONE)
		nb = va_arg(ap, unsigned int);
	else if (p->e_mod == L)
		nb = (unsigned long)va_arg(ap, uintmax_t);
	else if (p->e_mod == LL)
		nb = (unsigned long long)va_arg(ap, uintmax_t);
	else if (p->e_mod == Z)
		nb = (size_t)va_arg(ap, uintmax_t);
	else if (p->e_mod == J)
		nb = va_arg(ap, uintmax_t);
	if (p->base == 10)
		ftpf_memset(p->prefix, 0, 2);
	return (nb);
}

/*
** Sets the precision to be used in umaxtoa_base() by first picking either
** p->precision or len (the number of digits in nb) depending on which is bigger
** then adds 1 for octal base if F_HASH has been enabled.
** Of course, zero being an exception, we get this mess of conditionals.
**
** Don't ask me why i handled it like that instead of using the prefix like
** the other bases : The man says it's done like that, so i did it like that.
*/

static size_t		ftpf_setup_int(uintmax_t nb, t_par *p)
{
	size_t		len;
	uintmax_t	tmp;

	len = 1;
	tmp = nb;
	while (tmp /= p->base)
		++len;
	if (!(p->flags & F_PRECI))
		p->precision = len;
	else if (p->precision != 0 || nb != 0)
		p->precision = p->precision > len ? p->precision : len;
	p->precision += (p->type == 'o' || p->type == 'O') && p->flags & F_HASH
		&& len >= p->precision && !(!nb && p->precision);
	tmp = nb || p->flags & F_PLUS || p->flags & F_SPACE
		? p->precision + ftpf_strlen(p->prefix) : p->precision;
	p->width = p->width > tmp ? p->width - tmp : 0;
	return (len);
}

int					ftpf_handle_int(t_par *p, va_list ap, t_buf *buf)
{
	uintmax_t	nb;
	size_t		len;

	nb = (ftpf_findchar("oOuUxXb", p->type) >= 0 || p->flags & F_BIN)
		? ftpf_convert_unsigned(p, ap) : ftpf_convert_int(p, ap);
	if (p->flags & F_BIN)
		return (ftpf_handle_bin(&nb, p, buf));
	len = ftpf_setup_int(nb, p);
	if (p->flags & F_WIDTH)
		ftpf_buffer_fill(buf, ' ', p->width);
	if (!(p->type == 'o' || p->type == 'O'
		|| (!nb && (p->type == 'x' || p->type == 'X'))))
		ftpf_buffer_literal(p->prefix, buf);
	if (p->flags & F_ZERO)
		ftpf_buffer_fill(buf, '0', p->width);
	ftpf_umaxtoa_base(nb, len, p, buf);
	if (p->flags & F_MINUS)
		ftpf_buffer_fill(buf, ' ', p->width);
	return (1);
}
