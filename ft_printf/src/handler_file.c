/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 12:17:29 by pfragnou          #+#    #+#             */
/*   Updated: 2018/07/28 12:17:30 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ftpf_handle_file(t_par *p, va_list ap, t_buf *buf)
{
	int		fd;
	int		len;
	char	str[64];

	if (!(fd = open(va_arg(ap, char*), O_RDONLY)))
		return (0);
	while ((len = read(fd, str, 64)) > 0)
		ftpf_buffer_copy(str, buf, len);
	close(fd);
	return (len >= 0);
}
