/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:08:23 by chrhuang          #+#    #+#             */
/*   Updated: 2020/01/06 13:10:44 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** which_param() checks the type of the params
*/

char	which_params(t_assembler *as, char *param)
{
	char	*cpy;
	int		nb;

	if (!param || !*param)
		return (FAIL);
	if (*param == 'r')
	{
		param++;
		if (ft_strlen(param) <= 2 && ft_isnumber(param) &&
			(nb = ft_atoi(param)) <= REG_NUMBER && nb > 0)
			return (REG_CODE);
		manage_error(as, &free_asm, as->epure_line, WRONG_REGISTER);
			return (REG_CODE);	//pour le mode -q, evite davoir error sur numero trop haut de registre ET syntax param
	}
	else if (*param == DIRECT_CHAR)
	{
		param++;
		if (*param == LABEL_CHAR)
		{
			if (!(cpy = ft_strsub(param, 1, ft_strlen(param))))
				manage_error(as, &free_asm, as->epure_line, ERROR_MALLOC);
			save_label_param(as, cpy);
			ft_memdel((void**)&cpy);
		}
		if (*param == LABEL_CHAR || ft_isnumber(param))
			return (DIR_CODE);
	}
	else
	{
		if (*param == LABEL_CHAR)
		{
			if (!(cpy = ft_strsub(param, 1, ft_strlen(param))))
				manage_error(as, &free_asm, as->epure_line, ERROR_MALLOC);
			// ft_printf("cpy= %s\n", cpy);
			save_label_param(as, cpy);
			ft_memdel((void**)&cpy);
		}
		if (*param == LABEL_CHAR || ft_isnumber(param))
			return (IND_CODE);
	}
	return (FAIL);
}

/*
** check_param() checks if the param is compatible with the instruction
** type :
** 1 = register
** 2 = direct
** 4 = indirect
** 3 = 1 or 2 (register or direct)
** 5 = 1 or 4 (register or indirect)
** 6 = 2 or 4 (direct or indirect)
** 7 = 1 or 2 or 4 (all parameters accepted)
*/

char	check_param(t_assembler *as, int id_command, char id_param, int nb_param)
{
	int	type;

	type = as->commands[id_command].param[nb_param];
	if (type == 7 || type == id_param)
		return (1);
	else if (id_param == REG_CODE)
		return (type == 3 || type == 5 ? 1 : 0);
	else if (id_param == DIR_CODE)
		return (type == 3 || type == 6 ? 1 : 0);
	else if (id_param == IND_CODE)
		return (type == 5 || type == 6 ? 1 : 0);
	return (FAIL);
}

/*
** is_param() checks if the params are compatible with the command given
** nb_param stands for param 1, param 2, param 3, not the total number of params
** returns FAIL if we have 2 commands so is_command can lower the number of
** parameters.
*/

int		is_param(t_assembler *as, int id_command, char *part, int nb_param,
				char *param_type)
{
	char	id_param;

	if (which_command(as, part) < 16)
	{
		manage_error(as, &free_asm, as->epure_line, TOO_MANY_CMD);
		if (as->bonus & BONUS_DONT_QUIT)
			return (FAIL);
	}
	if (!(as->bonus & BONUS_DONT_QUIT) \
		&& as->nb_sep != as->commands[id_command].nb_params - 1)
		manage_error(as, &free_asm, as->epure_line, SEPARATOR_ERROR);
	if (nb_param + 1 > as->commands[id_command].nb_params)
		manage_error(as, &free_asm, as->epure_line, TOO_MANY_PARAM);
	if ((id_param = which_params(as, part)) == FAIL)
		manage_error(as, &free_asm, as->epure_line, INVALID_PARAM);
	param_type[nb_param] = id_param;
	if (check_param(as, id_command, id_param, nb_param) == FAIL)
		manage_error(as, &free_asm, as->epure_line, WRONG_COMMAND_PARAM);
	return (SUCCESS);
}
