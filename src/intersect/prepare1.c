/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 07:58:38 by mateo             #+#    #+#             */
/*   Updated: 2024/10/02 12:01:32 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	prepare_data adds derived data on image, light and objects
 */
void	prepare_data(t_meta *meta_data)
{
	meta_data->aspect_ratio = (double)(WINDOW_WIDTH) / (double)(WINDOW_HEIGHT);
	prepare_img(meta_data);
	prepare_light(meta_data);
	prepare_obj(meta_data);
}

/*	prepare_img	updates meta_data with img parameters:
	- i.e., dimensions, basis vectors and img center  */
void	prepare_img(t_meta *meta_data)
{
	double	fov_rad;

	fov_rad = deg_to_rad(meta_data->camera->fov);
	meta_data->img_width = tan(fov_rad / 2) * 2;
	meta_data->img_height = meta_data->img_width / meta_data->aspect_ratio;
	img_basis_vec(meta_data);
	if (meta_data->rotate == true && meta_data->obj_select == 7)
		rotate_camera_x(meta_data);
}

/*	img_basis_vec calculates the right and up vectors for image plane
	- world_up is (0, 1, 0)
		unless camera looks along y-axis (then it is (0, 0, 1))
	*/
void	img_basis_vec(t_meta *meta_data)
{
	t_vector	world_up;

	meta_data->img_forward.x = meta_data->camera->orient.x;
	meta_data->img_forward.y = meta_data->camera->orient.y;
	meta_data->img_forward.z = meta_data->camera->orient.z;
	world_up.x = 0;
	world_up.y = 1;
	world_up.z = 0;
	if (vec_cmp_num(&meta_data->img_forward, 0, 1, 0)
		|| vec_cmp_num(&meta_data->img_forward, 0, -1, 0))
	{
		world_up.x = 0;
		world_up.y = 0;
		world_up.z = 1;
	}
	vec_cross_product(&meta_data->img_right, &world_up,
		&meta_data->img_forward);
	vec_normalise(&meta_data->img_right);
	vec_cross_product(&meta_data->img_up, &meta_data->img_forward,
		&meta_data->img_right);
	vec_normalise(&meta_data->img_up);
}

/*	prepare_light adds derived parameters to light structs */
void	prepare_light(t_meta *meta_data)
{
	t_light		*curr;
	t_spotlight	*curr_spotlight;

	if (meta_data->amlight_allocated)
	{
		meta_data->amlight->colour.r_n = meta_data->amlight->colour.r / 255;
		meta_data->amlight->colour.g_n = meta_data->amlight->colour.g / 255;
		meta_data->amlight->colour.b_n = meta_data->amlight->colour.b / 255;
	}
	curr = meta_data->light;
	curr_spotlight = meta_data->spotlight;
	while (meta_data->light_allocated && curr)
	{
		curr->colour.r_n = curr->colour.r / 255;
		curr->colour.g_n = curr->colour.g / 255;
		curr->colour.b_n = curr->colour.b / 255;
		curr = curr->next;
	}
	while (meta_data->sl_allocated && curr_spotlight)
	{
		curr_spotlight->colour.r_n = curr_spotlight->colour.r / 255;
		curr_spotlight->colour.g_n = curr_spotlight->colour.g / 255;
		curr_spotlight->colour.b_n = curr_spotlight->colour.b / 255;
		curr_spotlight = curr_spotlight->next;
	}
}
