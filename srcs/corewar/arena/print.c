/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sregnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 14:47:50 by sregnard          #+#    #+#             */
/*   Updated: 2019/11/24 16:15:18 by sregnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		print_visu(t_vm *vm, unsigned int cur, unsigned int len,
		unsigned int i)
{
	unsigned int	color;

	color = vm->colors[i];
	color < 10 ?
		init_pair(color, color, -1) : init_pair(color, -1, color -10);
	attron(COLOR_PAIR(color));
	printw("%02x", vm->arena[i++]);
	attroff(COLOR_PAIR(color));
	i - (cur * len) < len ? printw(" ") : printw("\n");
}

static void		print_dump(t_vm *vm, unsigned int cur, unsigned int len,
		unsigned int i)
{
	unsigned int	color;

	color = vm->colors[i] + 30;
	ft_printf("\033[1;%dm", color);
	ft_printf("%02x", vm->arena[i++]);
	ft_printf("\033[0m");
	i - (cur * len) < len ? ft_printf(" ") : ft_printf("\n");
}

static void		print_line(t_vm *vm, unsigned int cur, unsigned int len)
{
	unsigned int	i;

	i = cur * len;
	while (i - (cur * len) < len)
	{
		if (vm->flags & VM_VISU)
			print_visu(vm, cur, len, i);
		else
			print_dump(vm, cur, len, i);
		++i;
	}
}

void		arena_print(t_vm *vm, unsigned int cols)
{
	unsigned int	cur;

	if (!vm)
		return ; 
	cur = 0;
	if (vm->flags & VM_VISU)
	{
		erase();
		printw("Cycle %d\n", vm->cycle);
	}
	while (cur < MEM_SIZE / cols)
		print_line(vm, cur++, cols);
	refresh();
	usleep(10000);
}

