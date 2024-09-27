/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:10:24 by mateo             #+#    #+#             */
/*   Updated: 2024/09/27 17:27:58 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	rotate_camera_vectors(t_meta *meta_data)
{
	rotate_x(&meta_data->img_right, meta_data->pixel.cam_theta_x);
	rotate_x(&meta_data->img_forward, meta_data->pixel.cam_theta_x);
	rotate_x(&meta_data->img_up, meta_data->pixel.cam_theta_x);
	rotate_y(&meta_data->img_right, meta_data->pixel.cam_theta_y);
	rotate_y(&meta_data->img_forward, meta_data->pixel.cam_theta_y);
	rotate_y(&meta_data->img_up, meta_data->pixel.cam_theta_y);
	rotate_z(&meta_data->img_right, meta_data->pixel.cam_theta_z);
	rotate_z(&meta_data->img_forward, meta_data->pixel.cam_theta_z);
	rotate_z(&meta_data->img_up, meta_data->pixel.cam_theta_z);
	vec_normalise(&meta_data->img_right);
	vec_normalise(&meta_data->img_forward);
	vec_normalise(&meta_data->img_up);
	vec_cross_product(&meta_data->img_up, &meta_data->img_forward,
		&meta_data->img_right);
	vec_normalise(&meta_data->img_up);
}
void	rotate_camera_x(t_meta *meta_data)
{
	if (meta_data->rot_x_i)
	{
		meta_data->pixel.cam_theta_x += 0.01;
		if (meta_data->pixel.cam_theta_x < 0)
			meta_data->pixel.cam_theta_x = 2 * M_PI;
	}
	if (meta_data->rot_x_d)
	{
		meta_data->pixel.cam_theta_x += -0.01;
		if (meta_data->pixel.cam_theta_x < 0)
			meta_data->pixel.cam_theta_x = 2 * M_PI;
	}
	rotate_camera_y(meta_data);
}

void	rotate_camera_y(t_meta *meta_data)
{
	if (meta_data->rot_y_i)
	{
		meta_data->pixel.cam_theta_y += 0.01;
		if (meta_data->pixel.cam_theta_y < 0)
			meta_data->pixel.cam_theta_y = 2 * M_PI;
	}
	if (meta_data->rot_y_d)
	{
		meta_data->pixel.cam_theta_y += -0.01;
		if (meta_data->pixel.cam_theta_y < 0)
			meta_data->pixel.cam_theta_y = 2 * M_PI;
	}
	rotate_camera_z(meta_data);
}

void	rotate_camera_z(t_meta *meta_data)
{
	if (meta_data->rot_z_i)
	{
		meta_data->pixel.cam_theta_z += 0.01;
		if (meta_data->pixel.cam_theta_z > (2 * M_PI))
			meta_data->pixel.cam_theta_z = 0;
	}
	if (meta_data->rot_z_d)
	{
		meta_data->pixel.cam_theta_z += -0.01;
		if (meta_data->pixel.cam_theta_y < 0)
			meta_data->pixel.cam_theta_y = 2 * M_PI;
	}
	if (meta_data->rot_reset)
	{
		printf("pressed reset\n");
		meta_data->pixel.cam_theta_x = 0;
		meta_data->pixel.cam_theta_y = 0;
		meta_data->pixel.cam_theta_z = 0;
	}
	rotate_camera_vectors(meta_data);

}
