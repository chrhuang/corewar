/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaultie <lgaultie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:37:26 by lgaultie          #+#    #+#             */
/*   Updated: 2020/01/12 21:32:27 by lgaultie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** parse_header() parse only the name or comment (without ""), checks if they
** are too long or checks if invalid input after the name or comment
** (ex: .name "yes"no)
//a mettre en anglais:
//si on trouve pas de " dans la ligne ->error
// on chope la partie apres la premiere "
// si il y a pas une deuxieme " -->error
// on reverifie si il y a bien une deuxieme " (verif obligatoire pour -q),
// et on regarde ce quil y apres
// alors on va choper ce qui est entre parenthese, mais pas si
// il y a eu une erreur, parceque la size du malloc sera caca, dans ce
// je fais un malloc vide pour empecher les breakfree
*/

void	parse_header(t_assembler *as, char **dst, int choice)
{
	char	*str;
	int		error;

	error = 0;
	if (dst && *dst)
		manage_error(as, &free_asm, as->epure_line, NAME_COMMENT_EXIST);
		//si on trouve pas de " dans la ligne ->error
	if (!ft_strchr(as->line, '"'))
		manage_error(as, &free_asm, as->epure_line, NO_QUOTES);
	// on chope la partie apres la premiere "
	str = ft_strchr(as->line, '"') + 1;
	// si il y a pas une deuxieme " -->error
	if (ft_strchr(str, '"') == NULL)
		manage_error(as, &free_asm, as->epure_line, QUOTES_NOT_CLOSED);
	// on reverifie si il y a bien une deuxieme " (verif obligatoire pour -q),
	if (!(ft_strchr(str, '"')))
		error = 1;
	// et on regarde ce quil y apres
	if (error == 0 && (ft_strcmp("", ft_strchr(str, '"') + 1) != 0))
		manage_error(as, &free_asm, as->epure_line, STUFF_AFTER);
	// alors on va choper ce qui est entre parenthese, mais pas si
	// il y a eu une erreur, parceque la size du malloc sera caca, dans ce
	// je fais un malloc vide pour empecher les breakfree
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
** epure name or comment line
*/

void	between_name_quote(t_assembler *as)
{
	char	*str;
	int		i;
	int		mode;

	str = as->line;
	i = 0;
	mode = 0;
	str = ft_strchr(str, '.'); //pour eviter de buger sur \t.name ou space.comment
	if (str && ft_strncmp(NAME_CMD_STRING, str, ft_strlen(NAME_CMD_STRING)) == 0)
		mode = 1;
	if (str && ft_strncmp(COMMENT_CMD_STRING, str, ft_strlen(COMMENT_CMD_STRING)) == 0)
		mode = 2;
	ft_printf("mode = %d\n", mode);
	if (mode != 1 && mode != 2)
	{
		if (ft_strcmp(as->line, "") == 0)
			return ;
		ft_printf("str = %s\n", str);
		manage_error(as, &free_asm, as->epure_line, BAD_FORMAT);
	}
	i = ft_strlen(mode == 1 ? NAME_CMD_STRING : COMMENT_CMD_STRING);
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
	i = ft_strlen(clean) - 1;
	if (i < 0)
		return (clean);
	while (clean[i] == ' ' || clean[i] == '\t')
		clean[i--] = '\0';
	return (clean);
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

	if (as->header->name && as->header->comment)
		return (FAIL);
	change_sharp(as);
	as->line = delete_space_after(as, as->line); // Leaks ICI ! ATTENTION
	// as->line = ft_strclean(as->line); // Leaks ICI ! ATTENTION
	between_name_quote(as);
	str = as->line;
	if (str)
		str = ft_strchr(str, '.'); //pour eviter de buger sur \t.name ou space.comment
	if (str == NULL || (len = ft_strchr(str, ' ')) == NULL)
		return (FAIL);
	if (!(part = ft_strsub(str, 0, len - str)))
		manage_error(as, &free_asm, as->epure_line, ERROR_MALLOC);
	if (ft_strcmp(NAME_CMD_STRING, part) == 0)
	{
		ft_printf("we go to save the name!\n");
		ft_memdel((void**)&part);
		parse_header(as, &as->header->name, SAVE_NAME);
		return (SUCCESS);
	}
	else if (ft_strcmp(COMMENT_CMD_STRING, part) == 0)
	{
		ft_memdel((void**)&part);
		parse_header(as, &as->header->comment, SAVE_COMMENT);
		return (SUCCESS);
	}
	ft_memdel((void**)&part);
	return (FAIL);
}
