/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:37:26 by lgaultie          #+#    #+#             */
/*   Updated: 2020/01/21 16:52:44 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	save_name_comment(t_assembler *as, int choice, char *str,
			char **dst)
{
	if (choice == SAVE_NAME)
	{
		if (ft_strlen(str) > PROG_NAME_LENGTH)
			manage_error(as, &free_asm, as->epure_line, NAME_TOO_LONG);
	}
	if (choice == SAVE_COMMENT)
	{
		if (ft_strlen(str) > COMMENT_LENGTH)
			manage_error(as, &free_asm, as->epure_line, COMM_TOO_LONG);
	}
	*dst = str;
}

/*
** check_quotes() parse only the name or comment (without ""), checks if they
** are too long or checks if invalid input after the name or comment
** (ex: .name "yes"no), etc...
*/

void	check_quotes(t_assembler *as, char **dst, int choice)
{
	char	*str;
	int		error;

	error = 0;
	if (dst && *dst)
		manage_error(as, &free_asm, as->epure_line, NAME_COMMENT_EXIST);
	if (!ft_strchr(as->line, '"'))
		manage_error(as, &free_asm, as->epure_line, NO_QUOTES);
	str = ft_strchr(as->line, '"') + 1;
	if (ft_strchr(str, '"') == NULL)
		manage_error(as, &free_asm, as->epure_line, QUOTES_NOT_CLOSED);
	if (!(ft_strchr(str, '"')))
		error = 1;
	if (error == 0 && (ft_strcmp("", ft_strchr(str, '"') + 1) != 0))
		manage_error(as, &free_asm, as->epure_line, STUFF_AFTER);
	if (error == 0)
	{
		if (!(str = ft_strsub(str, 0, ft_strchr(str, '"') - str)))
			manage_error(as, &free_asm, as->epure_line, ERROR_MALLOC);
	}
	else
	{
		if (!(str = ft_strdup("")))
			manage_error(as, &free_asm, as->epure_line, ERROR_MALLOC);
	}
	save_name_comment(as, choice, str, dst);
}

static void	replace_by_spaces(t_assembler *as, char *str, int i)
{
	while (str[i])
	{
		if (str[i] == COMMENT_CHAR || str[i] == ';')
			str[i] = '\0';
		if (str[i] == '\t')
			str[i] = ' ';
		if (str[i] == '"')
			return ;
		if (str[i] != ' ')
			manage_error(as, &free_asm, as->epure_line, BAD_FORMAT);
		++i;
	}
}

/*
** epure name or comment line
*/

void	between_name_quote(t_assembler *as)
{
	char	*str;
	int		i;
	int		mode;
	int		length;

	str = as->line;
	i = 0;
	mode = 0;
	str = ft_strchr(str, '.');
	length = ft_strlen(NAME_CMD_STRING);
	if (str && ft_strncmp(NAME_CMD_STRING, str, length) == 0)
		mode = 1;
	length = ft_strlen(COMMENT_CMD_STRING);
	if (str && ft_strncmp(COMMENT_CMD_STRING, str, length) == 0)
		mode = 2;
	if (mode != 1 && mode != 2)
	{
		if (ft_strcmp(as->line, "") == 0)
			return ;
		manage_error(as, &free_asm, as->epure_line, BAD_FORMAT);
	}
	i = ft_strlen(mode == 1 ? NAME_CMD_STRING : COMMENT_CMD_STRING);
	replace_by_spaces(as, str, i);
}

void	change_sharp(t_assembler *as)
{
	char	*str;
	int		i;

	str = as->line;
	i = 0;
	while (str[i])
	{
		if (str[i] == COMMENT_CHAR || str[i] == ';')
		{
			str[i] = '\0';
			i = -1;
			while (as->line[++i])
				if (as->line[i] != ' ')
					return ;
			as->line[0] = '\0';
			return ;
		}
		i++;
	}
	i = -1;
	while (as->line[++i])
		if (as->line[i] != ' ')
			return ;
	as->line[0] = '\0';
}

char	*delete_space_after(t_assembler *as, char *str)
{
	char	*clean;
	int		i;

	if (!str)
		return (NULL);
	if ((clean = ft_strdup(str)) == NULL)
		manage_error(as, &free_asm, as->epure_line, ERROR_MALLOC);
	ft_printf("clean = %s\n", clean);
	i = ft_strlen(clean) - 1;
	if (i < 0)
		return (clean);
	while (clean[i] == ' ' || clean[i] == '\t')
		clean[i--] = '\0';
	return (clean);
}

void	check_before_dot(t_assembler *as, char *str)
{
	int		i;
	int		count;
	count = 0;
	i = 0;
	if (str)
	{
		while (as->line && as->line[i] != '.')
		{
			if (as->line[i] != ' ' && as->line[i] != '\t')
				count++;
			i++;
		}
		if (count > 0)
			manage_error(as, &free_asm, as->epure_line, BEFORE_DOT);
	}
}

/*
** check_header() if there is no space in the header line, quit.
** if finds .name or .comment, parse string between quotes in our list.
*/

int		check_header(t_assembler *as)
{
	char	*len;
	char	*part;
	char	*str;
	char	*tmp;

	if (as->header->name && as->header->comment)
		return (FAIL);
	change_sharp(as);
	tmp = as->line;
	as->line = delete_space_after(as, tmp);
	ft_memdel((void **)&tmp);
	between_name_quote(as);
	str = as->line;
	if (str)
		str = ft_strchr(str, '.');
	check_before_dot(as, str);
	if (str == NULL || (len = ft_strchr(str, '"')) == NULL)
	{
		// ft_memdel((void **)as->line);
		return (FAIL);
	}
	ft_printf("len = %s\n", len);
	if (!(part = ft_strsub(str, 0, len - str)))
		manage_error(as, &free_asm, as->epure_line, ERROR_MALLOC);
	part = delete_space_after(as, part); // Leak ici normalement
	if (ft_strcmp(NAME_CMD_STRING, part) == 0)
	{
		ft_memdel((void**)&part);
		check_quotes(as, &as->header->name, SAVE_NAME);
		return (SUCCESS);
	}
	else if (ft_strcmp(COMMENT_CMD_STRING, part) == 0)
	{
		ft_memdel((void**)&part);
		check_quotes(as, &as->header->comment, SAVE_COMMENT);
		return (SUCCESS);
	}
	ft_printf("len = %s\n", len);
	ft_printf("Ne passe pas par ici\n");
	ft_memdel((void**)&part);
	return (FAIL);
}
