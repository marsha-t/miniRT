/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 07:58:38 by mateo             #+#    #+#             */
/*   Updated: 2024/08/21 04:07:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	prepare_data adds derived data on image, light and objects
*/
void	prepare_data(t_meta *meta_data)
{
	meta_data->aspect_ratio = (double)(WINDOW_WIDTH) / (double)(WINDOW_HEIGHT);
	printf("ASPECT RATIO %f\n", meta_data->aspect_ratio);
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
	// vec_subtract(&meta_data->img_center, &meta_data->camera->coord,
	// 		&meta_data->camera->orient);
}

/*	img_basis_vec calculates the right and up vectors for image plane
	- world_up is (0, 1, 0)
		unless camera looks along y-axis (then it is (0, 0, 1))
	*/
void	img_basis_vec(t_meta *meta_data)
{
	t_vector	world_up;

	world_up.x = 0;
	world_up.y = 1;
	world_up.z = 0;
	if (vec_cmp_num(&meta_data->camera->orient, 0, 1, 0)
		|| vec_cmp_num(&meta_data->camera->orient, 0, -1, 0))
	{
		world_up.x = 0;
		world_up.y = 0;
		world_up.z = 1;
	}
	vec_cross_product(&meta_data->img_right, &world_up, &meta_data->camera->orient);
	vec_normalise(&meta_data->img_right);
	vec_cross_product(&meta_data->img_up, &meta_data->camera->orient, &meta_data->img_right);
	vec_normalise(&meta_data->img_up);
}

/*	prepare_light adds derived parameters to light structs */
void	prepare_light(t_meta *meta_data)
{
	t_light	*curr;

	meta_data->amlight->colour.r_n = meta_data->amlight->colour.r / 255;
	meta_data->amlight->colour.g_n = meta_data->amlight->colour.g / 255;
	meta_data->amlight->colour.b_n = meta_data->amlight->colour.b / 255;
	curr = meta_data->light;
	while (curr)
	{
		curr->colour.r_n = curr->colour.r / 255;
		curr->colour.g_n = curr->colour.g / 255;
		curr->colour.b_n = curr->colour.b / 255;
		curr = curr->next;
	}
}

/*	prepare_obj adds derived parameters to object structs*/
void	prepare_obj(t_meta *meta_data)
{
	if (meta_data->sp)
		prepare_sp(meta_data->sp);
	if (meta_data->pl)
		prepare_pl(meta_data->pl);
	if (meta_data->cy)
		prepare_cy(meta_data->cy);
	if (meta_data->cn)
		prepare_cn(meta_data->cn);
}

/*	prepare_sp adds derived parameters to sphere nodes
	- normalise colour
	- add radius */
void	prepare_sp(t_sp *start)
{
	t_sp	*curr;

	curr = start;
	while (curr)
	{
		curr->radius = curr->diameter / 2;
		curr->colour.r_n = curr->colour.r / 255;
		curr->colour.g_n = curr->colour.g / 255;
		curr->colour.b_n = curr->colour.b / 255;
		curr = curr->next;
	}
}
/*	prepare_pl adds derived parameters to plane nodes
	- normalise colours */
void	prepare_pl(t_pl *start)
{
	t_pl	*curr;

	curr = start;
	while (curr)
	{
		curr->colour.r_n = curr->colour.r / 255;
		curr->colour.g_n = curr->colour.g / 255;
		curr->colour.b_n = curr->colour.b / 255;
		curr = curr->next;
	}
}
/*	prepare_cy adds derived parameters to cylinder nodes
	- normalise colours
	- centers of bottom and top base of cylinder
	- radius
	*/
void	prepare_cy(t_cy *start)
{
	t_cy		*curr;
	t_vector	temp;

	curr = start;
	while (curr)
	{
		vec_multiply_scalar(&temp, &curr->axis, curr->height / 2);
		vec_subtract(&curr->base_bottom, &curr->coord, &temp);
		vec_add(&curr->base_top, &curr->coord, &temp);
		curr->colour.r_n = curr->colour.r / 255;
		curr->colour.g_n = curr->colour.g / 255;
		curr->colour.b_n = curr->colour.b / 255;
		curr->radius = curr->diameter / 2;
		curr = curr->next;
	}
}
/*	prepare_cn adds derived parameters to cone nodes
	- normalise colours
	- radius of base
	- base center
	*/
void	prepare_cn(t_cn *start)
{
	t_cn		*curr;
	t_vector	temp;

	curr = start;
	while (curr)
	{
		curr->radius = curr->height * tan(curr->angle);
		vec_multiply_scalar(&temp, &curr->axis, curr->height);
		vec_add(&curr->base, &curr->coord, &temp);
		curr->colour.r_n = curr->colour.r / 255;
		curr->colour.g_n = curr->colour.g / 255;
		curr->colour.b_n = curr->colour.b / 255;
		curr = curr->next;
	}
}
