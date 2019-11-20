/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmouele <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 10:02:25 by cmouele           #+#    #+#             */
/*   Updated: 2019/11/17 17:09:52 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**			Frees a argument
*/

void		arg_free(t_arg **arg)
{
    ft_memdel((void **)arg);
}

/*
**			Frees all arguments in the list then the list itself
*/

void		args_free(t_args *args)
{
    while (args->first)
    {
        args->cur = args->first->next;
        arg_free(&args->first);
        args->first = args->cur;
    }
}
