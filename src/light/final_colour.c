/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_colour.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:49:00 by mateo             #+#    #+#             */
/*   Updated: 2024/08/08 21:27:29 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	gen_final_colour(t_meta *meta_data)
{
	t_light	*curr;

	get_ambient(meta_data);
	curr = meta_data->light;
	while (curr)
	{
		// if (in_shadow(meta_data, curr) == false)
		// {
			// get_diffuse(meta_data, curr);
			// get_specular(meta_data, curr);
		// }
		curr = curr->next;
	}
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
