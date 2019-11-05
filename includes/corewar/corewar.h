/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:15:20 by sregnard          #+#    #+#             */
/*   Updated: 2019/11/05 01:48:30 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "common.h"

# include "param.h"
# include "command.h"
# include "label.h"
# include "process.h"
# include "champ.h"

typedef struct	s_vm
{
	t_champs			*champs;
	unsigned char		arena[MEM_SIZE];
}				t_vm;

/*
**	Free
*/

void			free_all(void *vm);

/*
**	Arena
*/

void			arena_print(t_vm *vm);
unsigned char	arena_get(t_vm *vm, int index);
void			arena_set(t_vm *vm, int index, unsigned char c);

/*
**	Champ
*/

void 			champs_add(t_vm *vm, t_champs *champs, t_champ *champ);
t_champ			*champ_new(t_vm *vm);
void			champs_free(t_champs **champs);
void			champ_free(t_champ **champ);

/*
**	Label
*/

void 			labels_add(t_vm *vm, t_labels *labels, t_label *label);
t_label			*label_new(t_vm *vm, t_command *cmd);

/*
** Command
*/

void 			cmds_add(t_vm *vm, t_commands *cmds, t_command *cmd);
t_command		*cmd_new(t_vm *vm);

/*
** Process
*/

void 			procs_add(t_vm *vm, t_processes *procs, t_process *proc);
t_process		*proc_new(t_vm *vm);

#endif
