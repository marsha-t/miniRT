/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:39:17 by mateo             #+#    #+#             */
/*   Updated: 2024/08/28 15:30:21 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	get_checkerboard determines checkerboard colour for given intersection
	- calls on object-specific functions to calculate checkerboard colour 
	*/
void	get_checkerboard(t_meta *meta_data)
{
	if (meta_data->pixel.surface == SF_PLANE)
		get_checkerboard_pl(meta_data, (t_pl *)meta_data->pixel.obj);
	else if (meta_data->pixel.surface == SF_SPHERE)
		get_checkerboard_sp(meta_data, (t_sp *)meta_data->pixel.obj);
	else if (meta_data->pixel.surface == SF_CY_CURVE)
		get_checkerboard_cy_curve(meta_data, (t_cy *)meta_data->pixel.obj);
	else if (meta_data->pixel.surface == SF_CY_BASE_B || meta_data->pixel.surface == SF_CY_BASE_T)
		get_checkerboard_cy_base(meta_data, (t_cy *)meta_data->pixel.obj, meta_data->pixel.surface);
	else if (meta_data->pixel.surface == SF_CONE_CURVE)
		get_checkerboard_cn_curve(meta_data, (t_cn *)meta_data->pixel.obj);
 	else if (meta_data->pixel.surface == SF_CONE_BASE)
		get_checkerboard_cn_base(meta_data, (t_cn *)meta_data->pixel.obj);
}

/*	get_checkerboard_pl determines checkerboard colour 
	for intersection with plane */
void	get_checkerboard_pl(t_meta *meta_data, t_pl *plane)
{
	t_vector	a;
	t_vector	u;
	t_vector	v;
	double	x;
	double	z;

	least_parallel_avector(&a, &plane->normal);
	vec_cross_product(&u, &plane->normal, &a);
	vec_normalise(&u);
	vec_cross_product(&v, &plane->normal, &u);
	vec_normalise(&v);
	vec_subtract(&a, &meta_data->pixel.intersect, &plane->coord);
	x = vec_dot_product(&a, &u);
	z = vec_dot_product(&a, &v);
	x = floor(x / 5);
	z = floor(z / 1);
	assign_checker_colour(x, z, &plane->colour);
}

/*	get_checkerboard_sp determines checkerboard colour 
	for intersection with sphere */
void	get_checkerboard_sp(t_meta *meta_data, t_sp *sphere)
{
	double	theta;
	double	phi;
	t_vector	temp;

	vec_subtract(&temp, &meta_data->pixel.intersect, &sphere->coord);
	phi = atan2(temp.z, temp.x);
	if (phi < 0)
		phi += (2 * M_PI);
	theta = acos(temp.y / sphere->radius);
	theta /= (2 * M_PI);
	phi /= (M_PI);
	theta = theta * 10;
	phi = phi * 10;
	assign_checker_colour(theta, phi, &sphere->colour);
}

/*	get_checkerboard_cy_curve determines checkerboard colour 
	for intersection with cylinder curved surface */
void	get_checkerboard_cy_curve(t_meta *meta_data, t_cy *cylinder)
{
	t_vector	temp1;
	t_vector	temp2;
	double	height;
	double	theta;

	vec_subtract(&temp1, &meta_data->pixel.intersect, &cylinder->coord);
	height = vec_dot_product(&temp1, &cylinder->axis);
	vec_multiply_scalar(&temp2, &cylinder->axis, -height);
	vec_add(&temp2, &temp1, &temp2);
	vec_normalise(&temp2);
	if (temp2.x >= temp2.z && temp2.x >= temp2.y)
		theta = atan2(temp2.z, temp2.y);
	else if (temp2.y >= temp2.z && temp2.y >= temp2.x)
		theta = atan2(temp2.z, temp2.x);
	else
		theta = atan2(temp2.y, temp2.x);
	// theta = atan2(temp2.y, temp2.x);
	if (theta < 0)
		theta += (2 * M_PI);
	theta /= (2*M_PI);
	height = (height + (cylinder->height / 2)) / cylinder->height;
	theta *= 20;
	height *= 10;
	assign_checker_colour(theta, height, &cylinder->colour);
}

