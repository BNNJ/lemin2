/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qtr_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 12:11:51 by pfragnou          #+#    #+#             */
/*   Updated: 2018/08/20 12:11:52 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_qtr	ft_qtr_new(const double x, const double y,
	const double z, const double w)
{
	t_qtr	q;

	q.v.x = x;
	q.v.y = y;
	q.v.z = z;
	q.w = w;
	return (q);
}
