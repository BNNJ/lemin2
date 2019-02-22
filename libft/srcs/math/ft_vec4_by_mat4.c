/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec4_by_mat4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 19:11:56 by pfragnou          #+#    #+#             */
/*   Updated: 2018/08/21 19:11:58 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec4	ft_vec4_by_mat4(t_vec4 *v, t_mat4 *m)
{
	t_vec4	victor;

	victor.x = ft_vec4_scalprod(v, &m->x);
	victor.y = ft_vec4_scalprod(v, &m->y);
	victor.z = ft_vec4_scalprod(v, &m->z);
	victor.w = ft_vec4_scalprod(v, &m->w);
	return (victor);
}
