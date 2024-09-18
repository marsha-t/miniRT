/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:03:25 by mateo             #+#    #+#             */
/*   Updated: 2024/09/19 00:28:43 by marvin           ###   ########.fr       */
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
