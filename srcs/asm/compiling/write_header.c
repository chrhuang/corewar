/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhuang <chrhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 15:56:44 by lgaultie          #+#    #+#             */
/*   Updated: 2020/01/21 18:02:07 by chrhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** write_padding with padding_size
*/

void		write_padding(int fd, int size)
{
	int	i;

	i = -1;
	if (size <= 0)
		return ;
	while (++i)
		write(fd, "\0", 1);
}

/*
** write_big_endian1() change the order of magic number's bytes
*/

static void	write_big_endian1(int fd, int magic_number)
{
	unsigned char	octets[4];

	octets[0] = magic_number >> 24;
	octets[1] = magic_number >> 16;
	octets[2] = magic_number >> 8;
	octets[3] = magic_number >> 0;
	write(fd, octets, 4);
}

/*
** write_name() writes magic number, then writes champion's name,
** then fills the rest of the place reserved for the name with 0.
*/

static void	write_name(t_assembler *as)
{
	int		len_name;
	int		len_reserved;
	char	*reserved;

	write_big_endian1(as->cor_fd, COREWAR_EXEC_MAGIC);
	len_name = ft_strlen(as->header->name);
	write(as->cor_fd, as->header->name, len_name);
	len_reserved = PROG_NAME_LENGTH - len_name;
	if (!(reserved = ft_memalloc(sizeof(char) * len_reserved)))
		manage_error(as, &free_asm, ERROR_MALLOC);
	write(as->cor_fd, reserved, len_reserved);
	ft_memdel((void *)&reserved);
}

/*
** write_name() writes padding of 4, then writes the comment,
** then fills the rest of the place reserved for the comment with 0, and
** another padding.
*/

static void	write_comment(t_assembler *as)
{
	char	*to_fill;
	int		size_com;

	write(as->cor_fd, "\0\0\0\0", 4);
	size_com = ft_strlen(as->header->comment);
	write_big_endian1(as->cor_fd, as->prog_size);
	write(as->cor_fd, as->header->comment, size_com);
	if (!(to_fill = ft_memalloc(sizeof(char) * COMMENT_LENGTH - size_com)))
		manage_error(as, &free_asm, ERROR_MALLOC);
	write(as->cor_fd, to_fill, COMMENT_LENGTH - size_com);
	write(as->cor_fd, "\0\0\0\0", 4);
	ft_memdel((void*)&to_fill);
}

void		write_header(t_assembler *as)
{
	write_name(as);
	write_comment(as);
}
