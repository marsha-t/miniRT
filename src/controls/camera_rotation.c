/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:39:56 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/25 14:01:57 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	rotate_camera_y(t_vector *orientation, double theta_y)
{
	double	cos_theta;
	double	sin_theta;
	double	new_x;
	double	new_z;

	cos_theta = cos(theta_y);
	sin_theta = sin(theta_y);
	new_x = (cos_theta * orientation->x) + (sin_theta * orientation->z);
	new_z = (-sin_theta * orientation->x) + (cos_theta * orientation->z);
	orientation->x = new_x;
	orientation->z = new_z;
}

void	rotate_camera_x(t_vector *orientation, double theta_x)
{
	double	cos_theta;
	double	sin_theta;
	double	new_y;
	double	new_z;

	cos_theta = cos(theta_x);
	sin_theta = sin(theta_x);
	new_y = (cos_theta * orientation->y) - (sin_theta * orientation->z);
	new_z = (sin_theta * orientation->y) + (cos_theta * orientation->z);
	orientation->y = new_y;
	orientation->z = new_z;
}

void	rotate_camera_z(t_vector *orientation, double theta_z)
{
	double	cos_theta;
	double	sin_theta;
	double	new_x;
	double	new_y;

	cos_theta = cos(theta_z);
	sin_theta = sin(theta_z);
	new_x = (cos_theta * orientation->x) - (sin_theta * orientation->y);
	new_y = (sin_theta * orientation->x) + (cos_theta * orientation->y);
	orientation->x = new_x;
	orientation->y = new_y;
}

void	ft_rotation_status(t_meta *meta_data, int key, bool status)
{
	if (key == KEY_U)
		meta_data->rot_x_i = status;
	if (key == KEY_J)
		meta_data->rot_x_d = status;
	if (key == KEY_I)
		meta_data->rot_y_i = status;
	if (key == KEY_K)
		meta_data->rot_y_d = status;
	if (key == KEY_O)
		meta_data->rot_z_i = status;
	if (key == KEY_L)
		meta_data->rot_z_d = status;
	if (key == KEY_R)
		meta_data->rot_reset = status;
}
