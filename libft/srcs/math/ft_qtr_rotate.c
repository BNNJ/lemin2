/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qtr_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 16:29:28 by pfragnou          #+#    #+#             */
/*   Updated: 2018/08/20 16:29:29 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_vec3	ft_qtr_rotate_point(const t_qtr *q, const t_vec3 *v)
{
	t_qtr	p;
	t_qtr	inv_q;

	p.w = 0.0;
	p.v = *v;
	ft_qtr_norm((t_qtr*)q);
	inv_q = ft_qtr_invert(q);
	p = ft_qtr_mult(q, &p);
	p = ft_qtr_mult(&p, &inv_q);
	return (p.v);
}

t_vec3			ft_qtr_rotate(const t_vec3 *p, const t_vec3 *axis,
	const double angle)
{
	t_qtr	q;

	q.w = cos(angle / 2.0);
	q.v = ft_vec3_by_scalar(axis, sin(angle / 2.0));
	return (ft_qtr_rotate_point(&q, p));
}
