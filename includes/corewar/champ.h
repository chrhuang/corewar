/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:28:41 by sregnard          #+#    #+#             */
/*   Updated: 2019/11/10 16:07:10 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAMP_H
# define CHAMP_H

# include "corewar.h"

typedef struct		s_champ
{
	char			*file;
	char			content[BUFF_SIZE + 1];
	int				size;
	int				cursor;
	unsigned int	magic;
	char			name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
	t_labels		*labels;
	t_labels		*labels_queue;
	t_commands		*cmds;
	t_processes		*procs;
	struct s_champ	*next;
}					t_champ;

typedef struct		s_champs
{
	t_champ			*first;
	t_champ			*cur;
	t_champ			*last;
	unsigned int	size;
}					t_champs;

#endif
