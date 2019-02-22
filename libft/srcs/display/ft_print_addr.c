/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 01:27:00 by pfragnou          #+#    #+#             */
/*   Updated: 2018/05/17 01:27:02 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_print_addr_help(unsigned long long nbr)
{
	char	*base;

	base = "0123456789abcdef";
	if (nbr / 16 > 0)
		ft_print_addr_help(nbr / 16);
	write(1, base + nbr % 16, 1);
}

void		ft_print_addr(const void *ptr)
{
	write(1, "0x", 2);
	ft_print_addr_help((unsigned long long)ptr);
}
