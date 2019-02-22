/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec4_by_scalar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 21:34:29 by pfragnou          #+#    #+#             */
/*   Updated: 2018/08/21 21:34:30 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec4	ft_vec4_by_scalar(const t_vec4 *v, const double s)
{
	t_vec4	ret;

	ret.x = v->x * s;
	ret.y = v->y * s;
	ret.z = v->z * s;
	ret.w = v->w * s;
	return (ret);
}
