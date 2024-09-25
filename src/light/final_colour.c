/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:49:00 by mateo             #+#    #+#             */
/*   Updated: 2024/09/25 18:02:15 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	gen_final_colour(t_meta *meta_data)
{
	t_colour	ambient_colour;
	t_colour	diffuse;
	t_colour	specular;

	init_final_colour(meta_data, &diffuse, &specular, &ambient_colour);
	gen_final_colour_light(meta_data, &diffuse, &specular);
	gen_final_colour_spotlight(meta_data, &diffuse, &specular);
	meta_data->pixel.final.r = fmin((ambient_colour.r + diffuse.r + specular.r),
			255);
	meta_data->pixel.final.g = fmin((ambient_colour.g + diffuse.g + specular.g),
			255);
	meta_data->pixel.final.b = fmin((ambient_colour.b + diffuse.b + specular.b),
			255);
}

void	init_final_colour(t_meta *meta_data, t_colour *diffuse,
		t_colour *specular, t_colour *ambient)
{
	if (meta_data->amlight_allocated)
	{
		ambient->r = meta_data->amlight->colour.r
			* meta_data->amlight->amlight_ratio * (meta_data->pixel.final.r_n);
		ambient->g = meta_data->amlight->colour.g
			* meta_data->amlight->amlight_ratio * (meta_data->pixel.final.g_n);
		ambient->b = meta_data->amlight->colour.b
			* meta_data->amlight->amlight_ratio * (meta_data->pixel.final.b_n);
	}
	diffuse->r = 0;
	diffuse->g = 0;
	diffuse->b = 0;
	specular->r = 0;
	specular->g = 0;
	specular->b = 0;
}

void	gen_final_colour_light(t_meta *meta_data, t_colour *diffuse,
		t_colour *specular)
{
	t_light	*curr;

	curr = meta_data->light;
	while (curr)
	{
		if (in_shadow(meta_data, curr) == false)
		{
			gen_diffuse(meta_data, curr, diffuse);
			gen_specular(meta_data, curr, specular);
		}
		curr = curr->next;
	}
}

void	gen_final_colour_spotlight(t_meta *meta_data, t_colour *diffuse,
		t_colour *specular)
{
	t_spotlight	*curr_sl;

	curr_sl = meta_data->spotlight;
	while (curr_sl)
	{
		if (in_shadow_spotlight(meta_data, curr_sl) == false)
		{
			gen_diffuse_spotlight(meta_data, curr_sl, diffuse);
			gen_specular_spotlight(meta_data, curr_sl, specular);
		}
		curr_sl = curr_sl->next;
	}
}

t_vector	calculate_light_direction(t_vector surface_point,
		t_vector light_position)
{
	t_vector	light_dir;

	light_dir.x = light_position.x - surface_point.x;
	light_dir.y = light_position.y - surface_point.y;
	light_dir.z = light_position.z - surface_point.z;
	vec_normalise(&light_dir);
	return (light_dir);
}
