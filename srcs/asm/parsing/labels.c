/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:41:40 by lgaultie          #+#    #+#             */
/*   Updated: 2019/12/05 15:06:53 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** check_if_exists() depends on mode, returns SUCCESS if param is already
** defined or FAIL it doesn't exist
*/

int		check_if_exists(t_assembler *as, char *param, int mode)
{
	t_label	*tmp;

	if (mode == 1)
		tmp = as->labels;
	if (mode == 2)
		tmp = as->param_labels;
	while (tmp)
	{
		if (ft_strcmp(param, tmp->name) == 0)
			return (SUCCESS);
		tmp = tmp->next;
	}
	return (FAIL);
}

/*
** save_label_to_check() create a list of existing label, to check later if
** we are trying to create an already existing label
*/

void	save_label_to_check(t_assembler *as, char *label)
{
	t_label	*tmp;
	t_label	*new;

	if (check_if_exists(as, label, 1) == SUCCESS)
		manage_error(as, &free_asm, as->epure_line, LABEL_ALRDY_EXIST);
	tmp = as->labels;
	if (!(new = ft_memalloc(sizeof(t_label))))
		manage_error(as, &free_asm, as->epure_line, ERROR_MALLOC);
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		as->labels = new;
	if (!(new->name = ft_strdup(label)))
		manage_error(as, &free_asm, as->epure_line, ERROR_MALLOC);
}

/*
** save_label_param() create a list of label parameter, to check later if
** the label associated truly exists
*/

void	save_label_param(t_assembler *as, char *param)
{
	t_label	*tmp;
	t_label	*new;

	if (check_if_exists(as, param, 2) == SUCCESS)
		return ;
	tmp = as->param_labels;
	if (!(new = ft_memalloc(sizeof(t_label))))
		manage_error(as, &free_asm, as->epure_line, ERROR_MALLOC);
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		as->param_labels = new;
	if (!(new->name = ft_strdup(param)))
		manage_error(as, &free_asm, as->epure_line, ERROR_MALLOC);
}

/*
** check_existing_labels() checks both lists of label and parameter containing
** a label, to check if the label parameter refers to an existing label
*/

int		check_existing_labels(t_assembler *as)
{
	t_label	*tmp_label;
	t_label	*tmp_params;

	tmp_label = as->labels;
	tmp_params = as->param_labels;
	while (tmp_params)
	{
		while (tmp_label)
		{
			if (ft_strcmp(tmp_label->name, tmp_params->name) == 0)
			{
				tmp_label = as->labels;
				break;
			}
			if (tmp_label->next == NULL)
				manage_error(as, &free_asm, tmp_params->name, NO_EXIST_LABEL);
			tmp_label = tmp_label->next;
		}
		tmp_params = tmp_params->next;
	}
	return (SUCCESS);
}
