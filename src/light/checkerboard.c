/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:39:17 by mateo             #+#    #+#             */
/*   Updated: 2024/09/03 11:55:42 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
	get_checkerboard determines checkerboard colour for given intersection
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
	else if (meta_data->pixel.surface == SF_CY_BASE_B
		|| meta_data->pixel.surface == SF_CY_BASE_T)
		get_checkerboard_cy_base(meta_data, (t_cy *)meta_data->pixel.obj);
	else if (meta_data->pixel.surface == SF_CONE_CURVE)
		get_checkerboard_cn_curve(meta_data, (t_cn *)meta_data->pixel.obj);
	else if (meta_data->pixel.surface == SF_CONE_BASE)
		get_checkerboard_cn_base(meta_data, (t_cn *)meta_data->pixel.obj);
}

/*
	get_checkerboard_pl determines checkerboard colour
	for intersection with plane
	- uv map to convert 3d coordinates to 2d coordinates
	- scale 2d coords using size of squares
	- assign colour based on row/col of coord
*/
void	get_checkerboard_pl(t_meta *meta_data, t_pl *plane)
{
	double	x;
	double	z;

	if (plane->checker == 0)
		return ;
	uv_map_pl(&meta_data->pixel, plane, &x, &z);
	x = floor(x / plane->sqsize.row);
	z = floor(z / plane->sqsize.col);
	assign_checker_colour(x, z, &plane->colour);
}

/*
	get_checkerboard_sp determines checkerboard colour
	for intersection with sphere
	- uv map to convert 3d coordinates to 2d coordinates
	- scale 2d coords using no of squares along latitude and longitude
	- assign colour based on row/col of coord
*/
void	get_checkerboard_sp(t_meta *meta_data, t_sp *sphere)
{
	double	theta;
	double	phi;

	if (sphere->checker == 0)
		return ;
	uv_map_sp(&meta_data->pixel, sphere, &theta, &phi);
	theta = theta * sphere->sqsize.row;
	phi = phi * sphere->sqsize.col;
	assign_checker_colour(theta, phi, &sphere->colour);
}

/*
	get_checkerboard_cy_curve determines checkerboard colour
	for intersection with cylinder curved surface
	- uv map to convert 3d coordinates to 2d coordinates
	- scale 2d coords using no of squares along height and circumference
	- assign colour based on row/col of coord
*/
void	get_checkerboard_cy_curve(t_meta *meta_data, t_cy *cylinder)
{
	double	height;
	double	theta;

	if (cylinder->checker == 0)
		return ;
	uv_map_cy_curve(&meta_data->pixel, cylinder, &theta, &height);
	theta *= cylinder->sqsize.row;
	height *= cylinder->sqsize.col;
	assign_checker_colour(theta, height, &cylinder->colour);
}

/*
	get_checkerboard_cy_base determines checkerboard colour
	for intersection with cylinder base (either one)
	- uv map to convert 3d coordinates to 2d coordinates
	- scale 2d coords using size of squares
	- assign colour based on row/col of coord
 */
void	get_checkerboard_cy_base(t_meta *meta_data, t_cy *cylinder)
{
	double	x;
	double	z;

	if (cylinder->checker == 0)
		return ;
	uv_map_cy_base(&meta_data->pixel, cylinder, &x, &z);
	x = floor(x / cylinder->sqsize.row);
	z = floor(z / cylinder->sqsize.col);
	assign_checker_colour(x, z, &cylinder->colour);
}

/*
	get_checkerboard_cn_curve determines checkerboard colour
	for intersection with cone curved surface
	- uv map to convert 3d coordinates to 2d coordinates
	- scale 2d coords using no of squares along height and around axis
	- assign colour based on row/col of coord
*/
void	get_checkerboard_cn_curve(t_meta *meta_data, t_cn *cone)
{
	double	row;
	double	col;

	if (cone->checker == 0)
		return ;
	uv_map_cn_curve(&meta_data->pixel, cone, &row, &col);
	row *= cone->sqsize.row;
	col *= cone->sqsize.col;
	assign_checker_colour(row, col, &cone->colour);
}

/*
	get_checkerboard_cn_base determines checkerboard colour
	for intersection with cone base
	- uv map to convert 3d coordinates to 2d coordinates
	- scale 2d coords using size of squares
	- assign colour based on row/col of coord
 */
void	get_checkerboard_cn_base(t_meta *meta_data, t_cn *cone)
{
	double	x;
	double	z;

	if (cone->checker == 0)
		return ;
	uv_map_cn_base(&meta_data->pixel, cone, &x, &z);
	x = floor(x / cone->sqsize.row);
	z = floor(z / cone->sqsize.col);
	assign_checker_colour(x, z, &cone->colour);
}

/*
	least_parallel_avector sets up an arbitrary vector (a)
	- it is either (0, 1, 0) or (1, 0, 0)
		depending on which is less parallel to the normal
	- parallel-ness is determined by dot product:
		smaller absolute dot product gives vector
		that's least parallel to normal
*/
void	least_parallel_avector(t_vector *a, t_vector *normal)
{
	double		dot1;
	double		dot2;
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

/*
	assign_checker_colour determines checkerboard colour
	based on rol and col given
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
