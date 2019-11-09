/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:18:43 by chrhuang          #+#    #+#             */
/*   Updated: 2019/11/09 17:24:09 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	parsing(t_assembler *assembler)
{
	int		ret;
	int		fd;
	char	*line;

	ret = 1;
	fd = assembler->source_fd;
	while (ret != 0)
	{
		ret = get_next_line(fd, &line);
		if (ret != 0)
		{
			if (line[0] == '.')			//parsing avec aucune verif
				parse_name_comment(assembler, line);
			ft_memdel((void*)&line);
		ft_printf("ret = %d\n", ret);
		}
	ft_printf("parsing end\n");
	}
}