/*	get_checkerboard_cy_base determines checkerboard colour 
	for intersection with cylinder base (either one) 
	- math is similar to that for plane */
void	get_checkerboard_cy_base(t_meta *meta_data, t_cy *cylinder, int base)
{
	t_vector	a;
	t_vector	u;
	t_vector	v;
	double	x;
	double	z;

	least_parallel_avector(&a, &cylinder->axis);
	vec_cross_product(&u, &cylinder->axis, &a);
	vec_normalise(&u);
	vec_cross_product(&v, &cylinder->axis, &u);
	vec_normalise(&v);
	if (base == SF_CY_BASE_B)
		vec_subtract(&a, &meta_data->pixel.intersect, &cylinder->base_bottom);
	else if (base == SF_CY_BASE_T)
		vec_subtract(&a, &meta_data->pixel.intersect, &cylinder->base_top);
	x = vec_dot_product(&a, &u);
	z = vec_dot_product(&a, &v);
	// x = floor(x / SQSIZE_FLAT);
	// z = floor(z / SQSIZE_FLAT);
	x = floor(x / 2);
	z = floor(z / 1);
	assign_checker_colour(x, z, &cylinder->colour);
}

/*	get_checkerboard_cn_curve determines checkerboard colour 
	for intersection with cone curved surface */
void	get_checkerboard_cn_curve(t_meta *meta_data, t_cn *cone)
{
	t_vector	temp;
	double	row;
	double	col;
	
	vec_subtract(&temp, &meta_data->pixel.intersect, &cone->coord);
	if (temp.x >= temp.z && temp.x >= temp.y)
		col = atan2(temp.z, temp.y);
	else if (temp.y >= temp.z && temp.y >= temp.x)
		col = atan2(temp.z, temp.x);
	else
		col = atan2(temp.y, temp.x);
	if (col < 0)
		col += 2 * M_PI;
	col /= (2 * M_PI);
	row = vec_dot_product(&temp, &cone->axis);
	row /= cone->height;
	row *= 5;
	col *= 11;
	assign_checker_colour(row, col, &cone->colour);
}

/*	get_checkerboard_cn_base determines checkerboard colour 
	for intersection with cone base
	- math is similar to that for plane */
void	get_checkerboard_cn_base(t_meta *meta_data, t_cn *cone)
{
	t_vector	a;
	t_vector	u;
	t_vector	v;
	double	x;
	double	z;

	least_parallel_avector(&a, &cone->axis);
	vec_cross_product(&u, &cone->axis, &a);
	vec_normalise(&u);
	vec_cross_product(&v, &cone->axis, &u);
	vec_normalise(&v);
	vec_subtract(&a, &meta_data->pixel.intersect, &cone->base);
	x = vec_dot_product(&a, &u);
	z = vec_dot_product(&a, &v);
	x = floor(x / SQSIZE_FLAT);
	z = floor(z / SQSIZE_FLAT);
	assign_checker_colour(x, z, &cone->colour);
}

/*	least_parallel_avector sets up an arbitrary vector (a)
	- it is either (0, 1, 0) or (1, 0, 0) 
		depending on which is less parallel to the normal 
	- parallel-ness is determined by dot product: 
		smaller absolute dot product gives vector that's least parallel to normal*/
void	least_parallel_avector(t_vector *a, t_vector *normal)
{
	double	dot1;
	double	dot2;
	t_vector	temp;
	
	temp.x = 0;
	temp.y = 1;
	temp.z = 0;
	dot1 = vec_dot_product(&temp, normal);
	temp.x = 1;
	temp.y = 0;
	dot2 = vec_dot_product(&temp, normal);
	if (fabs(dot1) <= fabs(dot2))
	{
		a->x = 0;
		a->y = 1;
		a->z = 0;
	}
	else
	{
		a->x = 1;
		a->y = 0;
		a->z = 0;
	}
}

/*	assign_checker_colour determines checkerboard colour based on rol and col given
	- updates t_colour struct directly */
void	assign_checker_colour(int row, int column, t_colour *colour)
{
	if ((row + column) % 2 == 0)
	{
		colour->r_n = 0;
		colour->g_n = 0;
		colour->b_n = 0;
	}
	else
	{
		colour->r_n = 1;
		colour->g_n = 1;
		colour->b_n = 1;
	}
}