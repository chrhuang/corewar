/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:46:37 by chrhuang          #+#    #+#             */
/*   Updated: 2019/11/27 14:25:41 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*s_to_cor(t_assembler *assembler, char *s)
{
	int		len;
	char	*cor;

	len = ft_strlen(s);
	if ((cor = ft_memalloc(sizeof(char) * (len + 4))) == NULL)
	{
		ft_memdel((void **)&cor);
		ft_error(assembler, NULL, ERROR_MALLOC);
	}
	ft_strncat(cor, s, len - 1);
	ft_strcat(cor, "cor");
	cor[len + 2] = '\0';
	return (cor);
}

void	create_cor(t_assembler *as)
{
	as->file_name_cor = s_to_cor(as, as->file_name_s);
	ft_printf("cor file = %s\n", as->file_name_cor);
	as->cor_fd = open(as->file_name_cor,O_RDWR | O_APPEND | O_CREAT, 0644); // Creation du fichier .cor
	write_header(as);
	write_instruc(as);
	// ft_printf("name = [%s]\ncomment = [%s]\n", assembler->header->name, assembler->header->comment);
	return ;
}
