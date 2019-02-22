/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   augmenting_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:34:53 by pfragnou          #+#    #+#             */
/*   Updated: 2018/12/05 14:34:54 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Updates the graph by setting up the paths starting from each room
** stored in lm->paths and following the capacities stored in lm->adjmat
*/

static void	update_graph(t_path *path, t_room *end, int **mat, int n)
{
	int		i;
	int		j;
	int		len;
	t_room	*cur;

	i = 0;
	while (i < n)
	{
		cur = path[i].room;
		len = 1;
		while (cur != end)
		{
			j = 0;
			cur->status |= SPT_MEMBER;
			while (mat[cur->id][cur->links[j]->id] > 0)
				++j;
			cur->next = cur->links[j];
			cur = cur->next;
			++len;
		}
		path[i].len = len;
		++i;
	}
}

/*
** Edmonds-Karp algorithm :
** It's a maximum flow problem solving algorithm.
** At each iteration, the shortest augmenting path is found using a BFS
** Then, the graph is updated (the tubes capacity), and the paths as well.
** We also calculate the number of steps required to solve
** the graph, and compare it with the previous one.
** If the number of steps required is higher than the previous one, we reverse
** the graph to its previous state to ensure we end up with the optimal network.
*/

static int	**find_paths(t_lm *lm)
{
	int		i;
	int		nb_step;
	int		**matrix;

	i = 0;
	lm->nb_step = INT_MAX;
	if (!(matrix = create_matrix(lm->nb_room)))
		return (free_matrix(matrix, lm->nb_room));
	while (i < lm->nb_ant && (lm->paths[i].room = lm_shortest_path(lm)))
	{
		++i;
		update_graph(lm->paths, lm->end, lm->adjmat, i);
		if ((nb_step = number_of_steps(lm, i)) == -1)
			return (matrix);
		else if ((nb_step < lm->nb_step)
			|| (lm->opt & OPT_ALT && nb_step <= lm->nb_step))
		{
			update_matrix(lm, matrix);
			lm->nb_path = i;
			lm->nb_step = nb_step;
		}
	}
	return (matrix);
}

/*
** Assigns to each path its "end" room : the last room before lm->end.
** Also assigns the prev to each room.
*/

static void	finalize(t_lm *lm)
{
	int		i;
	t_room	*room;

	i = 0;
	while (i < lm->nb_path)
	{
		room = lm->paths[i].room;
		room->prev = lm->start;
		if (room != lm->end)
		{
			while (room->next != lm->end)
			{
				room->next->prev = room;
				room = room->next;
			}
			lm->paths[i].end = room;
		}
		++i;
	}
}

/*
** Handles the special case where start and end are linked.
*/

static int	exception_inf(t_lm *lm)
{
	if (!(lm->paths = ft_memalloc(sizeof(t_path))))
		lm_exit(lm, "alloc error", EXIT_FAILURE);
	lm->nb_path = 1;
	lm->nb_step = 1;
	lm->paths[0].room = lm->start;
	lm->paths[0].end = lm->start;
	lm->start->next = lm->end;
	lm->end->prev = lm->start;
	return (1);
}

/*
** Redirects to the proper handling function if end and start are linked
** Otherwise, calls the augmenting paths algorithm which returns a matrix,
** then uses that matrix to update the graph
*/

int			lm_solver(t_lm *lm)
{
	int		**matrix;

	matrix = NULL;
	if (lm->adjmat[lm->end->id][lm->start->id])
		return (exception_inf(lm));
	if (!(lm->paths = ft_memalloc(sizeof(t_path) * (lm->start->nb_link + 1))))
		lm_exit(lm, "alloc error", EXIT_FAILURE);
	if (!(matrix = find_paths(lm)))
		lm_exit(lm, "alloc error", EXIT_FAILURE);
	free_matrix(lm->adjmat, lm->nb_room);
	lm->adjmat = matrix;
	update_graph(lm->paths, lm->end, lm->adjmat, lm->nb_path);
	finalize(lm);
	return (lm->nb_path);
}
