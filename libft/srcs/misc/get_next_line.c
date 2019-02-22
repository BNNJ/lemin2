/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 01:07:10 by pfragnou          #+#    #+#             */
/*   Updated: 2018/05/17 01:07:13 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_file_rd	*init_file(int fd, t_file_rd *file)
{
	t_file_rd	*new_file;

	if (file)
	{
		file = file->start;
		while (file->next && file->fd != fd)
			file = file->next;
		if (file->fd == fd)
			return (file);
	}
	if (!(new_file = (t_file_rd*)malloc(sizeof(t_file_rd))))
		return (0);
	new_file->string = NULL;
	new_file->fd = fd;
	new_file->rd_len = 0;
	new_file->next = NULL;
	if (file)
	{
		new_file->start = file->start;
		file->next = new_file;
	}
	else
		new_file->start = new_file;
	return (new_file);
}

static int			terminate_file(t_file_rd **file, char **line)
{
	t_file_rd	*tmp;

	tmp = (*file)->start;
	if (*file == tmp)
	{
		(*file)->start = (*file)->next;
		while (tmp)
		{
			tmp->start = (*file)->start;
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp->next != *file)
			tmp = tmp->next;
		tmp->next = (*file)->next;
	}
	tmp = (*file)->start;
	if ((*file)->string)
		ft_tstr_del(&(*file)->string);
	free(*file);
	*file = tmp;
	ft_strdel(line);
	return (0);
}

static int			process_buffer(t_file_rd **file, char **line)
{
	t_string	*tmp;
	int			i;
	size_t		len;

	if ((i = ft_tstr_findchar((*file)->string, '\n')) >= 0)
	{
		if (!(tmp = ft_tstr_sub((*file)->string, 0, i, 0)))
			return (-1);
		(*file)->string->len -= i;
		if (!((*file)->string = ft_tstr_sub((*file)->string, i + 1,
			(*file)->string->len - 1, 1)))
			return (-1);
		*line = ft_tstr_to_str(tmp);
		len = tmp->len;
		ft_tstr_del(&tmp);
	}
	else
	{
		*line = ft_tstr_to_str((*file)->string);
		len = (*file)->string->len;
		ft_tstr_del(&((*file)->string));
		if ((*file)->rd_len < BUFF_SIZE && len == 0)
			return (terminate_file(file, line));
	}
	return (BINARY ? len : 1);
}

static int			close_file(t_file_rd **file, t_string *buffer)
{
	ft_tstr_del(&buffer);
	return (terminate_file(file, NULL));
}

int					get_next_line(int fd, char **line)
{
	static t_file_rd	*file = NULL;
	t_string			*buffer;
	int					rd_check;

	rd_check = 1;
	if (fd < 0 || !(file = init_file(fd, file))
		|| !(buffer = ft_tstr_new(BUFF_SIZE)))
		return (-1);
	if (line == NULL)
		return (close_file(&file, buffer));
	ft_strdel(line);
	while (rd_check)
	{
		if ((file->rd_len = read(fd, buffer->content, BUFF_SIZE)) < 0)
			return (-1);
		buffer->len = file->rd_len;
		if (!(file->string = ft_tstr_join(file->string, buffer, 1)))
			return (-1);
		if ((ft_tstr_findchar(file->string, '\n')) >= 0
			|| (file->rd_len < BUFF_SIZE))
			rd_check = 0;
		ft_tstr_clr(buffer);
	}
	ft_tstr_del(&buffer);
	return (process_buffer(&file, line));
}
