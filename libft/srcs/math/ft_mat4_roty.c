/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4_roty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 19:07:04 by pfragnou          #+#    #+#             */
/*   Updated: 2018/08/21 19:07:05 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_mat4	ft_mat4_roty(double angle)
{
	t_mat4	m;
	double	cosx;
	double	sinx;

	cosx = cos(angle * RAD);
	sinx = sin(angle * RAD);
	m.x = (t_vec4){cosx, 0.0, -sinx, 0.0};
	m.y = (t_vec4){0.0, 0.0, 0.0, 0.0};
	m.z = (t_vec4){sinx, 0.0, cosx, 0.0};
	m.w = (t_vec4){0.0, 0.0, 0.0, 0.0};
	return (m);
}
