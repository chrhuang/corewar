/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:14:04 by lgaultie          #+#    #+#             */
/*   Updated: 2019/12/04 14:07:12 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	open_file(t_assembler *as, char *argv)
{
	as->s_fd = open(argv, O_RDONLY);
	return (as->s_fd);
}

int			check_file_type(char *argv)
{
	char		*s;

	if (!(s = ft_strchr(argv, '.')) || ft_strcmp(s, ".s") != 0)
	{
		ft_putstr(NOT_S_FILE);
		return (0);
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_assembler	as;
	int			i;

	i = 1;
	if (argc == 1)
	{
		ft_putstr("Usage: ./asm [-help] mychampion1.s mychampion2.s\n");
		return (0);
	}
	while (i < argc)
	{
		init_asm(&as);
		if (ft_strcmp(argv[i], "-help") == 0)
		{
			ft_putstr("Usage: -e pour changer les trucs en errors, etc les bonus\n");
			//free as
			return (0);
		}
		if (ft_strcmp(argv[i], "-e") == 0)
		{
			as.bonus |= BONUS_MANAGE_ERROR;
			i++;
		}
		if (check_file_type(argv[i]) == 0)
			return (0);
		if (open_file(&as, argv[i]) == -1)
			manage_error(&as, &free_asm, NULL, CANT_READ);
		as.file_name_s = ft_strdup(argv[i]);
		parsing(&as);
		close(as.s_fd);
		create_cor(&as);
		i++;
	}
	free_asm(&as);
	return (0);
}
