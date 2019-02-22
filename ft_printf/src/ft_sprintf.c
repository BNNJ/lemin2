/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 02:21:51 by pfragnou          #+#    #+#             */
/*   Updated: 2018/07/19 02:21:52 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Allocate a string to store the formated output into
*/

int		ft_asprintf(char **str, const char *format, ...)
{
	t_buf	buf;
	int		ret;
	va_list	ap;

	if (!(*str = (char*)malloc(0)))
		return (-1);
	ftpf_memset(&buf, 0, sizeof(buf));
	buf.strmode = 1;
	buf.fd = 1;
	buf.str = str;
	va_start(ap, format);
	ret = ftpf_groundcontrol(format, ap, &buf);
	va_end(ap);
	*str = *buf.str;
	return (ret);
}

/*
** Store the formated string into a string given as parameter.
** The string must be big enough to hold everything.
*/

int		ft_sprintf(char *str, const char *format, ...)
{
	va_list	ap;
	t_buf	buf;
	int		ret;

	ftpf_memset(&buf, 0, sizeof(buf));
	buf.strmode = 2;
	buf.fd = 1;
	buf.str = &str;
	va_start(ap, format);
	ret = ftpf_groundcontrol(format, ap, &buf);
	va_end(ap);
	return (ret);
}

/*
** Store up to n characters of a formated string in str.
** A terminating null character will always be added, str should
** therefore be the lenth of the formated string + 1
*/

int		ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list	ap;
	t_buf	buf;
	int		ret;

	ftpf_memset(&buf, 0, sizeof(buf));
	buf.strmode = 3;
	buf.fd = 1;
	buf.str = &str;
	buf.size = size;
	va_start(ap, format);
	ret = ftpf_groundcontrol(format, ap, &buf);
	va_end(ap);
	return (ret);
}
