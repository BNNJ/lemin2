/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_crossprod.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 14:21:42 by pfragnou          #+#    #+#             */
/*   Updated: 2018/08/20 14:21:43 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3	ft_vec3_crossprod(const t_vec3 *v1, const t_vec3 *v2)
{
	t_vec3	ret;

	ret.x = v1->y * v2->z - v1->z * v2->y;
	ret.y = v1->z * v2->x - v1->x * v2->z;
	ret.z = v1->x * v2->y - v1->y * v2->x;
	return (ret);
}
