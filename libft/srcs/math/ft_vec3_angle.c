/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_angle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 13:54:48 by pfragnou          #+#    #+#             */
/*   Updated: 2018/08/20 13:54:49 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_vec3_angle(const t_vec3 *v1, const t_vec3 *v2)
{
	return (acos(ft_vec3_scalprod(v1, v2)
		/ (ft_vec3_len(v1) * ft_vec3_len(v2))) * (180 / M_PI));
}
