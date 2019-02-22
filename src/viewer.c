/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 21:22:54 by pfragnou          #+#    #+#             */
/*   Updated: 2019/02/18 21:22:57 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		sdl_exit(t_lm *lm, t_sdl *sdl, int exit_status)
{
	if (exit_status == EXIT_FAILURE)
		ft_dprintf(2, "%{red}SDL Error : %s%{eoc}\n", SDL_GetError());
	if (sdl->win)
		SDL_DestroyWindow(sdl->win);
	if (sdl->rend)
		SDL_DestroyRenderer(sdl->rend);
	if (sdl->texture)
		SDL_DestroyTexture(sdl->texture);
	if (sdl->surface)
		SDL_FreeSurface(sdl->surface);
	SDL_Quit();
	lm_exit(lm, NULL, exit_status);
}

static int	lm_draw(t_lm *lm, t_sdl *sdl)
{
	int	i;

	i = 0;
	while (i <= NB_FRAME)
	{
		if (SDL_SetRenderDrawColor(sdl->rend, 0, 25, 25, 25))
			return (0);
		SDL_RenderClear(sdl->rend);
		if (!draw_map(lm, sdl))
			return (0);
		if (!draw_ants(lm, sdl, i))
			return (0);
		SDL_RenderPresent(sdl->rend);
		indraw_control(lm, sdl);
		SDL_Delay(sdl->delay);
		++i;
	}
	print_move(lm);
	return (1);
}

static int	sdl_init(t_lm *lm, t_sdl *sdl)
{
	*sdl = (t_sdl){NULL, NULL, NULL, NULL, 0, 15};
	if (!setup_map(lm))
		return (0);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (0);
	if (!(sdl->win = SDL_CreateWindow("Lem-in", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0)))
		return (0);
	if (!(sdl->rend = SDL_CreateRenderer(sdl->win, -1,
		SDL_RENDERER_ACCELERATED)))
		return (0);
	if (SDL_SetRenderDrawColor(sdl->rend, 0, 25, 25, 25))
		return (0);
	SDL_RenderClear(sdl->rend);
	if (!(draw_map(lm, sdl)))
		return (0);
	if (!(draw_ants(lm, sdl, NB_FRAME)))
		return (0);
	SDL_RenderPresent(sdl->rend);
	return (1);
}

void		viewer(t_lm *lm)
{
	t_sdl		sdl;
	int			step;

	if (!(sdl_init(lm, &sdl)))
		sdl_exit(lm, &sdl, EXIT_FAILURE);
	step = 0;
	while (42)
	{
		if (viewer_control(lm, &sdl, &step))
		{
			if (!lm_draw(lm, &sdl))
				sdl_exit(lm, &sdl, EXIT_FAILURE);
		}
		if (step < lm->nb_step && sdl.state == 1)
		{
			move_forward(lm, &step);
			if (!lm_draw(lm, &sdl))
				sdl_exit(lm, &sdl, EXIT_FAILURE);
			SDL_Delay(50);
		}
	}
	sdl_exit(lm, &sdl, EXIT_SUCCESS);
}
