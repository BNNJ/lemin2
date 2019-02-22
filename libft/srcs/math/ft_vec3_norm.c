/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 01:49:59 by pfragnou          #+#    #+#             */
/*   Updated: 2018/08/20 01:50:00 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vec3_norm(t_vec3 *v)
{
	float	len;

	len = ft_vec3_len(v);
	if (len >= 0.00001f)
	{
		v->x /= len;
		v->y /= len;
		v->z /= len;
	}
}