/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:32:59 by lgaultie          #+#    #+#             */
/*   Updated: 2020/02/02 09:49:49 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	open_file(t_assembler *as, char *argv)
{
	as->s_fd = open(argv, O_RDONLY | O_NOFOLLOW);
	return (as->s_fd);
}

static int	check_file_type(char *argv)
{
	char		*s;

	if (!(s = ft_strrchr(argv, '.')) || ft_strcmp(s, ".s") != 0)
	{
		ft_putstr(NOT_S_FILE);
		return (0);
	}
	return (1);
}

static int	assembler(t_assembler *as, char **argv, int i, unsigned int flag)
{
	init_asm(as, flag);
	if (open_file(as, argv[i]) == -1)
		manage_error(as, &free_asm, CANT_READ);
	if (!(as->file_name_s = ft_strdup(argv[i])))
	{
		free_asm(&as);
		return (FAIL);
	}
	read_function(as);
	close(as->s_fd);
	create_cor(as);
	free_asm(as);
	return (SUCCESS);
}

int			main(int argc, char **argv)
{
	t_assembler		as;
	unsigned int	flag;
	int				i;
	int				flag_on;

	i = 0;
	flag_on = 0;
	if (argc == 1)
		return (print_usage());
	init_bonus(&flag, argv);
	while (++i < argc)
	{
		if (argv[i][0] == '-')
		{
			flag_on = 1;
			continue;
		}
		if (check_file_type(argv[i]) == 0 \
		|| (assembler(&as, argv, i, flag)) == FAIL)
			return (0);
	}
	if (flag_on != 0 && i == 2)
		print_usage();
	return (0);
}
