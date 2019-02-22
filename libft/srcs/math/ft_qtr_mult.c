/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qtr_mult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 14:37:34 by pfragnou          #+#    #+#             */
/*   Updated: 2018/08/20 14:37:35 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_qtr	ft_qtr_mult(const t_qtr *q1, const t_qtr *q2)
{
	t_qtr	q;
	t_vec3	v;
	t_vec3	tmp;

	q.w = q1->w * q2->w - ft_vec3_scalprod(&q1->v, &q2->v);
	v = ft_vec3_crossprod(&q1->v, &q2->v);
	tmp = ft_vec3_by_scalar(&q2->v, q1->w);
	v = ft_vec3_add(&v, &tmp);
	tmp = ft_vec3_by_scalar(&q1->v, q2->w);
	q.v = ft_vec3_add(&v, &tmp);
	return (q);
}
