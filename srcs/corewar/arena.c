/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 00:19:47 by sregnard          #+#    #+#             */
/*   Updated: 2019/11/07 14:14:13 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		print_line(t_vm *vm, unsigned int cur, unsigned len)
{
	unsigned int	i;

	i = 0;
	while (i < len)
	{
		ft_printf("%02x", vm->arena[cur * len + i++]);
		i < len ? ft_printf(" ") : 0;
	}
	ft_putln();
}

void		arena_print(t_vm *vm)
{
	unsigned int	len;
	unsigned int	cur;

	if (!vm)
		return ; 
	len = ft_sqrt(MEM_SIZE);
	cur = 0;
	while (cur < len)
		print_line(vm, cur++, len);
}

unsigned char	arena_get(t_vm *vm, int index)
{
//	ft_printf("arena_get : index before = %-4d\t", index);
	if (index >= MEM_SIZE)
		index %= MEM_SIZE;
	else if (index < 0)
		index = index % -MEM_SIZE + MEM_SIZE - 1;
//	ft_printf("arena_get : index after = %-4d\t", index);
	if (index < 0 || index >= MEM_SIZE)
		ft_error(vm, &free_all, "arena_get out of bounds\n");
//	ft_printf("arena_get : vm->arena[%d] = %02x\n", index, vm->arena[index]);
	return (vm->arena[index]);
}

void			arena_set(t_vm *vm, int index, unsigned char c)
{
//	ft_printf("arena_set : index before = %-4d\t", index);
	if (index >= MEM_SIZE)
		index %= MEM_SIZE;
	else if (index < 0)
		index = index % -MEM_SIZE + MEM_SIZE - 1;
//	ft_printf("arena_set : index after = %-4d\t", index);
	if (index < 0 || index >= MEM_SIZE)
		ft_error(vm, &free_all, "arena_set out of bounds\n");
	vm->arena[index] = c;
// 	ft_printf("arena_set : vm->arena[%d] = %02x\n", index, vm->arena[index]);
}

void			arena_init(t_vm *vm)
{
	unsigned int	nb_players;
	t_champ			*champ;
	int 			id_champ;

	nb_players = vm->champs->size;
	champ = vm->champs->first;
	id_champ = 0;
	while (champ)
	{
		champ->id = id_champ;
		champ->pos = champ->id * (MEM_SIZE / nb_players);
		ft_memcpy(&vm->arena[champ->pos], &champ->content[champ->cursor], champ->prog_size);
		champ = champ->next;
		id_champ++;
	}
}