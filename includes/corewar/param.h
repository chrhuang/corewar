/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:28:41 by sregnard          #+#    #+#             */
/*   Updated: 2019/11/17 12:01:50 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAM_H
# define PARAM_H

# include "corewar.h"

typedef struct			s_param
{
	struct s_param		*next;
	struct s_params		*list;
	struct s_champ		*champ;
	struct s_command	*cmd;
}						t_param;

typedef struct			s_params
{
	t_param				*first;
	t_param				*cur;
	t_param				*last;
	unsigned int		size;
}						t_params;

#endif
