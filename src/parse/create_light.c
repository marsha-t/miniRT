/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:32:45 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/11 22:31:37 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
    create_light creates a light source object and check if each value is valid.
    returns t_light pointer.
*/
t_light	*create_light(t_meta *meta_data, char **argv)
{
	char	**coordlight_p;
	char	**rgb;
	t_light	*temp_light;

	ft_printf(G"\tLIGHT SETTINGS ...\t"RST);
	temp_light = check_light_args(meta_data, argv);
	coordlight_p = ft_split(argv[1], ',');
	temp_light->coord = check_coord(&meta_data, temp_light, argv, coordlight_p);
	free_pointer(coordlight_p);
	temp_light->brightness = check_double(&meta_data, temp_light, argv, \
		argv[2]);
	rgb = ft_split(argv[3], ',');
	temp_light->colour = check_colour(&meta_data, temp_light, argv, rgb);
	free_pointer(rgb);
	temp_light->next = NULL;
	ft_printf(G" OK \n"RST);
	return (temp_light);
}

t_light	*check_light_args(t_meta *meta_data, char **argv)
{
	t_light	*temp_light;

	if (pointer_count(argv) != 4)
	{
		ft_printf(RED"Incorrect LIGHT data <C X,Y,Z brightness RGB>\n"RST);
		free_pointer(argv);
		free_exit(meta_data);
		exit(EXIT_FAILURE);
	}
	temp_light = malloc(sizeof(t_light));
	if (!temp_light)
	{
		free_pointer(argv);
		free_exit(meta_data);
		exit(EXIT_FAILURE);
	}
	return (temp_light);
}
