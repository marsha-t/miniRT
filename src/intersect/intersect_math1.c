/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_math1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:24:23 by mateo             #+#    #+#             */
/*   Updated: 2024/09/30 12:35:16 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
	intersect_sp_math finds the intersection between ray and a given sphere
	- returns -1 if there are no intersections or t <= 0
	- returns t otherwise
*/
double	intersect_sp_math(t_sp *sphere, t_vector *ray, t_vector *origin)
{
	double		a;
	double		b;
	double		c;
	t_vector	temp;

	a = vec_dot_product(ray, ray);
	vec_subtract(&temp, origin, &sphere->coord);
	b = vec_dot_product(ray, &temp) * 2;
	c = vec_dot_product(&temp, &temp) - (sphere->radius) * (sphere->radius);
	return (quadratic_formula(a, b, c));
}

/*
	intersect_pl_math finds the intersection between ray and a given plane
	- returns -1 if there are no intersections or t <= 0
	- returns t otherwise
*/
double	intersect_pl_math(t_pl *plane, t_vector *ray, t_vector *origin)
{
	double		t;
	double		denom;
	t_vector	temp;

	denom = vec_dot_product(&plane->normal, ray);
	if (denom == 0)
		return (-1);
	vec_subtract(&temp, origin, &plane->coord);
	t = -1 * (vec_dot_product(&plane->normal, &temp) / denom);
	if (t <= 0)
		return (-1);
	return (t);
}

/*	
	intersect_cy_curve_math checks intersection with curved surface of cylinder
	- returns -1 if there are no intersections or t <= 0
	- returns -1 if pt doesnt lie within cylinder height
	- returns t otherwise  
*/
double	intersect_cy_curve_math(t_cy *cylinder, t_vector *ray, t_vector *origin)
{
	double		abc[3];
	t_vector	temp[2];
	t_vector	d_perpen;
	t_vector	w_perpen;
	double		t;

	vec_multiply_scalar(&temp[0], &cylinder->axis, vec_dot_product(ray,
			&cylinder->axis));
	vec_subtract(&d_perpen, ray, &temp[0]);
	vec_subtract(&temp[1], origin, &cylinder->coord);
	vec_multiply_scalar(&temp[0], &cylinder->axis, vec_dot_product(&temp[1],
			&cylinder->axis));
	vec_subtract(&w_perpen, &temp[1], &temp[0]);
	abc[0] = vec_dot_product(&d_perpen, &d_perpen);
	abc[1] = vec_dot_product(&w_perpen, &d_perpen) * 2;
	abc[2] = vec_dot_product(&w_perpen, &w_perpen) - (cylinder->radius
			* cylinder->radius);
	t = quadratic_formula(abc[0], abc[1], abc[2]);
	return (cy_curve_check(cylinder, t, ray, origin));
}

double	cy_curve_check(t_cy *cy, double t, t_vector *ray, t_vector *origin)
{
	t_vector	ray_pt;
	double		projection;
	t_vector	temp;

	if (t > 0)
	{
		get_ray_pt(&ray_pt, ray, origin, t);
		vec_subtract(&temp, &ray_pt, &cy->coord);
		projection = vec_dot_product(&temp, &cy->axis);
		if (projection < -cy->height / 2 || projection > cy->height
			/ 2)
			return (-1);
	}
	return (t);
}

/*	intersect_cy_base_math checks intersection with EITHER bases of cylinder
	- returns -1 if there are no intersections or t <= 0
	- returns -1 if intersection is outside radius of cylinder
	- returns t otherwise  */
double	intersect_cy_base_math(t_cy *cylinder, int base, t_vector *ray,
		t_vector *origin)
{
	t_vector	temp;
	double		denom;
	double		t;
	double		len;
	t_vector	ray_pt;

	denom = vec_dot_product(&cylinder->axis, ray);
	if (denom == 0)
		return (-1);
	if (base == SF_CY_BASE_B)
		vec_subtract(&temp, &cylinder->base_bottom, origin);
	else if (base == SF_CY_BASE_T)
		vec_subtract(&temp, &cylinder->base_top, origin);
	t = vec_dot_product(&cylinder->axis, &temp) / denom;
	if (t <= 0)
		return (-1);
	get_ray_pt(&ray_pt, ray, origin, t);
	if (base == SF_CY_BASE_B)
		vec_subtract(&temp, &cylinder->base_bottom, &ray_pt);
	else if (base == SF_CY_BASE_T)
		vec_subtract(&temp, &cylinder->base_top, &ray_pt);
	len = vec_len(&temp);
	if (len > cylinder->radius)
		return (-1);
	return (t);
}
