/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 12:47:35 by pfragnou          #+#    #+#             */
/*   Updated: 2018/06/27 12:47:37 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_dfprintf(int fd, const char *format, va_list ap)
{
	t_buf	buf;

	ftpf_memset(&buf, 0, sizeof(buf));
	buf.strmode = 0;
	buf.fd = fd;
	return (ftpf_groundcontrol(format, ap, &buf));
}

int		ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_dfprintf(fd, format, ap);
	va_end(ap);
	return (ret);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_dfprintf(1, format, ap);
	va_end(ap);
	return (ret);
}
