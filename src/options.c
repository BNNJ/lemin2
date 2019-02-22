/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 21:28:41 by pfragnou          #+#    #+#             */
/*   Updated: 2019/02/18 21:28:42 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static char	get_opt(t_lm *lm, char *arg)
{
	int	opt;

	while (*arg)
	{
		if ((opt = ft_findchar("pgsdcav", *arg)) >= 0)
			lm->opt |= (1 << opt);
		else
			return (*arg);
		++arg;
	}
	return (-1);
}

static int	get_command(t_lm *lm, char *com)
{
	if (ft_strequ(com + 2, "print"))
		lm->opt |= OPT_PRINT;
	else if (ft_strequ(com + 2, "debug"))
		lm->opt |= OPT_DEBUG;
	else if (ft_strequ(com + 2, "display"))
		lm->opt |= OPT_DISP;
	else if (ft_strequ(com + 2, "strict"))
		lm->opt |= OPT_STRICT;
	else if (ft_strequ(com + 2, "color"))
		lm->opt |= OPT_COLOR;
	else if (ft_strequ(com + 2, "color"))
		lm->opt |= OPT_COLOR;
	else if (ft_strequ(com + 2, "alt"))
		lm->opt |= OPT_ALT;
	else if (ft_strequ(com + 2, "viewer"))
		lm->opt |= OPT_VIEWER;
	else if (ft_strnequ(com + 2, "ants=", 5))
		lm->nb_ant = ft_atoi(com + 7);
	else
		return (0);
	return (1);
}

static int	display_help(void)
{
	ft_dprintf(2, "Lem-in is a path finding program, in which ants are sent ");
	ft_dprintf(2, "through a maze of rooms linked by pipes. It computes the ");
	ft_dprintf(2, "best combination of paths from a room to another ");
	ft_dprintf(2, "for a given network and number of ants.\n");
	ft_dprintf(2, "It parses stdin for data about ants, rooms and pipes.\n");
	ft_dprintf(2, "Here's how to use it, and some options it takes :\n");
	return (1);
}

int			lm_options(t_lm *lm, int argc, char **argv)
{
	int		i;
	char	opt;

	i = 0;
	while (++i < argc)
	{
		if (*argv[i] == '-')
		{
			if (*(argv[i] + 1) == '-')
			{
				if (ft_strequ(argv[i], "--help"))
					return (display_help());
				if (!get_command(lm, argv[i]))
					return (ft_dprintf(2, "invalid option : %s\n", argv[i]));
			}
			else if ((opt = get_opt(lm, argv[i] + 1)) >= 0)
				return (ft_dprintf(2, "invalid option : -%c\n", opt));
		}
		else
			return (ft_dprintf(2, "invalid parameter : '%s'\n", argv[i]));
	}
	return (0);
}
