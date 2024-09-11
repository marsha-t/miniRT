/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:25:06 by mateo             #+#    #+#             */
/*   Updated: 2024/09/03 16:26:00 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	vec_multiply_scalar multiplies vector with scalar
	- updates dest with the multiplied values */
void	vec_multiply_scalar(t_vector *dest, t_vector *vec, double n)
{
	dest->x = vec->x * n;
	dest->y = vec->y * n;
	dest->z = vec->z * n;
}

/*	vec_normalise normalises vec but does so in-place
*/
void	vec_normalise(t_vector *vec)
{
	double	len;

	len = vec_len(vec);
	vec->x /= len;
	vec->y /= len;
	vec->z /= len;
}

/*	vec_cross_product does the cross product of 2 vectors
	- updates dest with the multiplied values */
void	vec_cross_product(t_vector *dest, t_vector *a, t_vector *b)
{
	dest->x = a->y * b->z - a->z * b->y;
	dest->y = a->z * b->x - a->x * b->z;
	dest->z = a->x * b->y - a->y * b->x;
}
