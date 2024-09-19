/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:34:38 by mateo             #+#    #+#             */
/*   Updated: 2024/09/19 17:42:01 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_vector	get_sp_normal(t_vector surface_point, t_vector center)
{
	t_vector	normal;

	normal.x = surface_point.x - center.x;
	normal.y = surface_point.y - center.y;
	normal.z = surface_point.z - center.z;
	vec_normalise(&normal);
	return (normal);
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
	t_vector	perpen;

	vec_subtract(&temp, &pixel->intersect, &cone->coord);
	vec_multiply_scalar(&parallel, &cone->axis, vec_dot_product(&temp,
			&cone->axis));
	vec_subtract(&perpen, &temp, &parallel);
	vec_multiply_scalar(&temp, &cone->axis, tan(cone->angle_rad)
		* vec_len(&perpen));
	vec_subtract(&normal, &perpen, &temp);
	vec_normalise(&normal);
	return (normal);
}
