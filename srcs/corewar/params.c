/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 21:40:27 by cmouele           #+#    #+#             */
/*   Updated: 2019/11/06 21:46:57 by cmouele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**			Adds an existing parameter to an existing parameters list
*/

void 		params_add(t_vm *vm, t_params *params, t_param *param)
{
	if (!vm || !params || !param)
		ft_error(vm, &free_all, "params_add args\n");
	if (!params->first)
	{
		params->first = param;
		params->cur = param;
		params->last = param;
	}
	else
	{
		params->last->next = param;
		params->last = param;
	}
	++params->size;
}

/*
**			Frees all parameters in the list then the list itself
*/

void		params_free(t_params **params_ptr)
{
	t_params	*params;

	if (!params_ptr || !*params_ptr)
		return ;
	params = *params_ptr;
	while (params->first)
	{
		params->cur = params->first->next;
		param_free(&params->first);
		params->first = params->cur;
	}
	ft_memdel((void **)params_ptr);
}
