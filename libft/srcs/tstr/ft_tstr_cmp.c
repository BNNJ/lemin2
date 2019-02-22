/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tstr_cmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 04:41:46 by pfragnou          #+#    #+#             */
/*   Updated: 2018/05/17 04:41:49 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tstr_cmp(const t_string *s1, const t_string *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (i < s1->len && i < s2->len && s1->content[i] == s2->content[i])
		++i;
	return ((unsigned char)s1->content[i] - (unsigned char)s2->content[i]);
}
