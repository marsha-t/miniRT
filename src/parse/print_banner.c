/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_banner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:29:13 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/11 22:29:31 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	print_spotlight(t_meta *meta_data)
{
	t_spotlight	*current_spotlight;

	current_spotlight = meta_data->spotlight;
	while (current_spotlight != NULL)
	{
		printf("spotlight: (%f, %f, %f) (%f, %f, %f)\n",
			current_spotlight->coord.x, current_spotlight->coord.y,
			current_spotlight->coord.z, current_spotlight->colour.r,
			current_spotlight->colour.g, current_spotlight->colour.b);
		current_spotlight = current_spotlight->next;
	}
}

void	print_banner(void)
{
	ft_printf(Y " _____________________________________\n");
	ft_printf("|            _       _ _____ _______  |\n");
	ft_printf("|           (_)     (_)  __ \\__   __| |\n");
	ft_printf("|  _ __ ___  _ _ __  _| |__) | | |    |\n");
	ft_printf("| | '_ ` _ \\| | '_ \\| |  _  /  | |    |\n");
	ft_printf("| | | | | | | | | | | | | \\ \\  | |    |\n");
	ft_printf("| |_| |_| |_|_|_| |_|_|_|  \\_\\ |_|    |\n");
	ft_printf("|_____________________________________|\n" RST);
	ft_printf(B "\t\t    by: mateo|emaravil\n" RST);
	return ;
}
