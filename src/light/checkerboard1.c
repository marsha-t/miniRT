/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:47:42 by mateo             #+#    #+#             */
/*   Updated: 2024/09/03 16:47:44 by mateo            ###   ########.fr       */
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
