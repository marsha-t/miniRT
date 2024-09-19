/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:32:19 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/11 21:32:19 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
	ft_fill_data checks the singleline for each id from the .rt file.
	Subsequently it assigns to the associated function of each id.
	if an unknown id is declared in the .rt file, the function exits
	the program
*/
void	ft_fill_data(t_meta *meta_data, char *singleline)
{
	char		**argv;

	argv = ft_split(singleline, ' ');
	free(singleline);
	if (ft_strncmp(argv[0], "A", 1) == 0 && ft_strlen(argv[0]) == 1)
	{
		fill_ambient(meta_data, argv);
		meta_data->amlight_allocated = true;
		ft_printf(G" OK \n"RST);
	}
	else if (ft_strncmp(argv[0], "C", 1) == 0 && ft_strlen(argv[0]) == 1)
	{
		fill_camera(meta_data, argv);
		meta_data->camera_allocated = true;
		ft_printf(G" OK \n"RST);
		meta_data->obj = (void *)meta_data->camera;
		meta_data->obj_select = 7;
		meta_data->obj_option->coord = &meta_data->camera->coord;
		meta_data->obj_option->size = &meta_data->camera->fov;
	}
	else
		ft_fill_light(meta_data, argv);
	free_pointer(argv);
}

void	ft_fill_light(t_meta *meta_data, char **argv)
{
	static int	light_count;
	t_light		*temp_light;

	if (ft_strncmp(argv[0], "L", 1) == 0 && ft_strlen(argv[0]) == 1)
	{
		if (light_count == 0)
		{
			meta_data->light = create_light(meta_data, argv);
			meta_data->light_allocated = true;
		}
		else
		{
			temp_light = meta_data->light;
			while (temp_light->next != NULL)
				temp_light = temp_light->next;
			temp_light->next = create_light(meta_data, argv);
		}
		light_count++;
	}
	else
		ft_fill_spotlight(meta_data, argv);
}

void	ft_fill_spotlight(t_meta *meta_data, char **argv)
{
	t_spotlight	*temp_spotlight;
	static int	spot_light_count;

	if (ft_strncmp(argv[0], "SL", 1) == 0 && ft_strlen(argv[0]) == 2)
	{
		if (spot_light_count == 0)
		{
			meta_data->spotlight = create_spotlight(meta_data, argv);
			meta_data->sl_allocated = true;
		}
		else
		{
			temp_spotlight = meta_data->spotlight;
			while (temp_spotlight->next != NULL)
				temp_spotlight = temp_spotlight->next;
			temp_spotlight->next = create_spotlight(meta_data, argv);
		}
		spot_light_count++;
	}
	else
		ft_fill_objects(meta_data, argv);
}

void	ft_fill_objects(t_meta *meta_data, char **argv)
{
	if ((ft_strncmp(argv[0], "pl", 2) == 0 || \
		ft_strncmp(argv[0], "sp", 2) == 0 || ft_strncmp(argv[0], "cy", 2) \
			== 0 || ft_strncmp(argv[0], "cn", 2) == 0) \
			&& ft_strlen(argv[0]) == 2)
		create_objects(meta_data, argv);
	else
	{
		ft_printf(RED"\tUNKNOWN OBJECT FOUND ...\n"RST);
		free_pointer(argv);
		free_exit(meta_data);
		exit(EXIT_FAILURE);
	}
}
