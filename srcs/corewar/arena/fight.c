/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:53:46 by sregnard          #+#    #+#             */
/*   Updated: 2019/11/13 14:29:55 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	round(t_vm *vm)
{
	t_champs	*champs;
	t_champ		*champ;

	champs = &vm->champs;
	champ = champs->first;
	while (champ)
	{
		if (champ->procs.size == 0)
			ft_printf("I'm dead ! [%s]\n", champ->name);
		else
			ft_printf("I'm alive with %d process(es) ! [%s]\n", champ->procs.size, champ->name);
		champ = champ->next;
	}
}

void		fight(t_vm *vm)
{
	while (vm->champs.size &&\
		!(vm->flags & VM_DUMP && vm->cycle >= vm->dump))
	{
		round(vm);
		++vm->cycle;
	}
	//vm->flags & VM_DUMP ? arena_print(vm) : 0;
}
