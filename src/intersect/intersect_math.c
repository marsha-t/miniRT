/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_math.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:24:23 by mateo             #+#    #+#             */
/*   Updated: 2024/09/02 17:40:58 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	intersect_sp_math finds the intersection between ray and a given sphere
	- returns -1 if there are no intersections or t <= 0
	- returns t otherwise  */
// double	intersect_sp_math(t_sp *sphere, t_vector *ray, t_vector *origin)
double	intersect_sp_math(t_sp *sphere, t_vector *ray, t_vector *origin, int x, int y)
{
	double		a;
	double		b;
	double		c;
	t_vector	temp;

	a = vec_dot_product(ray, ray);
	vec_subtract(&temp, origin, &sphere->coord);
	b = vec_dot_product(ray, &temp) * 2;
	c = vec_dot_product(&temp, &temp) - (sphere->radius) * (sphere->radius);
	if (x == 640 && y == 360)
	{
		printf("%d, %d: \n", x, y);
		print_vector("ray: ", ray);
		printf("a: %f\n", a);
		printf("b: %f\n", b);
		printf("c: %f\n", c);
	}
	return (quadratic_formula(a, b, c));
}

// /*	intersect_pl_math finds the intersection between ray and a given plane
// 	- returns -1 if there are no intersections or t <= 0
// 	- returns t otherwise  */
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

/*	intersect_cy_curve_math checks intersection with curved surface of cylinder
	- returns -1 if there are no intersections or t <= 0
	- returns -1 if pt doesnt lie within cylinder height
	- returns t otherwise  */
double	intersect_cy_curve_math(t_cy *cylinder, t_vector *ray, t_vector *origin)
{
	double		a;
	double		b;
	double		c;
	t_vector	temp;
	t_vector	d_perpen;
	t_vector	w;
	t_vector	w_perpen;
	double		t;
	t_vector	ray_pt;
	double		projection;

	vec_multiply_scalar(&temp, &cylinder->axis, vec_dot_product(ray,
			&cylinder->axis));
	vec_subtract(&d_perpen, ray, &temp);
	vec_subtract(&w, origin, &cylinder->coord);
	vec_multiply_scalar(&temp, &cylinder->axis, vec_dot_product(&w,
			&cylinder->axis));
	vec_subtract(&w_perpen, &w, &temp);
	a = vec_dot_product(&d_perpen, &d_perpen);
	b = vec_dot_product(&w_perpen, &d_perpen) * 2;
	c = vec_dot_product(&w_perpen, &w_perpen) - (cylinder->radius
		* cylinder->radius);
	t = quadratic_formula(a, b, c);
	if (t > 0)
	{
		get_ray_pt(&ray_pt, ray, origin, t);
		vec_subtract(&temp, &ray_pt, &cylinder->coord);
		projection = vec_dot_product(&temp, &cylinder->axis);
		if (projection < -cylinder->height / 2 || projection > cylinder->height
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

/*	intersect_cn_curve_math checks intersection with curved surface of cylinder
	- returns -1 if there are no intersections or t <= 0
	- returns -1 if pt doesnt lie within cone height
	- returns t otherwise  */
double	intersect_cn_curve_math(t_cn *cone, t_vector *ray, t_vector *origin)
{
	double		a;
	double		b;
	double		c;
	double	cos_sq;
	t_vector	temp;
	t_vector	ray_pt;
	double		projection;
	double t;

	cos_sq = cos(cone->angle) * cos(cone->angle);
	a = vec_dot_product(ray, &cone->axis) * vec_dot_product(ray, &cone->axis) - cos_sq;
	vec_subtract(&temp, origin, &cone->coord);
	b = vec_dot_product(&temp, &cone->axis) * vec_dot_product(ray, &cone->axis) - (cos_sq * vec_dot_product(&temp, ray));
	b *= 2;
	c = vec_dot_product(&temp, &cone->axis) * vec_dot_product(&temp, &cone->axis) - (cos_sq * vec_dot_product(&temp, &temp));
	t = quadratic_formula(a, b, c);
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
