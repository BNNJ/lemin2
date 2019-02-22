/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_by_scalar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 13:48:31 by pfragnou          #+#    #+#             */
/*   Updated: 2018/08/20 13:48:32 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3	ft_vec3_by_scalar(const t_vec3 *v, const double s)
{
	t_vec3	ret;

	ret.x = v->x * s;
	ret.y = v->y * s;
	ret.z = v->z * s;
	return (ret);
}
