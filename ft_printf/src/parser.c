/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 12:47:49 by pfragnou          #+#    #+#             */
/*   Updated: 2018/06/27 12:47:51 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Yes, it's a global array. It's not absolutely necessary, but it's faster.
** It obviously uses the conversion specifiers as indexes,
** to match them with the proper functions.
*/

static t_fct	g_functable[127] = {NULL};

static void		function_factory(void)
{
	g_functable['d'] = ftpf_handle_int;
	g_functable['D'] = ftpf_handle_int;
	g_functable['i'] = ftpf_handle_int;
	g_functable['u'] = ftpf_handle_int;
	g_functable['U'] = ftpf_handle_int;
	g_functable['o'] = ftpf_handle_int;
	g_functable['O'] = ftpf_handle_int;
	g_functable['x'] = ftpf_handle_int;
	g_functable['X'] = ftpf_handle_int;
	g_functable['b'] = ftpf_handle_int;
	g_functable['B'] = ftpf_handle_int;
	g_functable['f'] = ftpf_handle_float;
	g_functable['F'] = ftpf_handle_float;
	g_functable['c'] = ftpf_handle_char;
	g_functable['C'] = ftpf_handle_wchar;
	g_functable['s'] = ftpf_handle_str;
	g_functable['S'] = ftpf_handle_wstr;
	g_functable['p'] = ftpf_handle_ptr;
	g_functable['P'] = ftpf_handle_ptr;
	g_functable['n'] = ftpf_handle_n;
	g_functable['y'] = ftpf_handle_file;
	g_functable['t'] = ftpf_handle_int_array;
	g_functable['w'] = ftpf_handle_str_array;
}

/*
** if no conversion specifier is found, print the char that's where
** the specifier should be. With width and precision applied to it.
** Unless it's a null character.
*/

static int		no_conv(t_par *p, t_buf *buf, const char **format)
{
	if (p->type != 0)
	{
		if (p->flags & F_BIN)
			return (ftpf_handle_bin(&p->type, p, buf));
		if ((p->flags & F_WIDTH || p->flags & F_ZERO) && p->width > 1)
			ftpf_buffer_fill(buf, p->flags & F_ZERO ? '0' : ' ', p->width - 1);
		ftpf_buffer_fill(buf, p->type, 1);
		if (p->flags & F_MINUS)
			ftpf_buffer_fill(buf, ' ', p->width - 1);
	}
	else
		--*format;
	return (1);
}

/*
** cleans up the mess in the flags, by disabling those that won't be used,
** especially for width handling.
** It looks quite ugly, but it makes everything else much clearer.
*/

static void		ftpf_flags_setup(t_par *p)
{
	if (p->type == 'o' || p->type == 'O' || p->type == 'x' || p->type == 'X')
	{
		p->flags &= ~F_PLUS;
		p->flags &= ~F_SPACE;
	}
	if (p->flags & F_SPACE)
		p->prefix[0] = ' ';
	if (p->flags & F_PLUS)
		p->prefix[0] = '+';
	if ((p->flags & F_PRECI && (ftpf_findchar("dDioOuUxXpPbB", p->type) >= 0))
		|| !(p->flags & F_WIDTH) || p->flags & F_MINUS)
		p->flags &= ~F_ZERO;
	if (!(p->flags & F_WIDTH))
		p->flags &= ~F_MINUS;
	if (p->flags & F_ZERO || p->flags & F_MINUS)
		p->flags &= ~F_WIDTH;
}

/*
** First check for the display handling flag,
** then call the option parsing functions.
** Get type, throw it against the function pointers array and what sticks.
** If nothing does, then call no_conv, using the false conversion specifier
** as character.
*/

static int		ftpf_majortom(const char **format, t_par *p,
	t_buf *buf, va_list ap)
{
	int	i;

	++*format;
	if (**format == '{' && (i = ftpf_findchar(*format, '}')) >= 0)
		return (ftpf_handle_display(format, buf, i));
	ftpf_get_flags(p, format, ap);
	ftpf_get_type(p, format);
	ftpf_flags_setup(p);
	return (!g_functable[p->type]
		? no_conv(p, buf, format)
		: g_functable[p->type](p, ap, buf));
}

/*
** setup the buffer and parameters structs,
** parse format for conversion placeholders or literals
** call the appropriate function.
** flush the buffer at the end or in case of error
** (anything that shouldn't be printed supposedly isn't in the buffer)
*/

int				ftpf_groundcontrol(const char *format, va_list ap, t_buf *buf)
{
	t_par	p;

	function_factory();
	while (*format)
	{
		ftpf_memset(&p, 0, sizeof(p));
		if (*format != '%')
			format += ftpf_buffer_literal(format, buf);
		else if (!(ftpf_majortom(&format, &p, buf, ap)))
		{
			ftpf_buffer_flush(buf);
			return (-1);
		}
	}
	ftpf_buffer_flush(buf);
	return (buf->ret);
}
