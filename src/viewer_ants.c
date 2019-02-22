/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 21:23:03 by pfragnou          #+#    #+#             */
/*   Updated: 2019/02/18 21:23:04 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	lerp(int x1, int x2, int k)
{
	float	x;
	int		d;

	x1 += 10;
	x2 += 10;
	d = x1 - x2;
	x = x2 + ((d * k) / NB_FRAME);
	return ((int)x);
}

static int	ant_color(int color, t_sdl *sdl)
{
	static int	col_tab[8][3] = {
		{0, 0, 0},
		{255, 0, 0},
		{0, 255, 0},
		{255, 255, 0},
		{0, 0, 255},
		{255, 0, 255},
		{0, 255, 255},
		{255, 255, 255}
	};

	if (SDL_SetRenderDrawColor(sdl->rend,
		col_tab[color][0],
		col_tab[color][1],
		col_tab[color][2], 255) != 0)
		return (0);
	return (1);
}

int			draw_ants(t_lm *lm, t_sdl *sdl, int k)
{
	int			i;
	SDL_Rect	rect;

	i = lm->nb_ant;
	rect.w = 10;
	rect.h = 10;
	while (--i >= 0)
	{
		if (lm->ants[i].room)
		{
			if (!ant_color(lm->ants[i].color, sdl))
				return (0);
			rect.x = lerp(lm->ants[i].room->coord.x, lm->ants[i].coord.x, k);
			rect.y = lerp(lm->ants[i].room->coord.y, lm->ants[i].coord.y, k);
			if (SDL_RenderFillRect(sdl->rend, &rect) != 0)
				return (0);
			if (k == NB_FRAME)
			{
				lm->ants[i].coord.x = lm->ants[i].room->coord.x;
				lm->ants[i].coord.y = lm->ants[i].room->coord.y;
			}
		}
	}
	return (1);
}
