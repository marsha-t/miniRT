/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_math2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:07:32 by mateo             #+#    #+#             */
/*   Updated: 2024/09/05 18:07:46 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	intersect_cn_curve_math checks intersection with curved surface of cylinder
	- returns -1 if there are no intersections or t <= 0
	- returns -1 if pt doesnt lie within cone height
	- returns t otherwise  */
double	intersect_cn_curve_math(t_cn *cone, t_vector *ray, t_vector *origin)
{
	double		abc[3];
	t_vector	temp;
	t_vector	ray_pt;
	double		projection;
	double		t;

	abc[0] = vec_dot_product(ray, &cone->axis) * vec_dot_product(ray,
			&cone->axis) - cos(cone->angle) * cos(cone->angle);
	vec_subtract(&temp, origin, &cone->coord);
	abc[1] = 2 * (vec_dot_product(&temp, &cone->axis) * vec_dot_product(ray,
				&cone->axis) - (cos(cone->angle) * cos(cone->angle)
				* vec_dot_product(&temp, ray)));
	abc[2] = vec_dot_product(&temp, &cone->axis) * vec_dot_product(&temp,
			&cone->axis) - (cos(cone->angle) * cos(cone->angle)
			* vec_dot_product(&temp, &temp));
	t = quadratic_formula(abc[0], abc[1], abc[2]);
	if (t > 0)
	{
		get_ray_pt(&ray_pt, ray, origin, t);
		vec_subtract(&temp, &ray_pt, &cone->coord);
		projection = vec_dot_product(&temp, &cone->axis);
		if (projection < 0 || projection > cone->height)
			return (-1);
	}
	return (t);
}

/*	intersect_cn_base_math checks intersection with base of cone
	- returns -1 if there are no intersections or t <= 0
	- returns -1 if intersection is outside radius of cylinder
	- returns t otherwise  */
double	intersect_cn_base_math(t_cn *cone, t_vector *ray, t_vector *origin)
{
	t_vector	temp;
	double		denom;
	double		t;
	t_vector	ray_pt;

	denom = vec_dot_product(ray, &cone->axis);
	if (denom == 0)
		return (-1);
	vec_subtract(&temp, &cone->base, origin);
	t = vec_dot_product(&temp, &cone->axis) / denom;
	if (t <= 0)
		return (-1);
	get_ray_pt(&ray_pt, ray, origin, t);
	vec_subtract(&temp, &ray_pt, &cone->base);
	if (vec_len(&temp) > cone->radius)
		return (-1);
	return (t);
}
