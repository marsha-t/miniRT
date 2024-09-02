/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_prepare.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:54:46 by mateo             #+#    #+#             */
/*   Updated: 2024/09/02 11:33:21 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	prepare_intersect adds derived parameters about the intersection point
	- parameters: colours, coord, normal */
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

/*	prepare_intersect_sp adds derived parameters about intersection point with a sphere */
void	prepare_intersect_sp(t_pixel *pixel)
{
	t_sp	*sphere;

	sphere = (t_sp *)pixel->obj;
	pixel->final.r_n = sphere->colour.r_n;
	pixel->final.g_n = sphere->colour.g_n;
	pixel->final.b_n = sphere->colour.b_n;
	pixel->coord = sphere->coord;
	pixel->normal = get_sp_normal(pixel->intersect, pixel->coord);
	// print_vector("ori_normal:", &pixel->normal);
	if (sphere->bump == 1)
	{
		pixel->normal = get_sp_bm_normal(pixel, sphere);
	}
	// print_vector("new_normal:", &pixel->normal);
}

t_vector	get_sp_normal(t_vector surface_point, t_vector center)
{
	t_vector normal;

	normal.x = surface_point.x - center.x;
	normal.y = surface_point.y - center.y;
	normal.z = surface_point.z - center.z;

	vec_normalise(&normal);
	return (normal);
}

/*	prepare_intersect_pl adds derived parameters about intersection point with a plane */
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
	{
		vec_inv(&pixel->normal, &plane->normal);
	}
}

/*	prepare_intersect_cy adds derived parameters about intersection point with a cylinder */
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
		// print_vector("ori_normal:", &pixel->normal);
		if (cylinder->bump == 1)
			pixel->normal = get_cy_base_bm_normal(pixel, cylinder);
		// print_vector("new_normal:", &pixel->normal);

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

/*	
	get_cy_curve_normal calculates normal vector for intersection
	on cylinder's curved surface 
*/
t_vector	get_cy_curve_normal(t_pixel *pixel, t_cy *cylinder)
{
	t_vector	temp1;
	t_vector	temp2;

	vec_subtract(&temp1, &pixel->intersect, &cylinder->coord);
	vec_multiply_scalar(&temp2, &cylinder->axis, vec_dot_product(&temp1,
			&cylinder->axis));
	vec_subtract(&temp1, &temp1, &temp2);
	vec_normalise(&temp1);
	return (temp1);
}

/*	
	get_cn_curve_normal calculates normal vector for intersection
	on cone's curved surface 
*/
t_vector	get_cn_curve_normal(t_pixel *pixel, t_cn *cone)
{
	t_vector	temp;
	t_vector	parallel;
	t_vector	normal;

	vec_subtract(&temp, &pixel->intersect, &cone->coord);
	vec_multiply_scalar(&parallel, &cone->axis, vec_dot_product(&temp, &cone->axis));
	t_vector	perpen;
	vec_subtract(&perpen, &temp, &parallel);
	vec_multiply_scalar(&temp, &cone->axis, tan(cone->angle) * vec_len(&perpen));
	vec_subtract(&normal, &perpen, &temp);
	vec_normalise(&normal);
	return (normal);
}