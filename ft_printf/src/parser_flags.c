/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 15:28:41 by pfragnou          #+#    #+#             */
/*   Updated: 2018/06/28 15:28:42 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Go through format as long as the character pointed at is something that
** can be used as an option/flag/precision/etc.
** the first 6 characters are formatting flags, ordered precisely so that
** a bitshift based on their position in the character set enables the
** matching flag.
** Then comes the dot, that fires up the precision function,
** then the digits and star, which mean minimum field width,
** and finally the length modifiers.
*/

void	ftpf_get_flags(t_par *p, const char **format, va_list ap)
{
	int i;

	i = 0;
	p->e_mod = NONE;
	while ((i = ftpf_findchar("0#+- &.123456789*hljz", **format)) >= 0)
	{
		if (i <= 5)
		{
			p->flags |= (1 << i);
			++*format;
		}
		else if (i == 6)
			ftpf_get_precision(p, format, ap);
		else if (i <= 16)
			ftpf_get_width(p, format, ap);
		else
			ftpf_get_size_flag(p, format);
	}
}

void	ftpf_get_width(t_par *p, const char **format, va_list ap)
{
	int		tmp;

	if (**format == '*')
	{
		tmp = va_arg(ap, int);
		p->flags |= tmp < 0 ? F_MINUS + F_WIDTH : F_WIDTH;
		p->width = tmp < 0 ? -tmp : tmp;
		++*format;
	}
	else if (**format >= '1' && **format <= '9')
	{
		p->width = ftpf_atoi(*format);
		while (**format >= '0' && **format <= '9')
			++*format;
		p->flags |= F_WIDTH;
	}
}

void	ftpf_get_precision(t_par *p, const char **format, va_list ap)
{
	int		tmp;

	++*format;
	if (**format == '*')
	{
		tmp = va_arg(ap, int);
		p->precision = tmp < 0 ? 0 : tmp;
		p->flags |= tmp < 0 ? 0 : F_PRECI;
		++*format;
	}
	else
	{
		p->precision = ftpf_atoi(*format);
		while ((**format >= '0' && **format <= '9') || **format == '.')
			++*format;
		p->flags |= F_PRECI;
	}
}

void	ftpf_get_size_flag(t_par *p, const char **format)
{
	if (**format == 'l')
	{
		if (p->e_mod == L)
			p->e_mod = LL;
		else
			p->e_mod = p->e_mod <= NONE ? L : p->e_mod;
	}
	else if (**format == 'h')
	{
		if (p->e_mod == H)
			p->e_mod = HH;
		else
			p->e_mod = p->e_mod <= NONE ? H : p->e_mod;
	}
	else if (**format == 'j')
		p->e_mod = p->e_mod <= LL ? J : p->e_mod;
	else
		p->e_mod = Z;
	++*format;
}

void	ftpf_get_type(t_par *p, const char **format)
{
	p->type = **format;
	++*format;
	if (p->type == 'x' || p->type == 'X' || p->type == 'p' || p->type == 'P')
	{
		p->base = 16;
		p->flags |= p->type == 'p' || p->type == 'P' ? F_HASH : 0;
		if (p->flags & F_HASH)
			ftpf_memcpy(p->prefix, p->type >= 'a' ? "0x" : "0X", 2);
		else
			p->prefix[0] = 0;
	}
	else if (p->type == 'o' || p->type == 'O')
		p->base = 8;
	else if (p->type == 'b' || p->type == 'B')
	{
		p->base = 2;
		p->flags & F_HASH && p->type == 'b'
			? ftpf_memcpy(p->prefix, "0b", 2) : 0;
	}
	else
		p->base = 10;
	if ((ftpf_findchar("SDOU", p->type) >= 0) && p->e_mod <= NONE)
		p->e_mod = L;
}
