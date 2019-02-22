/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:30:43 by pfragnou          #+#    #+#             */
/*   Updated: 2018/11/07 15:30:46 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strtoi(char **str)
{
	short				sign;
	unsigned long long	result;

	result = 0;
	while ((**str >= 9 && **str <= 13) || **str == ' ')
		++*str;
	sign = (**str == '-' || **str == '+') ? -(*(*str)++ - 44) : 1;
	while (**str && **str >= '0' && **str <= '9')
		result = result * 10 + (*(*str)++ - '0');
	return (result * sign);
}
