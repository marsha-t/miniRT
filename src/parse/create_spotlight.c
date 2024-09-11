/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_spotlight.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:36:32 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/11 21:39:37 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_spotlight	*create_spotlight(t_meta *meta_data, char **argv)
{
	char		**coordspotlight_p;
	char		**rgb;
	char		**spot_dir;
	t_spotlight	*temp_spotlight;

	ft_printf(G"\tSPOTLIGHT SETTINGS ...\t"RST);
	temp_spotlight = check_spotlight_args(meta_data, argv);
	coordspotlight_p = ft_split(argv[1], ',');
	temp_spotlight->coord = check_coord(&meta_data, temp_spotlight, \
		argv, coordspotlight_p);
	free_pointer(coordspotlight_p);
	spot_dir = ft_split(argv[2], ',');
	temp_spotlight->spot_dir = check_norm(&meta_data, \
		temp_spotlight, argv, spot_dir);
	free_pointer(spot_dir);
	temp_spotlight->brightness = check_double(&meta_data, \
		temp_spotlight, argv, argv[3]);
	rgb = ft_split(argv[4], ',');
	temp_spotlight->colour = check_colour(&meta_data, \
		temp_spotlight, argv, rgb);
	free_pointer(rgb);
	temp_spotlight->next = NULL;
	ft_printf(G" OK \n"RST);
	return (temp_spotlight);
}

t_spotlight	*check_spotlight_args(t_meta *meta_data, char **argv)
{
	t_spotlight	*temp_spotlight;

	if (pointer_count(argv) != 5)
	{
		ft_printf(RED"Incorrect SPOTLIGHT data <C X,Y,Z brightness RGB>\n"RST);
		free_pointer(argv);
		free_exit(meta_data);
		exit(EXIT_FAILURE);
	}
	temp_spotlight = malloc(sizeof(t_spotlight));
	if (!temp_spotlight)
	{
		free_pointer(argv);
		free_exit(meta_data);
		exit(EXIT_FAILURE);
	}
	return (temp_spotlight);
}
