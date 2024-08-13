/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:49:00 by mateo             #+#    #+#             */
/*   Updated: 2024/08/13 11:48:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	gen_final_colour(t_meta *meta_data)
{
	t_light	*curr;
	// t_colour ambient_colour;
	// t_vector normal;
	// t_vector light_direction;
	// t_vector surface;
	// t_vector temp1;
	// t_colour diffuse;
	// // t_vector center;
	// double	dot_product;

	// // get_ambient(meta_data);
	// ambient_colour.r = meta_data->amlight->colour.r * meta_data->amlight->amlight_ratio * meta_data->pixel.final.r;
	// ambient_colour.g = meta_data->amlight->colour.g * meta_data->amlight->amlight_ratio * meta_data->pixel.final.g;
	// ambient_colour.b = meta_data->amlight->colour.b * meta_data->amlight->amlight_ratio * meta_data->pixel.final.b;
	// vec_multiply_scalar(&temp1, &meta_data->pixel.ray, meta_data->pixel.t);
	// vec_subtract(&surface, &meta_data->camera->coord, &temp1);
	// // vec_subtract(&normal, &surface, &meta_data->sp->coord);
	// normal = calculate_normal(surface, meta_data->sp->coord);

	curr = meta_data->light;
	while (curr)
	{
		// light_direction = calculate_light_direction(surface, curr->coord);
		// dot_product = fmax(0.0, vec_dot_product(&normal, &light_direction));
		// diffuse.r = curr->colour.r * curr->brightness * dot_product * meta_data->pixel.final.r;
		// diffuse.g = curr->colour.g * curr->brightness * dot_product * meta_data->pixel.final.g;
		// diffuse.b = curr->colour.b * curr->brightness * dot_product * meta_data->pixel.final.b;

		// meta_data->pixel.final.r = fmin(ambient_colour.r + diffuse.r, 1.0);
		// meta_data->pixel.final.g = fmin(ambient_colour.g + diffuse.g, 1.0);
		// meta_data->pixel.final.b = fmin(ambient_colour.b + diffuse.b, 1.0);
		// if (in_shadow(meta_data, curr) == false)
		// {
			// get_diffuse(meta_data, curr);
			// get_specular(meta_data, curr);
		// }

		curr = curr->next;
	}
}

t_vector	calculate_light_direction(t_vector surface_point, t_vector light_position)
{
	t_vector light_dir;

	light_dir.x = light_position.x - surface_point.x;
	light_dir.y = light_position.y - surface_point.y;
	light_dir.z = light_position.z - surface_point.z;

	vec_normalise(&light_dir);
	return (light_dir);
}

t_vector	calculate_normal(t_vector surface_point, t_vector center)
{
	t_vector normal;

	normal.x = surface_point.x - center.x;
	normal.y = surface_point.y - center.y;
	normal.z = surface_point.z - center.z;

	vec_normalise(&normal);
	return (normal);
}

/*	get_ambient updates final colour in pixel with ambient light
*/
// WIP: this is a really ugly function D: 
void	get_ambient(t_meta *meta_data)
{
	meta_data->pixel.final.r_n = meta_data->amlight->amlight_ratio * meta_data->amlight->colour.r_n;
	if (meta_data->pixel.surface == SF_SPHERE)
		meta_data->pixel.final.r_n *= ((t_sp *)meta_data->pixel.obj)->colour.r_n;
	else if (meta_data->pixel.surface == SF_PLANE)
		meta_data->pixel.final.r_n *= ((t_pl *)meta_data->pixel.obj)->colour.r_n;
	else if (meta_data->pixel.surface == SF_CY_CURVE || meta_data->pixel.surface == SF_CY_BASE_B || meta_data->pixel.surface == SF_CY_BASE_T)
		meta_data->pixel.final.r_n *= ((t_cy *)meta_data->pixel.obj)->colour.r_n;
	else if (meta_data->pixel.surface == SF_CONE_CURVE || meta_data->pixel.surface == SF_CONE_BASE)
		meta_data->pixel.final.r_n *= ((t_cn *)meta_data->pixel.obj)->colour.r_n;
	
	meta_data->pixel.final.g_n = meta_data->amlight->amlight_ratio * meta_data->amlight->colour.g_n;
	if (meta_data->pixel.surface == SF_SPHERE)
		meta_data->pixel.final.g_n *= ((t_sp *)meta_data->pixel.obj)->colour.g_n;
	else if (meta_data->pixel.surface == SF_PLANE)
		meta_data->pixel.final.g_n *= ((t_pl *)meta_data->pixel.obj)->colour.g_n;
	else if (meta_data->pixel.surface == SF_CY_CURVE || meta_data->pixel.surface == SF_CY_BASE_B || meta_data->pixel.surface == SF_CY_BASE_T)
		meta_data->pixel.final.g_n *= ((t_cy *)meta_data->pixel.obj)->colour.g_n;
	else if (meta_data->pixel.surface == SF_CONE_CURVE || meta_data->pixel.surface == SF_CONE_BASE)
		meta_data->pixel.final.g_n *= ((t_cn *)meta_data->pixel.obj)->colour.g_n;
	
	meta_data->pixel.final.b_n = meta_data->amlight->amlight_ratio * meta_data->amlight->colour.b_n;
	if (meta_data->pixel.surface == SF_SPHERE)
		meta_data->pixel.final.b_n *= ((t_sp *)meta_data->pixel.obj)->colour.b_n;
	else if (meta_data->pixel.surface == SF_PLANE)
		meta_data->pixel.final.b_n *= ((t_pl *)meta_data->pixel.obj)->colour.b_n;
	else if (meta_data->pixel.surface == SF_CY_CURVE || meta_data->pixel.surface == SF_CY_BASE_B || meta_data->pixel.surface == SF_CY_BASE_T)
		meta_data->pixel.final.b_n *= ((t_cy *)meta_data->pixel.obj)->colour.b_n;
	else if (meta_data->pixel.surface == SF_CONE_CURVE || meta_data->pixel.surface == SF_CONE_BASE)
		meta_data->pixel.final.b_n *= ((t_cn *)meta_data->pixel.obj)->colour.b_n;
}

/*	in_shadow checks whether intersection point is in shadow
	- looks for ANY valid intersection with object
	*/
// WIP: incomplete function
// bool	in_shadow(t_meta *meta_data, t_light *light)
// {
// 	t_vector	light;
// 	t_vector	temp;
	
// 	vec_subtract(&light, &light->coord, &meta_data->pixel.intersect);
// 	vec_normalise(&light);
// 	vec_multiply_scalar(&temp, &light, meta_data->pixel.t);
// 	vec_add(&meta_data->pixel.shadow, &meta_data->pixel.intersect, &temp);
// 	if (meta_data->sp)
// 	{
// 		sphere = meta_data->sp;
// 		while (sphere)
// 		{
// 			if (sphere->exclude == 0)
// 				intersect_sp(meta_data, sphere);
// 			sphere = sphere->next;
// 		}
// 	}
// }
