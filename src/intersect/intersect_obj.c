/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:13:16 by mateo             #+#    #+#             */
/*   Updated: 2024/09/05 18:13:25 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

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
