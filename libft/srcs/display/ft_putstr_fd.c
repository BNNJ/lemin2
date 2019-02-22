/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 02:24:45 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/06 02:24:48 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>

void	ft_putstr_fd(char const *s, int fd)
{
	size_t	len;

	len = 0;
	if (s)
	{
		while (s[len])
			++len;
		write(fd, s, len);
	}
}
