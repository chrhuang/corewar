/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:54:29 by sregnard          #+#    #+#             */
/*   Updated: 2019/11/12 13:47:34 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**			Creates a new label, which adds itself to a champion's label list
**			Takes an existing command as argument
*/

t_label		*label_new(t_vm *vm)
{
	t_label	*label;

	if (!vm || !vm->champs.cur)
		ft_error(vm, &free_all, "label_new args\n");
	if (!(label = ft_memalloc(sizeof(t_label))))
		ft_error(vm, &free_all, "label_new memalloc\n");
	labels_add(vm, &vm->champs.cur->labels, label);
	return (label);
}

/*
**			Frees a label
*/

void		label_free(t_label **label)
{
	ft_memdel((void **)label);
}
