/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_specular.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:45:01 by mateo             #+#    #+#             */
/*   Updated: 2024/09/05 17:22:25 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	gen_diffuse(t_meta *meta_data, t_light *curr, t_colour *diffuse)
{
	t_vector	light_direction;
	double		dot_product;

	light_direction = calculate_light_direction(meta_data->pixel.intersect,
			curr->coord);
	dot_product = fmax(0.0, vec_dot_product(&meta_data->pixel.normal,
				&light_direction));
	diffuse->r += curr->colour.r * curr->brightness * dot_product
		* (meta_data->pixel.final.r_n);
	diffuse->g += curr->colour.g * curr->brightness * dot_product
		* (meta_data->pixel.final.g_n);
	diffuse->b += curr->colour.b * curr->brightness * dot_product
		* (meta_data->pixel.final.b_n);
}

void	gen_specular(t_meta *meta_data, t_light *curr, t_colour *specular)
{
	t_vector	light_direction;
	double		dot_product;
	t_vector	reflection;
	double		p2;

	light_direction = calculate_light_direction(meta_data->pixel.intersect,
			curr->coord);
	dot_product = fmax(0.0, vec_dot_product(&meta_data->pixel.normal,
				&light_direction));
	vec_multiply_scalar(&reflection, &meta_data->pixel.normal, 2 * dot_product);
	vec_subtract(&reflection, &light_direction, &reflection);
	dot_product = fmax(0.0, vec_dot_product(&reflection,
				&meta_data->pixel.ray));
	if (dot_product > 0.0001)
		dot_product = pow(fmax(0.0, dot_product), meta_data->pixel.shine_fac)
			* meta_data->pixel.coeff_ref;
	p2 = dot_product * curr->brightness;
	specular->r += fmin(curr->colour.r * p2, 255);
	specular->g += fmin(curr->colour.g * p2, 255);
	specular->b += fmin(curr->colour.b * p2, 255);
}

void	gen_diffuse_spotlight(t_meta *meta_data, t_spotlight *curr_sl,
		t_colour *diffuse)
{
	t_vector	light_direction;
	double		dot_product;

	light_direction = calculate_light_direction(meta_data->pixel.intersect,
			curr_sl->coord);
	dot_product = fmax(0.0, vec_dot_product(&meta_data->pixel.normal,
				&light_direction));
	diffuse->r += curr_sl->colour.r * meta_data->pixel.spot_intensity
		* dot_product * (meta_data->pixel.final.r_n);
	diffuse->g += curr_sl->colour.g * meta_data->pixel.spot_intensity
		* dot_product * (meta_data->pixel.final.g_n);
	diffuse->b += curr_sl->colour.b * meta_data->pixel.spot_intensity
		* dot_product * (meta_data->pixel.final.b_n);
}

void	gen_specular_spotlight(t_meta *meta_data, t_spotlight *curr_sl,
		t_colour *specular)
{
	t_vector	light_direction;
	double		dot_product;
	t_vector	reflection;
	double		p2;

	light_direction = calculate_light_direction(meta_data->pixel.intersect,
			curr_sl->coord);
	dot_product = fmax(0.0, vec_dot_product(&meta_data->pixel.normal,
				&light_direction));
	vec_multiply_scalar(&reflection, &meta_data->pixel.normal, 2 * dot_product);
	vec_subtract(&reflection, &light_direction, &reflection);
	dot_product = fmax(0.0, vec_dot_product(&reflection,
				&meta_data->pixel.ray));
	if (dot_product > 0.0001)
		dot_product = pow(fmax(0.0, dot_product), meta_data->pixel.shine_fac)
			* meta_data->pixel.coeff_ref;
	p2 = dot_product * meta_data->pixel.spot_intensity;
	specular->r += fmin(curr_sl->colour.r * p2, 255);
	specular->g += fmin(curr_sl->colour.g * p2, 255);
	specular->b += fmin(curr_sl->colour.b * p2, 255);
}
