/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_coord.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:56:07 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/11 21:13:08 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
	check_coord iterates through each input value and check if each character
	is a digit. Also checks if the number of inputs is equal to three.
	if condition fails, it frees the allocated memories and exits the program
*/
t_vector	check_coord(t_meta **meta_data, void *temp, char **src, char **argv)
{
	t_vector	vec;
	int			index;
	int			arg_count;

	arg_count = -1;
	while (argv[++arg_count])
	{
		index = -1;
		while (argv[arg_count][++index])
		{
			if (ft_isdigit(argv[arg_count][index]) == 0 && \
				argv[arg_count][index] != '.' && argv[arg_count][index] != '-' \
				&& argv[arg_count][index] != '+')
				coord_exit(meta_data, temp, src, argv);
		}
	}
	if (arg_count != 3)
		coord_exit(meta_data, temp, src, argv);
	vec.x = ft_strtod(argv[0]);
	vec.y = ft_strtod(argv[1]);
	vec.z = ft_strtod(argv[2]);
	return (vec);
}

void	coord_exit(t_meta **meta_data, void *temp, char **src, char **argv)
{
	if (temp != NULL)
		free(temp);
	if (src != NULL)
		free_pointer(src);
	if (argv != NULL)
		free_pointer(argv);
	ft_printf(RED"Incorrect XYZ input values\n"RST);
	free_exit(*meta_data);
	exit(EXIT_FAILURE);
}
