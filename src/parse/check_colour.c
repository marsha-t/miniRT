/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:18:30 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/11 22:30:55 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
	check_colour iterates through each input value and check if each character
	is a digit. Also checks if the number of inputs is equal to three and if
	the value is between 0 and 255.
	if condition fails, it frees the allocated memories and exits the program
*/
t_colour	check_colour(t_meta **meta_data, void *temp, char **src, \
	char **argv)
{
	t_colour	rgb;
	int			arg_count;

	arg_count = -1;
	while (argv[++arg_count])
	{
		if (!check_colour_val(*meta_data, src, arg_count, argv))
			colour_exit(meta_data, temp, src, argv);
	}
	if (arg_count != 3)
		colour_exit(meta_data, temp, src, argv);
	rgb.r = ft_atoi(argv[0]);
	rgb.g = ft_atoi(argv[1]);
	rgb.b = ft_atoi(argv[2]);
	return (rgb);
}

bool	check_colour_val(t_meta *meta_data, char **src, int arg_count, \
	char **argv)
{
	int	temp;
	int	index;

	index = -1;
	(void)meta_data;
	(void)src;
	while (argv[arg_count][++index])
	{
		if (ft_isdigit(argv[arg_count][index]) == 0 && \
			argv[arg_count][index] != '-' && argv[arg_count][index] != '+')
			return (false);
	}
	temp = ft_atoi(argv[arg_count]);
	if (!(temp >= 0 && temp <= 255) || arg_count >= 3)
		return (false);
	return (true);
}

void	colour_exit(t_meta **meta_data, void *temp, char **src, char **argv)
{
	if (temp != NULL)
		free(temp);
	free_pointerlist(2, src, argv);
	ft_printf(RED"Incorrect RGB input values\n"RST);
	free_exit(*meta_data);
	exit(EXIT_FAILURE);
}
