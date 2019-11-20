/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 11:33:42 by cmouele           #+#    #+#             */
/*   Updated: 2019/11/20 17:23:52 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_champ	*get_target(t_vm *vm)
{
	t_arg			*arg;
	unsigned int	id;

	id = 0;
	arg = arg_new(vm);
	arg->type = DIR_CODE; 
	get_val(vm, arg, LIVE);
	ft_memcpy(&id, &arg->val, sizeof(unsigned int));
	if (id < 1 || id > vm->champs.size)
		ft_error(vm, &free_all, "Invalid ID.\n");
	return (vm->champs.byId[id]);
}

/*
**		Keeps a process alive and tells that a player is alive.
*/

void   			 op_live(void *vm_ptr)
{
    t_vm    	*vm;
	t_champ		*champ;
	t_process	*proc;

    vm = (t_vm *)vm_ptr;
	champ = get_target(vm);
	proc = vm->champs.cur->procs.cur;
    proc->live = 1;
	if (vm->verbose & V_LIVES)
	    ft_printf("A process shows that player %u (%s) is alive\n", champ->id, champ->name);
}
