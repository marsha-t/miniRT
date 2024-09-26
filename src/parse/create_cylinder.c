/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:07:18 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/26 09:44:59 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	cy_elements(t_meta *meta_data, t_cy *cy, char **argv)
{
	char	**coord;
	char	**axis;
	char	**colour;

	coord = ft_split(argv[1], ',');
	cy->coord = check_coord(&meta_data, cy, argv, coord);
	free_pointer(coord);
	axis = ft_split(argv[2], ',');
	cy->axis = check_norm(&meta_data, cy, argv, axis);
	free_pointer(axis);
	colour = ft_split(argv[5], ',');
	cy->colour = check_colour(&meta_data, cy, argv, colour);
	free_pointer(colour);
}

void	cy_bonus(t_meta *meta_data, t_cy *cy, char **argv)
{
	int		i;
	char	**bonus;

	i = 5;
	while (argv[++i])
	{
		bonus = ft_split(argv[i], ',');
		if (bonus[0][0] == 'c')
		{
			cy->checker = 1;
			cy->sqsize = check_checker(&meta_data, cy, argv, bonus);
			free_pointer(bonus);
			if (cy->sqsize.row < 1 || cy->sqsize.col < 1)
				cylinder_exit(meta_data, NULL, RED"Incorrect checkerboard square\
					size values\n"RST);
		}
		else if (bonus[0][0] == 'b')
		{
			cy->bump = 1;
			cy->bump_img = check_bump(&meta_data, cy, argv, bonus);
			free_pointer(bonus);
		}
		else
			cylinder_exit(meta_data, bonus, RED"Incorrect bonus\n"RST);
	}
}

/*
	create_cy creates a sphere object and check if each value is valid.
	returns t_cy pointer.
*/
t_cy	*create_cy(t_meta *meta_data, char **argv)
{
	t_cy	*cy;

	ft_printf(G"\tCYLINDER OBJECT ...\t"RST);
	cy = check_cy_args(meta_data, argv);
	cy_elements(meta_data, cy, argv);
	cy->diameter = check_double(&meta_data, cy, argv, argv[3]);
	cy->height = check_double(&meta_data, cy, argv, argv[4]);
	cy->checker = 0;
	cy->bump = 0;
	cy_bonus(meta_data, cy, argv);
	cy->next = NULL;
	ft_printf(G" OK \n"RST);
	return (cy);
}

t_cy	*check_cy_args(t_meta *meta_data, char **argv)
{
	t_cy	*cy;

	if (pointer_count(argv) < 6 || pointer_count(argv) > 8)
		cylinder_exit(meta_data, argv, RED"Incorrect CY data <cy X,Y,Z NVector diameter height RGB\
			[checkerboard] [bumpmap]>\n"RST);
	cy = malloc(sizeof(t_cy));
	if (!cy)
		cylinder_exit(meta_data, argv, NULL);
	return (cy);
}

void	cylinder_exit(t_meta *meta_data, char **argv, char *message)
{
	free_args(meta_data, argv);
	if (message != NULL)
		ft_printf(message);
	exit(EXIT_FAILURE);
}
