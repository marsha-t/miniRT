/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_translation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:41:34 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/25 14:07:59 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	translate_camera(t_meta *meta_data)
{
	if (meta_data->rot_x_i)
	{
		meta_data->pixel.theta_x += 0.001;
		if (meta_data->pixel.theta_x > (2 * M_PI))
			meta_data->pixel.theta_x = 0;
		rotate_camera_x(&meta_data->camera->orient, meta_data->pixel.theta_x);
	}
	if (meta_data->rot_x_d)
	{
		meta_data->pixel.theta_x -= 0.001;
		if (meta_data->pixel.theta_x < 0)
			meta_data->pixel.theta_x = 2 * M_PI;
		rotate_camera_x(&meta_data->camera->orient, meta_data->pixel.theta_x);
	}
	if (meta_data->rot_y_i)
	{
		meta_data->pixel.theta_y += 0.001;
		if (meta_data->pixel.theta_y > (2 * M_PI))
			meta_data->pixel.theta_y = 0;
		rotate_camera_y(&meta_data->camera->orient, meta_data->pixel.theta_y);
	}
	else
		translate_camera_a(meta_data);
}

void	translate_camera_a(t_meta *meta_data)
{
	if (meta_data->rot_y_d)
	{
		meta_data->pixel.theta_y -= 0.001;
		if (meta_data->pixel.theta_y < 0)
			meta_data->pixel.theta_y = 2 * M_PI;
		rotate_camera_y(&meta_data->camera->orient, meta_data->pixel.theta_y);
	}
	if (meta_data->rot_z_i)
	{
		meta_data->pixel.theta_z += 0.001;
		if (meta_data->pixel.theta_z > (2 * M_PI))
			meta_data->pixel.theta_z = 0;
		rotate_camera_z(&meta_data->camera->orient, meta_data->pixel.theta_z);
	}
	else
		translate_camera_b(meta_data);
}

void	translate_camera_b(t_meta *meta_data)
{
	if (meta_data->rot_z_d)
	{
		meta_data->pixel.theta_z -= 0.001;
		if (meta_data->pixel.theta_z < 0)
			meta_data->pixel.theta_z = 2 * M_PI;
		rotate_camera_z(&meta_data->camera->orient, meta_data->pixel.theta_z);
	}
	if (meta_data->rot_reset)
	{
		meta_data->pixel.theta_x = 0;
		meta_data->pixel.theta_y = 0;
		meta_data->pixel.theta_z = 0;
		meta_data->camera->orient = meta_data->orient;
	}
}
