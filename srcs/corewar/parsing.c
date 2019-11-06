/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:44:20 by sregnard          #+#    #+#             */
/*   Updated: 2019/11/06 15:01:51 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		parse_file(t_vm *vm, char *file)
{
	char	content[BUFF_SIZE + 1];
	int		fd;
	int		ret;

	(fd = open(file, O_RDONLY)) == -1 ? 
	ft_error(vm, &free_all, "ERROR: file doesn't exist\n") : 0;
	ret = read(fd, content, BUFF_SIZE);
	ret < 1 ? ft_error(vm, &free_all, "ERROR: empty file\n") : 0;
	content[ret] = '\0';
	ft_hexdump(content, ret);
}

void		parse_args(t_vm *vm, int ac, char **av)
{
	while(ac--)
		parse_file(vm, *av++);
}
