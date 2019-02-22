/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_to_qtr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 12:11:27 by pfragnou          #+#    #+#             */
/*   Updated: 2018/08/20 12:11:28 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_qtr	ft_vec3_to_qtr(const t_vec3 *v, const double angle)
{
	t_qtr	q;

	q.v.x = v->x * sin(angle / 2.0);
	q.v.y = v->y * sin(angle / 2.0);
	q.v.z = v->z * sin(angle / 2.0);
	q.w = cos(angle / 2.0);
	return (q);
}
