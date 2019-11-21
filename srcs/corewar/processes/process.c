/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:21:55 by cmouele           #+#    #+#             */
/*   Updated: 2019/11/21 18:11:04 by sregnard         ###   ########.fr       */
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

	if (!vm || !vm->champs.cur)
		ft_error(vm, &free_all, "proc_new args\n");
	if (!(proc = ft_memalloc(sizeof(t_process))))
		ft_error(vm, &free_all, "proc_new memalloc\n");
	ft_bzero(&proc->args, sizeof(t_args));
	proc->champ = vm->champs.cur;
	proc->list = &vm->procs;
	procs_add(vm, proc->list, proc);
	ft_memcpy(&proc->reg[1], &proc->champ->id, sizeof(int));
	proc->pc = proc->champ->pos;
	vm->colors[proc->pc] = proc->champ->id + 10;
	ft_memcpy(&proc->reg, &proc->champ->id, sizeof(REG_SIZE));
	return (proc);
}

void		proc_exec(t_vm *vm, t_champ *champ, t_process *proc)
{
	int		opcode;

	vm->champs.cur = champ;
	vm->procs.cur = proc;
	opcode = arena_get(vm, proc->pc);
	if (opcode < 1 || opcode > 16)
		return ;
	if (proc->cycle == 0)
		proc->cycle = vm->cycle + op_cycles[opcode];
	if (proc->cycle > vm->cycle)
		return ;
	ft_printf("Cycle %d, executing %s\n", vm->cycle, op_names[opcode]);
	vm->pc = proc->pc;
	proc_set_pc(vm, proc, proc->pc + 1);
	ocp(vm, opcode);
	op[opcode](vm);
	args_free(&proc->args);
	proc->cycle = 0;
}

void		proc_set_pc(t_vm *vm, t_process *proc, unsigned int pc)
{
	vm->colors[proc->pc] = proc->champ->id;
	if (pc >= MEM_SIZE)
		pc &= MEM_SIZE;
	else if (pc < 0)
		pc = pc & -MEM_SIZE + MEM_SIZE - 1;
	if (pc < 0 || pc >= MEM_SIZE)
		ft_error(vm, &free_all, "PC out of arena !\n");
	proc->pc = pc;
	vm->arena[pc] ? vm->colors[pc] = proc->champ->id + 10 : 0;
}
