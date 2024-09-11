/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_prepare.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:54:46 by mateo             #+#    #+#             */
/*   Updated: 2024/09/05 17:36:23 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	
	prepare_intersect adds derived parameters about the intersection point
	- parameters: colours, coord, normal 
*/
void	prepare_intersect(t_pixel *pixel)
{
	if (pixel->surface == SF_SPHERE)
		prepare_intersect_sp(pixel);
	else if (pixel->surface == SF_PLANE)
		prepare_intersect_pl(pixel);
	else if (pixel->surface == SF_CY_CURVE || pixel->surface == SF_CY_BASE_B
		|| pixel->surface == SF_CY_CURVE)
		prepare_intersect_cy(pixel);
	else if (pixel->surface == SF_CONE_CURVE || pixel->surface == SF_CONE_BASE)
		prepare_intersect_cn(pixel);
}

/*	
	prepare_intersect_sp adds derived parameters 
	about intersection point with a sphere 
*/
void	prepare_intersect_sp(t_pixel *pixel)
{
	t_sp	*sphere;

	sphere = (t_sp *)pixel->obj;
	pixel->final.r_n = sphere->colour.r_n;
	pixel->final.g_n = sphere->colour.g_n;
	pixel->final.b_n = sphere->colour.b_n;
	pixel->coord = sphere->coord;
	pixel->normal = get_sp_normal(pixel->intersect, pixel->coord);
	if (sphere->bump == 1)
		pixel->normal = get_sp_bm_normal(pixel, sphere);
}

/*	
	prepare_intersect_pl adds derived parameters 
	about intersection point with a plane 
*/
void	prepare_intersect_pl(t_pixel *pixel)
{
	t_pl	*plane;

	plane = (t_pl *)pixel->obj;
	pixel->final.r_n = plane->colour.r_n;
	pixel->final.g_n = plane->colour.g_n;
	pixel->final.b_n = plane->colour.b_n;
	pixel->coord = plane->coord;
	pixel->normal = plane->normal;
	if (vec_dot_product(&plane->normal, &pixel->ray) > 0)
		vec_inv(&pixel->normal, &plane->normal);
	if (plane->bump == 1)
		pixel->normal = get_pl_bm_normal(pixel, plane);
}

/*	
	prepare_intersect_cy adds derived parameters 
	about intersection point with a cylinder 
*/
void	prepare_intersect_cy(t_pixel *pixel)
{
	t_cy	*cylinder;

	cylinder = (t_cy *)pixel->obj;
	pixel->final.r_n = cylinder->colour.r_n;
	pixel->final.g_n = cylinder->colour.g_n;
	pixel->final.b_n = cylinder->colour.b_n;
	if (pixel->surface == SF_CY_CURVE)
	{
		pixel->normal = get_cy_curve_normal(pixel, (t_cy *)pixel->obj);
		if (cylinder->bump == 1)
			pixel->normal = get_cy_curve_bm_normal(pixel, cylinder);
	}
	else if (pixel->surface == SF_CY_BASE_B)
	{
		vec_inv(&pixel->normal, &cylinder->axis);
		if (cylinder->bump == 1)
			pixel->normal = get_cy_base_bm_normal(pixel, cylinder);
	}
	else if (pixel->surface == SF_CY_BASE_T)
	{
		pixel->normal = cylinder->axis;
		if (cylinder->bump == 1)
			pixel->normal = get_cy_base_bm_normal(pixel, cylinder);
	}
}

/*
	prepare_intersect_cn adds derived parameters about intersection point
	with a cone
*/
void	prepare_intersect_cn(t_pixel *pixel)
{
	t_cn	*cone;

	cone = (t_cn *)pixel->obj;
	pixel->final.r_n = cone->colour.r_n;
	pixel->final.g_n = cone->colour.g_n;
	pixel->final.b_n = cone->colour.b_n;
	if (pixel->surface == SF_CONE_CURVE)
		pixel->normal = get_cn_curve_normal(pixel, (t_cn *)pixel->obj);
	if (pixel->surface == SF_CONE_BASE)
		vec_inv(&pixel->normal, &cone->axis);
}
