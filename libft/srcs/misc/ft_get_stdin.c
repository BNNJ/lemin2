/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_stdin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 20:15:06 by pfragnou          #+#    #+#             */
/*   Updated: 2018/11/22 20:15:08 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char*)(dst + i) = *(unsigned char*)(src + i);
		++i;
	}
	return (dst);
}

static int	add_buf(char *buf, size_t rd, t_stdbuf **buf_list)
{
	t_stdbuf	*new;
	t_stdbuf	*tmp;

	if (!(new = (t_stdbuf*)malloc(sizeof(t_stdbuf))))
		return (0);
	ft_memcpy(new->buf, buf, rd);
	new->buf[rd] = '\0';
	new->size = rd;
	new->next = NULL;
	if (!*buf_list)
		*buf_list = new;
	else
	{
		tmp = *buf_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

static char	*listcat(t_stdbuf *list, size_t size)
{
	char	*ret;
	size_t	i;
	size_t	j;

	if (!(ret = (char*)malloc(size + 1)))
		return (NULL);
	i = 0;
	while (list)
	{
		j = 0;
		while (list->buf[j])
		{
			ret[i] = list->buf[j];
			++j;
			++i;
		}
		list = list->next;
	}
	return (ret);
}

ssize_t		ft_get_stdin(char **str)
{
	size_t		rd;
	char		buf[GSTD_BUFSIZ];
	t_stdbuf	*buf_list;
	ssize_t		list_size;

	buf_list = NULL;
	list_size = 0;
	if (!str)
		return (-1);
	while ((rd = read(0, buf, GSTD_BUFSIZ)) > 0)
	{
		if (!(add_buf(buf, rd, &buf_list)))
			return (-1);
		list_size += rd;
	}
	if (!(*str = listcat(buf_list, list_size)))
		return (-1);
	return (list_size);
}
