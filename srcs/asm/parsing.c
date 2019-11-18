/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:18:43 by chrhuang          #+#    #+#             */
/*   Updated: 2019/11/18 17:05:23 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// Marche si label n'as pas de ':' à la fin

void	check_label(t_assembler *as, char *label)
{
	int	i;

	i = 0;
	while (label[i] != '\0')
	{
		if (ft_strchr(LABEL_CHARS, label[i]) == NULL)
			ft_error(as, &free_asm, "Label with a non LABEL_CHARS\n");
		i = i + 1;
	}
}

void	clean_line(char *line)
{
	char	replace[3];

	replace[0] = '\t';
	replace[1] = SEPARATOR_CHAR;
	replace[2] = '\0';
	line = ft_strreplace(line, replace, ' ');
}

/*
** parse_header() parse only the name or comment (without ""), checks if they
** are too long.
*/

void	parse_header(t_assembler *as, char *line, char **dst, int choice)
{
	char *str;

	if (dst && *dst)
		ft_error(as, &free_asm, NAME_COMMENT_EXIST);
	str = ft_strchr(line, '"') + 1;
	if (!(str = ft_strsub(str, 0, ft_strchr(str, '"') - str)))
		ft_error(as, &free_asm, "Malloc failed\n");
	if (choice == 1)
	{
		if (ft_strlen(str) > PROG_NAME_LENGTH)
			ft_error(as, &free_asm, "Program name is too long.\n");
	}
	if (choice == 2)
	{
		if (ft_strlen(str) > COMMENT_LENGTH)
			ft_error(as, &free_asm, "Comment is too long.\n");
	}
	*dst = str;
}

int		check_header(t_assembler *as, char *line)
{
	char	*len;

	if ((len = ft_strchr(line, ' ')) == NULL)
		return (0);
	clean_line(line);
	if (ft_strcmp(NAME_CMD_STRING, ft_strsub(line, 0, len - line)) == 0)
	{
		parse_header(as, line, &as->header->name, 1);
		return (1);
	}
	else if (ft_strcmp(COMMENT_CMD_STRING, ft_strsub(line, 0, len - line)) == 0)
	{
		parse_header(as, line, &as->header->comment, 2);
		return (1);
	}
	return (0);
}

void	parsing(t_assembler *as)
{
	int		fd;
	char	*line;

	fd = as->source_fd;
	while (get_next_line(fd, &line) == 1)
	{
		if (check_header(as, line) == 0)
			parse_instruction(as, line);
		ft_memdel((void*)&line);
	}
	print_instruc(as);
	ft_printf("Parsing end\n\n");
	ft_printf("name = %s\ncomment = %s\n", as->header->name, as->header->comment);
}
