/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 02:21:26 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/06 02:21:28 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>

void	ft_putendl(char const *s)
{
	size_t	len;

	len = 0;
	if (s)
	{
		while (s[len])
			++len;
		write(1, s, len);
		write(1, "\n", 1);
	}
}
