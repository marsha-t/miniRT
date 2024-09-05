/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_map1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:17:13 by mateo             #+#    #+#             */
/*   Updated: 2024/09/03 16:43:05 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
	uv_map_pl does uv mapping (maps 3D to 2D coordinates in UV space)
	for plane
*/
void	uv_map_pl(t_pixel *pixel, t_pl *plane, double *u, double *v)
{
	t_vector	a;
	t_vector	t;
	t_vector	b;

	least_parallel_avector(&a, &plane->normal);
	vec_cross_product(&t, &plane->normal, &a);
	vec_normalise(&t);
	vec_cross_product(&b, &plane->normal, &t);
	vec_normalise(&b);
	vec_subtract(&a, &pixel->intersect, &plane->coord);
	*u = vec_dot_product(&a, &t);
	*v = vec_dot_product(&a, &b);
}

/*
	uv_map_sp does uv mapping (maps 3D to 2D coordinates in UV space)
	for sphere 
*/
void	uv_map_sp(t_pixel *pixel, t_sp *sphere, double *u, double *v)
{
	t_vector	temp;

	vec_subtract(&temp, &pixel->intersect, &sphere->coord);
	*v = atan2(temp.z, temp.x);
	if (*v < 0)
		*v += (2 * M_PI);
	*u = acos(temp.y / sphere->radius);
	*u /= (2 * M_PI);
	*v /= (M_PI);
}

/*
	uv_map_cy_curve does uv mapping (maps 3D to 2D coordinates in UV space)
	for cylinder curved surface
*/
void	uv_map_cy_curve(t_pixel *pixel, t_cy *cylinder, double *u, double *v)
{
	t_vector	temp1;
	t_vector	temp2;

	vec_subtract(&temp1, &pixel->intersect, &cylinder->coord);
	*v = vec_dot_product(&temp1, &cylinder->axis);
	vec_multiply_scalar(&temp2, &cylinder->axis, -(*v));
	vec_add(&temp2, &temp1, &temp2);
	vec_normalise(&temp2);
	if (temp2.x >= temp2.z && temp2.x >= temp2.y)
		*u = atan2(temp2.z, temp2.y);
	else if (temp2.y >= temp2.z && temp2.y >= temp2.x)
		*u = atan2(temp2.z, temp2.x);
	else
		*u = atan2(temp2.y, temp2.x);
	if (*u < 0)
		*u += (2 * M_PI);
	*u /= (2 * M_PI);
	*v = (*v + (cylinder->height / 2)) / cylinder->height;
}

/*
	uv_map_cy_base does uv mapping (maps 3D to 2D coordinates in UV space)
	for cylinder base
*/
void	uv_map_cy_base(t_pixel *pixel, t_cy *cylinder, double *u, double *v)
{
	t_vector	a;
	t_vector	t;
	t_vector	b;

	least_parallel_avector(&a, &cylinder->axis);
	vec_cross_product(&t, &cylinder->axis, &a);
	vec_normalise(&t);
	vec_cross_product(&b, &cylinder->axis, &t);
	vec_normalise(&b);
	if (pixel->surface == SF_CY_BASE_B)
		vec_subtract(&a, &pixel->intersect, &cylinder->base_bottom);
	else if (pixel->surface == SF_CY_BASE_T)
		vec_subtract(&a, &pixel->intersect, &cylinder->base_top);
	*u = vec_dot_product(&a, &t);
	*v = vec_dot_product(&a, &b);
}
