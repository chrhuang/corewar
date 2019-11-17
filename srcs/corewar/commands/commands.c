/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 21:44:01 by cmouele           #+#    #+#             */
/*   Updated: 2019/11/12 13:48:19 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**			Adds an existing command to an existing commands list
*/

void		cmds_add(t_vm *vm, t_commands *cmds, t_command *cmd)
{
	if (!vm || !cmds || !cmd)
		ft_error(vm, &free_all, "cmds_add args\n");
	if (!cmds->first)
	{
		cmds->first = cmd;
		cmds->cur = cmd;
		cmds->last = cmd;
	}
	else
	{
		cmds->last->next = cmd;
		cmds->last = cmd;
	}
	++cmds->size;
}
