/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:49:00 by mateo             #+#    #+#             */
/*   Updated: 2024/08/27 03:48:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	gen_final_colour(t_meta *meta_data)
{
	t_light	*curr;
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
	double  coeff_ref = 0.5;
	double	shine_fac = 20;
	double  p2;

	// printf("amlight: r: %d g: %d b: %d\n", meta_data->amlight->colour.r, meta_data->amlight->colour.g, meta_data->amlight->colour.b);
	ambient_colour.r = meta_data->amlight->colour.r * meta_data->amlight->amlight_ratio * (meta_data->pixel.final.r_n);
	ambient_colour.g = meta_data->amlight->colour.g * meta_data->amlight->amlight_ratio * (meta_data->pixel.final.g_n);
	ambient_colour.b = meta_data->amlight->colour.b * meta_data->amlight->amlight_ratio * (meta_data->pixel.final.b_n);

	// vec_multiply_scalar(&temp1, &meta_data->pixel.ray, meta_data->pixel.t);
	// vec_subtract(&surface, &meta_data->camera->coord, &temp1);
	// vec_subtract(&normal, &surface, &meta_data->sp->coord);

	curr = meta_data->light;
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
			// printf("###########################################\n");
			// printf(RED"ambient_colour: r: %f g: %f b: %f\n"RST, ambient_colour.r/255, ambient_colour.g/255, ambient_colour.b/255);
			// printf(RED"diffuse: r: %f g: %f b: %f\n"RST, diffuse.r, diffuse.g, diffuse.b);
			// printf(RED"t: %f\n"RST, meta_data->pixel.t);
			// printf(RED"obj color_n: r_n: %f g_n: %f b_n: %f\n"RST, meta_data->pixel.final.r_n, meta_data->pixel.final.g_n, meta_data->pixel.final.b_n);
			// printf(RED"light_colour: r: %f g: %f b: %f\n"RST, curr->colour.r/255, curr->colour.g/255, curr->colour.b/255);
			light_direction = calculate_light_direction(meta_data->pixel.intersect, curr->coord);
			// vec_multiply_scalar(&meta_data->pixel.normal, &meta_data->pixel.normal, -1);
			dot_product = fmax(0.0, vec_dot_product(&meta_data->pixel.normal, &light_direction));
			// printf(Y"pixel final r: %f g: %f b %f\n"RST, meta_data->pixel.final.r, meta_data->pixel.final.g, meta_data->pixel.final.b);
			diffuse.r += curr->colour.r * curr->brightness * dot_product * (meta_data->pixel.final.r_n);
			diffuse.g += curr->colour.g * curr->brightness * dot_product * (meta_data->pixel.final.g_n);
			diffuse.b += curr->colour.b * curr->brightness * dot_product * (meta_data->pixel.final.b_n);
			vec_multiply_scalar(&reflection, &meta_data->pixel.normal, 2 * dot_product);
			vec_subtract(&reflection, &light_direction, &reflection);
			dot_product = fmax(0.0, vec_dot_product(&reflection, &meta_data->pixel.ray));
			if (dot_product > 0.0001)
				dot_product = pow(fmax(0.0, dot_product), shine_fac) * coeff_ref;
			p2 = dot_product * curr->brightness;
			specular.r += fmin(curr->colour.r * p2, 255);
			specular.g += fmin(curr->colour.g * p2, 255);
			specular.b += fmin(curr->colour.b * p2, 255);
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
		}
		curr = curr->next;
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
