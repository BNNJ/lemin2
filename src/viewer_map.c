/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 21:23:10 by pfragnou          #+#    #+#             */
/*   Updated: 2019/02/18 21:23:10 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	get_boundaries(t_lm *lm, t_point *min, t_point *max)
{
	int	i;

	i = 0;
	min->x = INT_MAX;
	max->x = 0;
	min->y = INT_MAX;
	max->y = 0;
	while (i < lm->nb_room)
	{
		if (lm->rooms[i]->coord.x < min->x)
			min->x = lm->rooms[i]->coord.x;
		if (lm->rooms[i]->coord.y < min->y)
			min->y = lm->rooms[i]->coord.y;
		if (lm->rooms[i]->coord.x > max->x)
			max->x = lm->rooms[i]->coord.x;
		if (lm->rooms[i]->coord.y > max->y)
			max->y = lm->rooms[i]->coord.y;
		++i;
	}
}

int			setup_map(t_lm *lm)
{
	t_point	min;
	t_point	max;
	int		i;
	int		rw;
	int		rh;

	i = 0;
	get_boundaries(lm, &min, &max);
	rw = max.x - min.x;
	rh = max.y - min.y;
	while (i < lm->nb_room)
	{
		lm->rooms[i]->coord.x = rw > 0
			? ((lm->rooms[i]->coord.x - min.x) * (WIDTH - 50)) / rw + 10
			: WIDTH / 2 + 10;
		lm->rooms[i]->coord.y = rh > 0
			? ((lm->rooms[i]->coord.y - min.y) * (HEIGHT - 50)) / rh + 10
			: HEIGHT / 2 + 10;
		++i;
	}
	return (1);
}

static int	draw_links(t_lm *lm, t_sdl *sdl)
{
	int		i;
	int		j;

	i = 0;
	while (i < lm->nb_room)
	{
		j = 0;
		while (j < lm->nb_room)
		{
			if (lm->adjmat[i][j])
			{
				if (lm->adjmat[j][i] == 0
					? SDL_SetRenderDrawColor(sdl->rend, 255, 25, 25, 255)
					: SDL_SetRenderDrawColor(sdl->rend, 255, 255, 25, 255))
					return (0);
				if (SDL_RenderDrawLine(sdl->rend,
					lm->rooms[i]->coord.x + 15, lm->rooms[i]->coord.y + 15,
					lm->rooms[j]->coord.x + 15, lm->rooms[j]->coord.y + 15))
					return (0);
			}
			++j;
		}
		++i;
	}
	return (1);
}

static int	draw_rooms(t_lm *lm, t_sdl *sdl)
{
	int			i;
	SDL_Rect	rect;

	i = 0;
	rect.h = 30;
	rect.w = 30;
	while (i < lm->nb_room)
	{
		rect.x = lm->rooms[i]->coord.x;
		rect.y = lm->rooms[i]->coord.y;
		if (SDL_SetRenderDrawColor(sdl->rend, 0, 25, 25, 255) != 0)
			return (0);
		if (SDL_RenderFillRect(sdl->rend, &rect) != 0)
			return (0);
		if (lm->rooms[i] == lm->start || lm->rooms[i] == lm->end
			? SDL_SetRenderDrawColor(sdl->rend, 255, 25, 25, 255) != 0
			: SDL_SetRenderDrawColor(sdl->rend, 255, 255, 25, 255) != 0)
			return (0);
		if (SDL_RenderDrawRect(sdl->rend, &rect) != 0)
			return (0);
		++i;
	}
	return (1);
}

int			draw_map(t_lm *lm, t_sdl *sdl)
{
	if (!(draw_links(lm, sdl)))
		return (0);
	if (!(draw_rooms(lm, sdl)))
		return (0);
	return (1);
}
