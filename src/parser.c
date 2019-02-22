/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:38:50 by pfragnou          #+#    #+#             */
/*   Updated: 2018/11/26 15:38:51 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Verifies that the data parsed can be used before exiting the parser.
** Prints the map data if the -p option wasn't given and if the data
** is sufficient to run the solver.
** Prints a warning if an error was parsed, and an error if there's not enough
** data to solve the map.
*/

static void	lm_check_data(t_lm *lm, t_parser *p)
{
	if (p->error)
	{
		ft_dprintf(2, "%{yellow}Warning : %s%{eoc}\n", p->error);
		ft_strdel(&p->error);
	}
	get_next_line(0, NULL);
	ft_strdel(&p->data);
	if (lm->nb_ant <= 0)
		lm_exitparser(lm, p, "invalid number of ants", EXIT_FAILURE);
	else if (!lm->start)
		lm_exitparser(lm, p, "no start", EXIT_FAILURE);
	else if (!lm->end)
		lm_exitparser(lm, p, "no end", EXIT_FAILURE);
	else if (lm->end == lm->start)
		lm_exitparser(lm, p, "start and end are the same room", EXIT_FAILURE);
	else if (!lm->adjmat)
		lm_exitparser(lm, p, "no links", EXIT_FAILURE);
}

/*
** Gets the number of ants.
** This number should be more than 0 and less or equal tham INT_MAX.
** If a non-digit character is encountered, the line is considered invalid.
*/

static void	lm_handle_ants(t_lm *lm, t_parser *p)
{
	char	*data;
	int		count;

	if (~lm->opt & OPT_ANT)
	{
		if (lm->nb_ant == 0)
		{
			data = p->data;
			count = 0;
			while (*data == '0')
				++data;
			while (*data >= '0' && *data <= '9')
			{
				lm->nb_ant = lm->nb_ant * 10 + (*data - '0');
				++data;
				++count;
			}
			if (count > 10 || lm->nb_ant <= 0 || *data != 0)
				lm_exitparser(lm, p, "Invalid number of ants", EXIT_FAILURE);
		}
		lm->opt |= OPT_ANT;
	}
	else if (!(p->error = ft_strdup("Number of ants already declared")))
		lm_exitparser(lm, p, "alloc error", EXIT_FAILURE);
}

/*
** Handles comments and instructions
*/

static void	lm_handle_comment(t_lm *lm, t_parser *p)
{
	if (ft_strequ(p->data, "##start") || ft_strequ(p->data, "##START"))
		p->next_type |= ROOM_START;
	else if (ft_strequ(p->data, "##end") || ft_strequ(p->data, "##END"))
		p->next_type |= ROOM_END;
	else if (ft_strnequ(p->data, "#Here is the number of lines required:", 38))
		lm->required = ft_atoi(p->data + 38);
}

/*
** Handles empty lines
*/

static void	lm_empty_line(t_lm *lm, t_parser *p)
{
	if (~lm->opt & OPT_STRICT && !(p->error = ft_strdup("empty line")))
		lm_exitparser(lm, p, "alloc error", EXIT_FAILURE);
}

/*
** Go through stdin up until encountering an error or it is finished.
** Empty lines are skipped, then the appropriate handler is called.
*/

void		lm_parser(t_lm *lm)
{
	t_parser	p;

	ft_memset(&p, 0, sizeof(t_parser));
	if (read(0, NULL, 0) < 0)
		lm_exitparser(lm, &p, "Dude what you doin", EXIT_FAILURE);
	while (!p.error && get_next_line(0, &p.data) > 0)
	{
		if (~lm->opt & OPT_PRINT)
			ft_printf("%s\n", p.data);
		if (!*p.data)
			lm_empty_line(lm, &p);
		else if (*p.data == '#')
			lm_handle_comment(lm, &p);
		else if (~lm->opt & OPT_ANT)
			lm_handle_ants(lm, &p);
		else if ((p.idx = ft_findchar(p.data, '-')) >= 0)
			lm_handle_link(lm, &p);
		else if ((p.idx = ft_findchar(p.data, ' ')) >= 0)
			lm_handle_room(lm, &p);
		else if (!(p.error = ft_strdup("Invalid line")))
			lm_exitparser(lm, &p, "alloc error", EXIT_FAILURE);
	}
	lm_check_data(lm, &p);
}
