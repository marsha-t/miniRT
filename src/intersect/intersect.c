/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:07:21 by mateo             #+#    #+#             */
/*   Updated: 2024/09/05 18:14:11 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	intersect_closest iterates through all objects
	- intersect_<shape> will update pixel data on
		value of t for closest intersection
	- compute closest intersection
*/
void	intersect_closest(t_meta *meta_data)
{
	intersect_closest_sp_pl(meta_data);
	intersect_closest_cy_cn(meta_data);
	get_ray_pt(&meta_data->pixel.intersect, &meta_data->pixel.ray,
		&meta_data->camera->coord, meta_data->pixel.t);
}

void	intersect_closest_sp_pl(t_meta *meta_data)
{
	t_sp	*sphere;
	t_pl	*plane;

	if (meta_data->sp_allocated && meta_data->sp)
	{
		sphere = meta_data->sp;
		while (sphere)
		{
			intersect_sp(meta_data, sphere, &meta_data->pixel.ray);
			sphere = sphere->next;
		}
	}
	if (meta_data->pl_allocated && meta_data->pl)
	{
		plane = meta_data->pl;
		while (plane)
		{
			intersect_pl(meta_data, plane, &meta_data->pixel.ray);
			plane = plane->next;
		}
	}
}

void	intersect_closest_cy_cn(t_meta *meta_data)
{
	t_cy	*cylinder;
	t_cn	*cone;

	if (meta_data->cy_allocated && meta_data->cy)
	{
		cylinder = meta_data->cy;
		while (cylinder)
		{
			intersect_cy(meta_data, cylinder, &meta_data->pixel.ray);
			cylinder = cylinder->next;
		}
	}
	if (meta_data->cn_allocated && meta_data->cn)
	{
		cone = meta_data->cn;
		while (cone)
		{
			intersect_cn(meta_data, cone, &meta_data->pixel.ray);
			cone = cone->next;
		}
	}
}
