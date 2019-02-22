/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 21:23:17 by pfragnou          #+#    #+#             */
/*   Updated: 2019/02/18 21:23:19 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	viewer_forward(t_lm *lm, t_sdl *sdl, int *step)
{
	if (*step < lm->nb_step)
	{
		move_forward(lm, step);
		sdl->state = 0;
		return (1);
	}
	else
		return (0);
}

static int	viewer_backward(t_lm *lm, t_sdl *sdl, int *step)
{
	if (*step > 0)
	{
		move_backward(lm, step);
		sdl->state = 0;
		return (1);
	}
	else
		return (0);
}

static int	viewer_reset(t_lm *lm, t_sdl *sdl, int *step)
{
	sdl->delay = 15;
	while (*step > 0)
		move_backward(lm, step);
	sdl->state = 0;
	return (1);
}

int			viewer_control(t_lm *lm, t_sdl *sdl, int *step)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT
			|| (e.key.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			sdl_exit(lm, sdl, EXIT_SUCCESS);
		if (e.key.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_SPACE)
				sdl->state ^= 1;
			else if (e.key.keysym.sym == SDLK_LEFT)
				return (viewer_backward(lm, sdl, step));
			else if (e.key.keysym.sym == SDLK_RIGHT)
				return (viewer_forward(lm, sdl, step));
			else if (e.key.keysym.sym == SDLK_RETURN)
				return (viewer_reset(lm, sdl, step));
			else if (e.key.keysym.sym == SDLK_DOWN)
				sdl->delay += 5;
			else if (e.key.keysym.sym == SDLK_UP && sdl->delay >= 5)
				sdl->delay -= 5;
		}
	}
	return (0);
}

int			indraw_control(t_lm *lm, t_sdl *sdl)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
		if (e.key.type == SDL_KEYDOWN)
		{
			if (e.type == SDL_QUIT
				|| (e.key.keysym.sym == SDLK_ESCAPE))
				sdl_exit(lm, sdl, EXIT_SUCCESS);
			else if (e.key.keysym.sym == SDLK_DOWN)
				sdl->delay += 5;
			else if (e.key.keysym.sym == SDLK_UP
				&& sdl->delay >= 5)
				sdl->delay -= 5;
			else if (e.key.keysym.sym == SDLK_SPACE
				|| e.key.keysym.sym == SDLK_RIGHT
				|| e.key.keysym.sym == SDLK_LEFT
				|| e.key.keysym.sym == SDLK_RETURN)
				sdl->state = 0;
		}
	}
	return (0);
}
