/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:44:20 by sregnard          #+#    #+#             */
/*   Updated: 2020/02/02 09:32:24 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		parse_header(t_vm *vm)
{
	t_champ	*champ;

	champ = vm->champs.cur;
	ft_memcpy(&champ->magic, champ->content, sizeof(int));
	ft_memrev(&champ->magic, sizeof(int));
	if (champ->magic != COREWAR_EXEC_MAGIC)
		error_magic(vm);
	champ->cursor += sizeof(int);
	ft_memcpy(&champ->name, champ->content + champ->cursor, PROG_NAME_LENGTH);
	champ->cursor += PROG_NAME_LENGTH + PADDING;
	ft_memcpy(&champ->prog_size, champ->content + champ->cursor,
			sizeof(unsigned int));
	ft_memrev(&champ->prog_size, sizeof(unsigned int));
	if (champ->prog_size == 0 || champ->prog_size > CHAMP_MAX_SIZE)
		error_prog_size(vm);
	champ->cursor += sizeof(unsigned int);
	ft_memcpy(&champ->comment, champ->content + champ->cursor, COMMENT_LENGTH);
	champ->cursor += COMMENT_LENGTH + PADDING;
	if (!ft_strlen(champ->name) || ft_strlen(champ->name) > PROG_NAME_LENGTH)
		error_name(vm);
	if (!(ft_strlen(champ->comment)) ||
			ft_strlen(champ->comment) > COMMENT_LENGTH)
		error_comment(vm);
}

static void		parse_file(t_vm *vm, char *file)
{
	t_champ	*champ;
	int		fd;

	champ = NULL;
	(fd = open(file, O_RDONLY | O_NOFOLLOW)) == -1 ?
	error_open(vm, file) : (champ = champ_new(vm));
	champ->file = file;
	champ->size = read(fd, champ->content, BUFF_SIZE);
	if (close(fd) != 0)
		ft_error(vm, &vm_free, "parse_file couldn't close file !\n");
	champ->size < FILE_MIN_SIZE ? error_too_small(vm) : 0;
	champ->content[champ->size] = '\0';
	parse_header(vm);
}

void			parse_args(t_vm *vm)
{
	!vm->ac ? error_usage(vm) : 0;
	while (vm->ac--)
	{
		if (**vm->av == '-')
			parse_option(vm);
		else
			parse_file(vm, *vm->av++);
	}
	vm->champs.size == 0 || vm->champs.size > MAX_PLAYERS ?
	error_usage(vm) : champs_ids(vm);
	champs_sort(vm);
}
