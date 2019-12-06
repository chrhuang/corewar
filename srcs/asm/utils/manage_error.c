/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:28:26 by lgaultie          #+#    #+#             */
/*   Updated: 2019/12/06 16:59:33 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** epure_line2() removes tabulations
*/

void	epure_line2(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
	}
}

/*
** manage_error() prints line if bonus -e is on.
** prints color if bonus -c is on.
** prints the apropriate error message.
** free and exit the program if bonus -q is off. (as -q lists all errors)
*/

void manage_error(void *p, void (*f)(void *), char *line, char *msg)
{
	t_assembler	*tmp;

	tmp = (t_assembler *)p;
	epure_line2(line);
	if (tmp->bonus & BONUS_MANAGE_ERROR && line)
	{
		msg && tmp->bonus & BONUS_COLOR ? write(2, "\e[35m", 5) : 0;
		ft_printf("line %d:\e[0m ", tmp->nb_line); // a mettre dans erreur output 2
		msg && tmp->bonus & BONUS_COLOR ? write(2, "\e[36m", 5) : 0;
		write(2, line, ft_strlen(line));
		msg && tmp->bonus & BONUS_COLOR ? write(2, "\e[0m", 4) : 0;
		write(2, "\n\t", 2);
	}
	msg && tmp->bonus & BONUS_COLOR ? write(2, "\e[1;31m", 7) : 0;
	msg ? write(2, "ERROR: ", 7) : 0;
	msg && tmp->bonus & BONUS_COLOR ? write(2, "\e[0m", 4) : 0;
	msg ? write(2, msg, ft_strlen(msg)) : 0;

	if (!(tmp->bonus & BONUS_DONT_QUIT))
	{
		if (f && p)
			f(p);
	}
	if (tmp->bonus & BONUS_DONT_QUIT)
		tmp->bonus |= BONUS_GOT_ERROR;
	else
		exit(EXIT_FAILURE);
}
