/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:53:41 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/26 12:43:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	free_exit(t_meta *meta_data)
{
	t_light		*light;
	t_spotlight	*spotlight;

	light = NULL;
	light = meta_data->light;
	spotlight = meta_data->spotlight;
	if (meta_data->amlight_allocated && meta_data->amlight != NULL)
		free(meta_data->amlight);
	if (meta_data->camera_allocated && meta_data->camera != NULL)
		free(meta_data->camera);
	while (meta_data->light_allocated && meta_data->light != NULL)
	{
		light = light->next;
		free(meta_data->light);
		meta_data->light = NULL;
		meta_data->light = light;
	}
	while (meta_data->sl_allocated && meta_data->spotlight != NULL)
	{
		spotlight = spotlight->next;
		free(meta_data->spotlight);
		meta_data->spotlight = NULL;
		meta_data->spotlight = spotlight;
	}
	free_objects(meta_data);
}

void	bump_exit(t_meta **meta_data, void *temp, char **src, char **argv)
{
	if (temp != NULL)
		free(temp);
	free_pointer(src);
	free_pointer(argv);
	ft_printf(RED"Error from mlx_xpm_file_to_image\n"RST);
	free_exit(*meta_data);
	exit(EXIT_FAILURE);
}

void	checker_exit(t_meta **meta_data, void *temp, char **src, char **argv)
{
	if (temp != NULL)
		free(temp);
	free_pointer(src);
	free_pointer(argv);
	ft_printf(RED"Incorrect no. of checkerboard arguments\n"RST);
	free_exit(*meta_data);
	exit(EXIT_FAILURE);
}
