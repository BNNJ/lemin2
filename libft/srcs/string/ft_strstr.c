/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:24:59 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/04 15:25:01 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *haystack, const char *needle)
{
	if (!*needle)
		return ((char*)haystack);
	if (!*haystack)
		return (0);
	return ((*needle == *haystack
		&& ft_strstr(haystack + 1, needle + 1) == haystack + 1)
		? (char*)haystack : ft_strstr(haystack + 1, needle));
}
