/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 17:17:15 by lgaultie          #+#    #+#             */
/*   Updated: 2019/11/17 19:15:13 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUC_H
# define INSTRUC_H

# include "asm.h"

typedef struct				s_instruc
{
	char					*label;
	char					*command;
	char					*param[4];
	struct s_instruc		*next;
	struct s_instruc		*prev;
}							t_instruc;

#endif
