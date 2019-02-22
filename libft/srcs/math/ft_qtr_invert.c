/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qtr_invert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:44:09 by pfragnou          #+#    #+#             */
/*   Updated: 2018/08/20 15:44:10 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_qtr	ft_qtr_invert(const t_qtr *q)
{
	t_qtr	ret;
	double	len;

	ret = ft_qtr_conj(q);
	len = ft_qtr_len(q);
	ret = ft_qtr_by_scalar(q, 1.0 / len * len);
	return (ret);
}
