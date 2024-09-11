/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_map2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:43:06 by mateo             #+#    #+#             */
/*   Updated: 2024/09/03 16:43:12 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
	uv_map_cn_curve does uv mapping (maps 3D to 2D coordinates in UV space)
	for cone curved surface
*/
void	uv_map_cn_curve(t_pixel *pixel, t_cn *cone, double *u, double *v)
{
	t_vector	temp;

	vec_subtract(&temp, &pixel->intersect, &cone->coord);
	if (temp.x >= temp.z && temp.x >= temp.y)
		*v = atan2(temp.z, temp.y);
	else if (temp.y >= temp.z && temp.y >= temp.x)
		*v = atan2(temp.z, temp.x);
	else
		*v = atan2(temp.y, temp.x);
	if (*v < 0)
		*v += 2 * M_PI;
	*v /= (2 * M_PI);
	*u = vec_dot_product(&temp, &cone->axis);
	*u /= cone->height;
}

/*
	uv_map_cn_base does uv mapping (maps 3D to 2D coordinates in UV space)
	for cone base
*/
void	uv_map_cn_base(t_pixel *pixel, t_cn *cone, double *u, double *v)
{
	t_vector	a;
	t_vector	t;
	t_vector	b;

	least_parallel_avector(&a, &cone->axis);
	vec_cross_product(&t, &cone->axis, &a);
	vec_normalise(&t);
	vec_cross_product(&b, &cone->axis, &t);
	vec_normalise(&b);
	vec_subtract(&a, &pixel->intersect, &cone->base);
	*u = vec_dot_product(&a, &t);
	*v = vec_dot_product(&a, &b);
}
