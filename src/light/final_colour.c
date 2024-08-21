/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:49:00 by mateo             #+#    #+#             */
/*   Updated: 2024/08/21 04:22:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	gen_final_colour(t_meta *meta_data)
{
	t_light	*curr;
	t_colour ambient_colour;
	t_vector normal;
	t_vector light_direction;
	// int count;
	// t_vector surface;
	// t_vector temp1;
	t_colour diffuse;
	// t_vector center;
	double	dot_product;

	// get_ambient(meta_data);
	// printf("amlight: r: %d g: %d b: %d\n", meta_data->amlight->colour.r, meta_data->amlight->colour.g, meta_data->amlight->colour.b);
	ambient_colour.r = meta_data->amlight->colour.r * meta_data->amlight->amlight_ratio * (meta_data->pixel.final.r_n);
	ambient_colour.g = meta_data->amlight->colour.g * meta_data->amlight->amlight_ratio * (meta_data->pixel.final.g_n);
	ambient_colour.b = meta_data->amlight->colour.b * meta_data->amlight->amlight_ratio * (meta_data->pixel.final.b_n);


	// vec_multiply_scalar(&temp1, &meta_data->pixel.ray, meta_data->pixel.t);
	// vec_subtract(&surface, &meta_data->camera->coord, &temp1);
	// vec_subtract(&normal, &surface, &meta_data->sp->coord);
	if (meta_data->pixel.surface == SF_SPHERE)
	{
		normal = calculate_normal(meta_data->pixel.intersect, meta_data->pixel.coord);
	}
	else if (meta_data->pixel.surface == SF_PLANE)
	{
		normal = meta_data->pixel.normal;
	}
	// normal = calculate_normal(meta_data->pixel.intersect, meta_data->sp->coord);

	curr = meta_data->light;
	diffuse.r = 0;
	diffuse.g = 0;
	diffuse.b = 0;
	// count = 1;
	while (curr)
	{
		// printf("###########################################\n");
		// printf(RED"ambient_colour: r: %f g: %f b: %f\n"RST, ambient_colour.r/255, ambient_colour.g/255, ambient_colour.b/255);
		// printf(RED"diffuse: r: %f g: %f b: %f\n"RST, diffuse.r, diffuse.g, diffuse.b);
		// printf(RED"t: %f\n"RST, meta_data->pixel.t);
		// printf(RED"obj color_n: r_n: %f g_n: %f b_n: %f\n"RST, meta_data->pixel.final.r_n, meta_data->pixel.final.g_n, meta_data->pixel.final.b_n);
		// printf(RED"light_colour: r: %f g: %f b: %f\n"RST, curr->colour.r/255, curr->colour.g/255, curr->colour.b/255);
		light_direction = calculate_light_direction(meta_data->pixel.intersect, curr->coord);
		dot_product = fmax(0.0, vec_dot_product(&normal, &light_direction));
		// printf(Y"pixel final r: %f g: %f b %f\n"RST, meta_data->pixel.final.r, meta_data->pixel.final.g, meta_data->pixel.final.b);
		diffuse.r += curr->colour.r * curr->brightness * dot_product * (meta_data->pixel.final.r_n);
		diffuse.g += curr->colour.g * curr->brightness * dot_product * (meta_data->pixel.final.g_n);
		diffuse.b += curr->colour.b * curr->brightness * dot_product * (meta_data->pixel.final.b_n);
		// print_vector(RED"light dir: "RST, &light_direction);
		// print_vector(RED"normal dir: "RST, &normal);
		// print_vector(RED"intersect dir: "RST, &meta_data->pixel.intersect);
		// print_vector(RED"ray dir: "RST, &meta_data->pixel.ray);
		// printf(RED"dot_product: %f\n"RST, dot_product);
		// printf(RED"diffuse: r: %f g: %f b: %f\n"RST, diffuse.r, diffuse.g, diffuse.b);
		// print_vector(RED"ray dir_n: "RST, &meta_data->pixel.ray_n);
		// if (meta_data->pixel.surface == SF_SPHERE || meta_data->pixel.surface == SF_PLANE)
		// 	printf(Y"%d f r: %f f g: %f f b %f\n"RST, count, meta_data->pixel.final.r, meta_data->pixel.final.g, meta_data->pixel.final.b);
		// printf("###########################################\n");
		// count++;
		curr = curr->next;
	}
	meta_data->pixel.final.r = fmin((ambient_colour.r + diffuse.r), 255);
	meta_data->pixel.final.g = fmin((ambient_colour.g + diffuse.g), 255);
	meta_data->pixel.final.b = fmin((ambient_colour.b + diffuse.b), 255);
	// count = 1;
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
