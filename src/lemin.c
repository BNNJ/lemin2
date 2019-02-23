/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:38:43 by pfragnou          #+#    #+#             */
/*   Updated: 2018/11/26 15:38:45 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	lm_usage(void)
{
	ft_dprintf(2, "usage:\t./lem-in [-g/s/p/d/c/a/v] [--ants=X] < <map>\n");
	ft_dprintf(2, "\t-g --debug : enable debug mode\n");
	ft_dprintf(2, "\t-s --strict : disable strict mode\n");
	ft_dprintf(2, "\t-p --print : do not print the map\n");
	ft_dprintf(2, "\t-d --display : enable alternative solution display ");
	ft_dprintf(2, "(incompatible with viewer)\n");
	ft_dprintf(2, "\t-c --color : enable colorized ants\n");
	ft_dprintf(2, "\t-a --alt : find alternative path\n");
	ft_dprintf(2, "\t--ants=X : set X as number of ants (if X is valid)\n");
	ft_dprintf(2, "\t-v --viewer : enable viewer\n");
	ft_dprintf(2, "\tviewer controls :\n");
	ft_dprintf(2, "\t\tleft/right : move backward/forward\n");
	ft_dprintf(2, "\t\tup/down : speed up/down\n");
	ft_dprintf(2, "\t\tspace : pause/unpause\n");
	ft_dprintf(2, "\t\treturn : reset\n");
}

int			main(int argc, char **argv)
{
	t_lm	lm;

	ft_memset(&lm, 0, sizeof(t_lm));
	if (lm_options(&lm, argc, argv))
		lm_usage();
	else
	{
		lm_parser(&lm);
		lm_setup_links(&lm);
		if (!lm_solver(&lm))
			ft_printf("%{red}No path found%{eoc}\n");
		else
		{
			if (lm.opt & OPT_DEBUG)
				print_stuff(&lm);
			ants(&lm);
		}
	}
	lm_exit(&lm, NULL, EXIT_SUCCESS);
	return (0);
}
