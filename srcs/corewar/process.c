/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:21:55 by cmouele           #+#    #+#             */
/*   Updated: 2019/11/11 15:52:37 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**			Creates a new process, which adds itself to a champion's processes
**			list
*/

t_process	*proc_new(t_vm *vm)
{
	t_process	*proc;

	if (!vm || !vm->champs || !vm->champs->cur ||
		!vm->champs->cur->procs)
		ft_error(vm, &free_all, "proc_new args\n");
	if (!(proc = ft_memalloc(sizeof(t_process))))
		ft_error(vm, &free_all, "proc_new memalloc\n");
	procs_add(vm, vm->champs->cur->procs, proc);
	ft_memcpy(&proc->reg[1], &vm->champs->cur->id, sizeof(int));
	return (proc);
}

/*
**			Frees a process
*/

void		proc_free(t_process **proc)
{
	ft_memdel((void **)proc);
}
