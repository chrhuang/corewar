/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 00:19:47 by sregnard          #+#    #+#             */
/*   Updated: 2019/11/26 15:21:47 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int	arena_id(t_vm *vm, int index)
{
	if (index >= MEM_SIZE)
		index %= MEM_SIZE;
	else if (index < 0)
		index = index % -MEM_SIZE + MEM_SIZE - 1;
	if (index < 0 || index >= MEM_SIZE)
		ft_error(vm, &free_all, "arena_get out of bounds\n");
	return (index);
}

unsigned char	arena_get(t_vm *vm, int index)
{
	return (vm->arena[arena_id(vm, index)]);
}

void			arena_set(t_vm *vm, int index, unsigned char c,
							unsigned int id_player)
{
	unsigned int	id;

	id = arena_id(vm, index);
	vm->arena[id] = c;
	vm->colors[id] = id_player;
}

/*
**				Copies n bytes from the arena to the destination
*/

void			arena_load(t_vm *vm, int index, void *dst, size_t n)
{
	char		*dest;

	dest = (char *)dst;
	while (n-- > 0)
		dest[n] = arena_get(vm, index + n);
}

/*
**				Copies n bytes from the source to the arena
*/

void			arena_store(t_vm *vm, int index, const void *src, size_t n,
							unsigned int id)
{
	const char	*source;

	source = (const char *)src;
	while (n-- > 0)
		arena_set(vm, index + n, source[n], id);
}

void			arena_init(t_vm *vm)
{
	unsigned int	nb_players;
	t_champ			*champ;

	nb_players = vm->champs.size;
	champ = vm->champs.first;
	while (champ)
	{
		champ->pos = (champ->id - 1) * (MEM_SIZE / nb_players);
		ft_memcpy(&vm->arena[champ->pos], &champ->content[champ->cursor], champ->prog_size);
		ft_memset(&vm->colors[champ->pos], champ->id, champ->prog_size);
		vm->champs.cur = champ;
		proc_new(vm);
		champ = champ->next;
	}
}
