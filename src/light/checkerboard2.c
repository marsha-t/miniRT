/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:44:49 by mateo             #+#    #+#             */
/*   Updated: 2024/09/03 16:45:02 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

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
