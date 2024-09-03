/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:07:21 by mateo             #+#    #+#             */
/*   Updated: 2024/09/03 12:51:38 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	intersect_closest iterates through all objects
	- intersect_<shape> will update pixel data on value of t for closest intersection
	- compute closest intersection
*/
void	intersect_closest(t_meta *meta_data)
{
	t_sp	*sphere;
	t_pl	*plane;
	t_cy	*cylinder;
	t_cn	*cone;

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
	get_ray_pt(&meta_data->pixel.intersect, &meta_data->pixel.ray,
		&meta_data->camera->coord, meta_data->pixel.t);
}

/*	intersect_sp
	- calls on intersect_sp_math to calculate t (of intersection point)
	- if there is a valid intersection, data in pixel (i.e., t,
		obj and surface) is updated
	- no update otherwise
	*/
void	intersect_sp(t_meta *meta_data, t_sp *sphere, t_vector *ray)
{
	double	t;

	t = intersect_sp_math(sphere, ray, &meta_data->camera->coord);
	if (t > 0 && t < meta_data->pixel.t)
	{
		meta_data->pixel.t = t;
		meta_data->pixel.obj = (void *)sphere;
		meta_data->pixel.surface = SF_SPHERE;
	}
}

/*	intersect_pl
	- calls on intersect_pl_math to calculate t (of intersection point)
	- if there is a valid intersection, data in pixel (i.e., t,
		obj and surface) is updated
	- no update otherwise
	*/
void	intersect_pl(t_meta *meta_data, t_pl *plane, t_vector *ray)
{
	double	t;

	t = intersect_pl_math(plane, ray, &meta_data->camera->coord);
	if (t > 0 && t < meta_data->pixel.t)
	{
		meta_data->pixel.t = t;
		meta_data->pixel.obj = (void *)plane;
		meta_data->pixel.surface = SF_PLANE;
	}
}

/*	intersect_cy finds intersection between ray and cylinder
	- calls on intersect_cy_curve_math to check intersection with curved surface
	- calls on intersect_cy_base_math twice to check intersection with both bases
*/
void	intersect_cy(t_meta *meta_data, t_cy *cylinder, t_vector *ray)
{
	double	t;

	t = intersect_cy_curve_math(cylinder, ray, &meta_data->camera->coord);
	if (t > 0 && t < meta_data->pixel.t)
	{
		meta_data->pixel.t = t;
		meta_data->pixel.obj = (void *)cylinder;
		meta_data->pixel.surface = SF_CY_CURVE;
	}
	t = intersect_cy_base_math(cylinder, SF_CY_BASE_B, ray,
			&meta_data->camera->coord);
	if (t > 0 && t < meta_data->pixel.t)
	{
		meta_data->pixel.t = t;
		meta_data->pixel.obj = (void *)cylinder;
		meta_data->pixel.surface = SF_CY_BASE_B;
	}
	t = intersect_cy_base_math(cylinder, SF_CY_BASE_T, ray,
			&meta_data->camera->coord);
	if (t > 0 && t < meta_data->pixel.t)
	{
		meta_data->pixel.t = t;
		meta_data->pixel.obj = (void *)cylinder;
		meta_data->pixel.surface = SF_CY_BASE_T;
	}
}

/*	intersect_cn finds intersection between ray and cone
	- calls on intersect_cn_curve_math to check intersection with curved surface
	- calls on intersect_cn_base_math to check intersection with base */
void	intersect_cn(t_meta *meta_data, t_cn *cone, t_vector *ray)
{
	double	t;

	t = intersect_cn_curve_math(cone, ray, &meta_data->camera->coord);
	if (t > 0 && t < meta_data->pixel.t)
	{
		meta_data->pixel.t = t;
		meta_data->pixel.obj = (void *)cone;
		meta_data->pixel.surface = SF_CONE_CURVE;
	}
	t = intersect_cn_base_math(cone, ray, &meta_data->camera->coord);
	if (t > 0 && t < meta_data->pixel.t)
	{
		meta_data->pixel.t = t;
		meta_data->pixel.obj = (void *)cone;
		meta_data->pixel.surface = SF_CONE_BASE;
	}
}
