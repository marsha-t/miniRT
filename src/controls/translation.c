/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:41:34 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/26 20:00:24 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	rotation(t_meta *meta_data)
{
	if (meta_data->rot_x_i)
	{
		meta_data->pixel.theta_x = 0.01;
		// meta_data->pixel.theta_x += 0.01;
		// if (meta_data->pixel.theta_x > (2 * M_PI))
		// 	meta_data->pixel.theta_x = 0;
		rotate_x(meta_data, meta_data->obj_option->orient, meta_data->pixel.theta_x);
	}
	if (meta_data->rot_x_d)
	{
		meta_data->pixel.theta_x = -0.01;
		// meta_data->pixel.theta_x -= 0.01;
		// if (meta_data->pixel.theta_x < 0)
		// 	meta_data->pixel.theta_x = 2 * M_PI;
		rotate_x(meta_data, meta_data->obj_option->orient, meta_data->pixel.theta_x);
	}
	if (meta_data->rot_y_i)
	{
		meta_data->pixel.theta_y = 0.01;
		// meta_data->pixel.theta_y += 0.01;
		// if (meta_data->pixel.theta_y > (2 * M_PI))
		// 	meta_data->pixel.theta_y = 0;
		rotate_y(meta_data, meta_data->obj_option->orient, meta_data->pixel.theta_y);
	}
	else
		rotation_a(meta_data);
}

void	rotation_a(t_meta *meta_data)
{
	if (meta_data->rot_y_d)
	{
		meta_data->pixel.theta_y = -0.01;
		
		// meta_data->pixel.theta_y -= 0.01;
		// if (meta_data->pixel.theta_y < 0)
		// 	meta_data->pixel.theta_y = 2 * M_PI;
		rotate_y(meta_data, meta_data->obj_option->orient, meta_data->pixel.theta_y);
	}
	if (meta_data->rot_z_i)
	{
		meta_data->pixel.theta_z = 0.01;
		// meta_data->pixel.theta_z += 0.01;
		// if (meta_data->pixel.theta_z > (2 * M_PI))
		// 	meta_data->pixel.theta_z = 0;
		rotate_z(meta_data, meta_data->obj_option->orient, meta_data->pixel.theta_z);
	}
	else
		rotation_b(meta_data);
}

void	rotation_b(t_meta *meta_data)
{
	if (meta_data->rot_z_d)
	{
		meta_data->pixel.theta_z = -0.01;
		// meta_data->pixel.theta_z -= 0.01;
		// if (meta_data->pixel.theta_z < 0)
		// 	meta_data->pixel.theta_z = 2 * M_PI;
		rotate_z(meta_data, meta_data->obj_option->orient, meta_data->pixel.theta_z);
	}
	if (meta_data->rot_reset)
	{
		printf("pressed reset\n");
		meta_data->pixel.theta_x = 0;
		meta_data->pixel.theta_y = 0;
		meta_data->pixel.theta_z = 0;
		*meta_data->obj_option->orient = meta_data->orient;
	}
}
