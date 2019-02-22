/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 21:22:37 by pfragnou          #+#    #+#             */
/*   Updated: 2019/02/18 21:22:38 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	*free_matrix(int **matrix, int size)
{
	int		i;

	i = 0;
	if (matrix)
	{
		while (i < size)
		{
			if (matrix[i])
				free(matrix[i]);
			++i;
		}
		free(matrix);
	}
	return (NULL);
}

int		**create_matrix(int size)
{
	int		i;
	int		**matrix;

	i = 0;
	if (!(matrix = malloc(sizeof(int*) * size)))
		return (NULL);
	while (i < size)
	{
		if (!(matrix[i] = malloc(sizeof(int) * size)))
			return (NULL);
		++i;
	}
	return (matrix);
}

void	update_matrix(t_lm *lm, int **matrix)
{
	int		i;

	i = 0;
	while (i < lm->nb_room)
	{
		ft_memcpy(matrix[i], lm->adjmat[i], sizeof(int) * lm->nb_room);
		++i;
	}
}
