/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:03:25 by mateo             #+#    #+#             */
/*   Updated: 2024/10/02 12:12:10 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	quadratic formula solves for a quadratic equation (given a, b, c)
	- returns smallest positivmakee t or -1 otherwise */
double	quadratic_formula(double a, double b, double c)
{
	double	t;
	double	t2;
	double	discriminant;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	t = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (discriminant == 0 && t <= 0)
		return (-1);
	else if (discriminant == 0 && t > 0)
		return (t);
	else if (t <= 0 && t2 <= 0)
		return (-1);
	else if (t <= 0 && t2 > 0)
		return (t2);
	else if (t > 0 && t2 > 0 && t < t2)
		return (t);
	else if (t > 0 && t2 > 0 && t >= t2)
		return (t2);
	else
		return (t);
}

/*	get_ray_pt generates coordinates for point on ray
	- point = camera + t * ray_direction
*/
void	get_ray_pt(t_vector *dest, t_vector *ray, t_vector *origin, double t)
{
	t_vector	temp;

	vec_multiply_scalar(&temp, ray, t);
	vec_add(dest, origin, &temp);
}

int	largest_component(t_vector vector)
{
	if (vector.x < 0)
		vector.x *= -1;
	if (vector.y < 0)
		vector.y *= -1;
	if (vector.z < 0)
		vector.z *= -1;
	if (vector.x > vector.y && vector.x > vector.z)
		return (1);
	else if (vector.y > vector.x && vector.y > vector.z)
		return (2);
	else
		return (3);
}

void	rejig_forward(t_meta *meta_data, int axis)
{
	if (axis == 1)
	{
		if (meta_data->img_forward.x < 0)
			meta_data->pixel.ray.x = -1 * FOCAL_LENGTH;
		else
			meta_data->pixel.ray.x = FOCAL_LENGTH;
	}
	else if (axis == 2)
	{
		if (meta_data->img_forward.y < 0)
			meta_data->pixel.ray.y = -1 * FOCAL_LENGTH;
		else
			meta_data->pixel.ray.y = FOCAL_LENGTH;
	}
	else
	{
		if (meta_data->img_forward.z < 0)
			meta_data->pixel.ray.z = -1 * FOCAL_LENGTH;
		else
			meta_data->pixel.ray.z = FOCAL_LENGTH;
	}
}
