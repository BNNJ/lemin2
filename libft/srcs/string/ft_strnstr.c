/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 20:43:14 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/04 20:43:16 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (!*needle)
		return ((char*)haystack);
	if (!*haystack)
		return (NULL);
	if (len == 0)
		return (NULL);
	return ((*needle == *haystack
		&& ft_strnstr(haystack + 1, needle + 1, len - 1) == haystack + 1)
		? (char*)haystack : ft_strnstr(haystack + 1, needle, len - 1));
}
