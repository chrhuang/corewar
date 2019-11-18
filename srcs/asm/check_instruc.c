/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 21:57:13 by lgaultie          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/11/18 17:20:38 by lgaultie         ###   ########.fr       */
=======
/*   Updated: 2019/11/18 17:16:10 by chrhuang         ###   ########.fr       */
>>>>>>> 44979186b012c20f444fbca1b84d2e77c03201f3
/*                                                                            */
/* ************************************************************************** */

# include "asm.h"

int		tab_len(char **tab)
{
	int		i;
		i = 0;
	while (tab[i] != '\0')
		i++;
	return (i);
}

/*
** check_label_chars() label characters: "abcdefghijklmnopqrstuvwxyz_0123456789"
*/

int		check_label_chars(t_assembler *as, char *str)
{
	int	i;
	int	j;
	int	len_j;
	int	len_i;

	i = 0;
	j = 0;
	ft_printf("str = %s\n", str);
	len_j = ft_strlen(LABEL_CHARS);
	len_i = ft_strlen(str);
	while (i < len_i && j < len_j && str[i] != LABEL_CHARS[j])
	{
		j++;
		if (j == 37)
		{
			ft_printf("%s --> ", str);
			ft_error(as, &free_asm, "Label with invalid characters.\n");
		}
		if (str[i] == LABEL_CHARS[j])
		{
			i++;
			j = 0;
		}
	}
	return (1);
}

/*
** is_label() checks if it's a label /!\ possible d'avoir un label invalide ? (ex trop long)
*/

int		is_label(t_assembler *as, char *part)
{
	char *ret;
	char *str;

	if ((ret = ft_strchr(part, LABEL_CHAR)) == NULL)
		return (0);
	if (!(str = ft_strsub(part, 0,  ft_strchr(part,  LABEL_CHAR) - part)))
		ft_error(as, &free_asm, "Malloc failed\n");
		//faut checker si le label est bien composé de label chars
	if (ft_strcmp(ret, ":") == 0)
	{
		check_label_chars(as, str);
		return (1);
	}
	return (0);
}

<<<<<<< HEAD
/*
** which_command() initiates the arrays of all commands and checks them.
*/

int		which_command(t_assembler *as, char *part)
{
	int		i;

	i = 0;
	as->commands[0] = "live";
	as->commands[1] = "ld";
	as->commands[2] = "st";
	as->commands[3] = "add";
	as->commands[4] = "sub";
	as->commands[5] = "and";
	as->commands[6] = "or";
	as->commands[7] = "xor";
	as->commands[8] = "zjmp";
	as->commands[9] = "ldi";
	as->commands[10] = "sti";
	as->commands[11] = "fork";
	as->commands[12] = "lld";
	as->commands[13] = "lldi";
	as->commands[14] = "lfork";
	as->commands[15] = "add";
	while (i < 16 && ft_strcmp(part, as->commands[i]) != 0)
		i++;
	return (i);
=======
int		is_command(t_assembler *as, char *part)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (ft_strcmp(part, as->commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
	// if (ft_strcmp(part, "live") != 0 && ft_strcmp(part, "ld") != 0 \
	// && ft_strcmp(part, "st") != 0 && ft_strcmp(part, "add") != 0 \
	// && ft_strcmp(part, "sub") != 0 && ft_strcmp(part, "and") != 0 \
	// && ft_strcmp(part, "or") != 0 && ft_strcmp(part, "xor") != 0 \
	// && ft_strcmp(part, "zjmp") != 0 && ft_strcmp(part, "ldi") != 0 \
	// && ft_strcmp(part, "sti") != 0 && ft_strcmp(part, "fork") != 0 \
	// && ft_strcmp(part, "lld") != 0 && ft_strcmp(part, "lldi") != 0 \
	// && ft_strcmp(part, "lfork") != 0 && ft_strcmp(part, "aff") != 0)
	// 	return (0);
	// return (1);
>>>>>>> 44979186b012c20f444fbca1b84d2e77c03201f3
}

/*
** is_param() checks if the params are compatible with the command given
*/

int		is_param(int id_command, char *part)
{
	// EN COURS
	(void)part;
	(void)id_command;
	return (0);
}

/*
** check_instruc() splits the line to check each part, once all is good,
** call add_instruc to save the line.
*/

void	check_instruc(t_assembler *as, char *line)
{
	char	**tab;
	int		len;
	int		i;
	int		id_command;

	i = 0;
	if (!(tab = ft_strsplit(line, ' ')))
		ft_error(as, &free_asm, "Malloc failed\n");
	len = tab_len(tab);
	while (i < len)
	{
<<<<<<< HEAD
		if (is_label(as, tab[i]) == 1)
			ft_printf("'%s' is a		label\n", tab[i]);
		else if ((id_command = which_command(as, tab[i])) < 16)
			ft_printf("'%s' is a		command\n", as->commands[id_command]);
		//envoyer id_command et verifier les params en fonction de la command
		else if (is_param(id_command, tab[i]) == 1)
			ft_printf("'%s' is a			param\n", tab[i]);
=======
		if (is_label(tab[i]) == 1)
			ft_printf("%s is a		label\n", tab[i]);
		else if (is_command(as, tab[i]) == 1)
			ft_printf("%s is a		command\n", tab[i]);
		else if (is_param(tab[i]) == 1)
			ft_printf("%s is a			param\n", tab[i]);
>>>>>>> 44979186b012c20f444fbca1b84d2e77c03201f3
		else
		{
			ft_printf("%s --> ", tab[i]);
			ft_printf("SYNTAX ERROR\n");
			// ft_error(as, &free_asm, "syntax error, element is neither a label nor a command nor a parameter\n");
		}
		i++;
	}
	add_instruct(as, line);
}
