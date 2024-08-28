/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:49:00 by mateo             #+#    #+#             */
/*   Updated: 2024/08/29 03:24:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	gen_final_colour(t_meta *meta_data)
{
	t_light	*curr;
	t_spotlight *curr_sl;
	t_colour ambient_colour;
	t_vector light_direction;
	// int count;
	// t_vector surface;
	// t_vector temp1;
	t_colour diffuse;
	t_colour specular;
	t_vector reflection;
	// t_vector temp;
	// t_vector center;
	double	dot_product;
	double  p2;

	// printf("amlight: r: %d g: %d b: %d\n", meta_data->amlight->colour.r, meta_data->amlight->colour.g, meta_data->amlight->colour.b);
	ambient_colour.r = meta_data->amlight->colour.r * meta_data->amlight->amlight_ratio * (meta_data->pixel.final.r_n);
	ambient_colour.g = meta_data->amlight->colour.g * meta_data->amlight->amlight_ratio * (meta_data->pixel.final.g_n);
	ambient_colour.b = meta_data->amlight->colour.b * meta_data->amlight->amlight_ratio * (meta_data->pixel.final.b_n);

	// vec_multiply_scalar(&temp1, &meta_data->pixel.ray, meta_data->pixel.t);
	// vec_subtract(&surface, &meta_data->camera->coord, &temp1);
	// vec_subtract(&normal, &surface, &meta_data->sp->coord);

	curr = meta_data->light;
	curr_sl = meta_data->spotlight;
	diffuse.r = 0;
	diffuse.g = 0;
	diffuse.b = 0;
	specular.r = 0;
	specular.g = 0;
	specular.b = 0;
	// count = 1;
	while (curr)
	{
		if (in_shadow(meta_data, curr) == false)
		{
			light_direction = calculate_light_direction(meta_data->pixel.intersect, curr->coord);
			dot_product = fmax(0.0, vec_dot_product(&meta_data->pixel.normal, &light_direction));
			diffuse.r += curr->colour.r * curr->brightness * dot_product * (meta_data->pixel.final.r_n);
			diffuse.g += curr->colour.g * curr->brightness * dot_product * (meta_data->pixel.final.g_n);
			diffuse.b += curr->colour.b * curr->brightness * dot_product * (meta_data->pixel.final.b_n);
			vec_multiply_scalar(&reflection, &meta_data->pixel.normal, 2 * dot_product);
			vec_subtract(&reflection, &light_direction, &reflection);
			dot_product = fmax(0.0, vec_dot_product(&reflection, &meta_data->pixel.ray));
			if (dot_product > 0.0001)
				dot_product = pow(fmax(0.0, dot_product), meta_data->pixel.shine_fac) * meta_data->pixel.coeff_ref;
			p2 = dot_product * curr->brightness;
			specular.r += fmin(curr->colour.r * p2, 255);
			specular.g += fmin(curr->colour.g * p2, 255);
			specular.b += fmin(curr->colour.b * p2, 255);
		}
		curr = curr->next;
	}
	while (curr_sl)
	{
		if (in_shadow_spotlight(meta_data, curr_sl) == false)
		{
			// printf("false\n");
			light_direction = calculate_light_direction(meta_data->pixel.intersect, curr_sl->coord);
			dot_product = fmax(0.0, vec_dot_product(&meta_data->pixel.normal, &light_direction));
			diffuse.r += curr_sl->colour.r * meta_data->pixel.spot_intensity * dot_product * (meta_data->pixel.final.r_n);
			diffuse.g += curr_sl->colour.g * meta_data->pixel.spot_intensity * dot_product * (meta_data->pixel.final.g_n);
			diffuse.b += curr_sl->colour.b * meta_data->pixel.spot_intensity * dot_product * (meta_data->pixel.final.b_n);
			vec_multiply_scalar(&reflection, &meta_data->pixel.normal, 2 * dot_product);
			vec_subtract(&reflection, &light_direction, &reflection);
			dot_product = fmax(0.0, vec_dot_product(&reflection, &meta_data->pixel.ray));
			if (dot_product > 0.0001)
				dot_product = pow(fmax(0.0, dot_product), meta_data->pixel.shine_fac) * meta_data->pixel.coeff_ref;
			p2 = dot_product * meta_data->pixel.spot_intensity;
			specular.r += fmin(curr_sl->colour.r * p2, 255);
			specular.g += fmin(curr_sl->colour.g * p2, 255);
			specular.b += fmin(curr_sl->colour.b * p2, 255);
		}
		curr_sl = curr_sl->next;
	}
	meta_data->pixel.final.r = fmin((ambient_colour.r + diffuse.r + specular.r), 255);
	meta_data->pixel.final.g = fmin((ambient_colour.g + diffuse.g + specular.g), 255);
	meta_data->pixel.final.b = fmin((ambient_colour.b + diffuse.b + specular.b), 255);
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
