/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tstr_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 01:14:30 by pfragnou          #+#    #+#             */
/*   Updated: 2018/05/17 01:14:33 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_string	*ft_tstr_new(size_t size)
{
	t_string	*str;

	if (!(str = (t_string*)malloc(sizeof(t_string))))
		return (0);
	if (!(str->content = ft_strnew(size)))
		return (0);
	str->len = size;
	return (str);
}
