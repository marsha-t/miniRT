/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_camera_ambient.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:19:13 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/11 22:52:10 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
	fill_ambient associats with the ambient setting of the ray tracing.
	this function fills out the amlight pointer of t_meta struct.
	allocates t_amlight and fills out the input values from the .rt file.
*/
void	fill_ambient(t_meta *meta_data, char **argv)
{
	char		**rgb;
	static int	count;

	meta_data->amlight = NULL;
	ft_printf(G"\tAMBIENT LIGHT ...\t"RST);
	if (pointer_count(argv) != 3 || (count > 0))
	{
		if ((count > 0))
			ft_printf(RED"\tMultiple declaration of Ambient light values\n"RST);
		else
			ft_printf(RED"\tIncorrect ambient data <A ratio RGBcolors>\n"RST);
		fill_exit(meta_data, argv);
	}
	count++;
	meta_data->amlight = malloc(sizeof(t_amlight));
	if (!meta_data->amlight)
		fill_exit(meta_data, argv);
	meta_data->amlight->amlight_ratio = check_double(&meta_data, \
		NULL, argv, argv[1]);
	rgb = ft_split(argv[2], ',');
	meta_data->amlight->colour = check_colour(&meta_data, NULL, argv, rgb);
	free_pointer(rgb);
}

/*
	fill_camera associats with the camera setting of the ray tracing.
	this function fills out the camera pointer of t_meta struct.
	allocates t_camera and fills out the input values from the .rt file.
*/
void	fill_camera(t_meta *meta_data, char **argv)
{
	char		**coord_p;
	char		**orient_p;
	static int	count;

	ft_printf(G"\tCAMERA SETTINGS ...\t"RST);
	fill_camera_args(meta_data, count, argv);
	count++;
	meta_data->camera = malloc(sizeof(t_camera));
	if (!meta_data->camera)
		fill_exit(meta_data, argv);
	coord_p = ft_split(argv[1], ',');
	meta_data->camera->coord = check_coord(&meta_data, NULL, argv, coord_p);
	free_pointer(coord_p);
	orient_p = ft_split(argv[2], ',');
	meta_data->camera->orient = check_norm(&meta_data, NULL, argv, orient_p);
	vec_normalise(&meta_data->camera->orient);
	free_pointer(orient_p);
	meta_data->camera->fov = check_double(&meta_data, NULL, argv, argv[3]);
	if (meta_data->camera->fov > 180)
		fill_exit(meta_data, argv);
}

void	fill_camera_args(t_meta *meta_data, int count, char **argv)
{
	if (pointer_count(argv) != 4)
	{
		ft_printf(RED"Incorrect camera data <C XYZ NormVector FOV>\n" RST);
		fill_exit(meta_data, argv);
	}
	if (count > 0)
	{
		ft_printf(RED"Multiple declaration of Camera values\n"RST);
		fill_exit(meta_data, argv);
	}
	return ;
}

void	fill_exit(t_meta *meta_data, char **argv)
{
	free_pointer(argv);
	free_exit(meta_data);
	exit(EXIT_FAILURE);
}
