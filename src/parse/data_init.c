/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:53:09 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/27 17:28:18 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	meta_data_init(t_meta *meta_data)
{
	meta_data->amlight = NULL;
	meta_data->camera = NULL;
	meta_data->pixel.theta_x = 0;
	meta_data->pixel.theta_y = 0;
	meta_data->pixel.theta_z = 0;
	meta_data->pixel.cam_theta_x = 0;
	meta_data->pixel.cam_theta_y = 0;
	meta_data->pixel.cam_theta_z = 0;
	meta_data->light = NULL;
	meta_data->spotlight = NULL;
	meta_data->sp = NULL;
	meta_data->pl = NULL;
	meta_data->cy = NULL;
	meta_data->cn = NULL;
	meta_data->light_allocated = false;
	meta_data->camera_allocated = false;
	meta_data->amlight_allocated = false;
	meta_data->sp_allocated = false;
	meta_data->sl_allocated = false;
	meta_data->pl_allocated = false;
	meta_data->cy_allocated = false;
	meta_data->cn_allocated = false;
	meta_data_init_a(meta_data);
}

void	meta_data_init_a(t_meta *meta_data)
{
	meta_data->row = WINDOW_HEIGHT;
	meta_data->col = WINDOW_WIDTH;
	meta_data->pixel.coeff_ref = 0.5;
	meta_data->pixel.shine_fac = 20;
	meta_data->pixel.spot_theta = 10;
	meta_data->pixel.spot_p = 100;
	meta_data->pixel.spot_k0 = 0.001;
	meta_data->pixel.spot_k1 = 0.0001;
	meta_data->pixel.spot_k2 = 0.00001;
	meta_data->low_quality = false;
	meta_data->mid_quality = false;
	meta_data->colour_init.r = 0;
	meta_data->colour_init.g = 0;
	meta_data->colour_init.b = 0;
	meta_data->step_x = 3;
	meta_data->step_y = 1;
	meta_data->move = false;
	meta_data->rotate = false;
	meta_data->move_x_i = false;
	meta_data->move_x_d = false;
	meta_data->move_y_i = false;
	meta_data->move_y_d = false;
	meta_data->move_z_i = false;
	meta_data->move_z_d = false;
	meta_data_init_b(meta_data);
}

void	meta_data_init_b(t_meta *meta_data)
{
	meta_data->rot_x_i = false;
	meta_data->rot_x_d = false;
	meta_data->rot_y_i = false;
	meta_data->rot_y_d = false;
	meta_data->rot_z_i = false;
	meta_data->rot_z_d = false;
	meta_data->rot_reset = false;
	meta_data->pixel.theta_x = 0;
	meta_data->pixel.theta_y = 0;
	meta_data->pixel.theta_z = 0;
}
