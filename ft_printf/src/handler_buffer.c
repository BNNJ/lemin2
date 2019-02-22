/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 17:44:15 by pfragnou          #+#    #+#             */
/*   Updated: 2018/06/28 17:44:17 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** ##########################################################################
** Store characters into a buffer, and only flush it when it's full.
** The content of the buffer is written in the case of the printf functions,
** and stored into a string for the sprintf functions.
** The number of characters flushed is added to buf->ret.
** ##########################################################################
*/

static int	ftpf_strjoin(t_buf *buf)
{
	char	*new_str;

	if (!(new_str = (char*)malloc(buf->ret + buf->cursor)))
		return (0);
	ftpf_memcpy(new_str, *buf->str, buf->ret);
	ftpf_memcpy(new_str + buf->ret, buf->content, buf->cursor);
	new_str[buf->ret + buf->cursor] = '\0';
	if (*buf->str)
		free(*buf->str);
	*buf->str = new_str;
	return (1);
}

/*
** strmode 0 for regular printf, 1 for asprintf, and 2 for sprintf
*/

void		ftpf_buffer_flush(t_buf *buf)
{
	if (buf->strmode == 0)
		buf->ret += write(buf->fd, buf->content, buf->cursor);
	else if (buf->strmode == 1)
		buf->ret += ftpf_strjoin(buf);
	else if (buf->strmode == 2)
	{
		ftpf_memcpy(*(buf->str) + buf->ret, buf->content, buf->cursor);
		(*buf->str)[buf->ret + buf->cursor] = 0;
		buf->ret += buf->cursor;
	}
	else if (buf->strmode == 3)
	{
		if (buf->ret + buf->cursor >= buf->size)
			buf->cursor = buf->size - buf->ret - 1;
		ftpf_memcpy(*(buf->str) + buf->ret, buf->content, buf->cursor);
		(*buf->str)[buf->ret + buf->cursor] = 0;
		buf->ret += buf->cursor;
	}
	buf->cursor = 0;
}

/*
** Add characters from str to the buffer, up to a null or % character
*/

int			ftpf_buffer_literal(const char *str, t_buf *buf)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '%')
	{
		if (buf->cursor == BUFFSIZE)
			ftpf_buffer_flush(buf);
		buf->content[buf->cursor] = str[i];
		++buf->cursor;
		++i;
	}
	return (i);
}

/*
** Add up to [precision] characters to the buffer, ot up to a null character
*/

void		ftpf_buffer_copy(const char *str, t_buf *buf, int precision)
{
	int	i;

	i = 0;
	while (i < precision && str[i])
	{
		if (buf->cursor == BUFFSIZE)
			ftpf_buffer_flush(buf);
		buf->content[buf->cursor] = str[i];
		++buf->cursor;
		++i;
	}
}

/*
** Add [size] character c to the buffer
*/

void		ftpf_buffer_fill(t_buf *buf, char c, size_t size)
{
	while (size > 0)
	{
		if (buf->cursor == BUFFSIZE)
			ftpf_buffer_flush(buf);
		buf->content[buf->cursor] = c;
		++buf->cursor;
		--size;
	}
}
