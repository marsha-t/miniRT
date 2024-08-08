/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 07:41:44 by mateo             #+#    #+#             */
/*   Updated: 2024/08/08 10:53:44 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	vec_dot_product returns dot product of 2 vectors */
double	vec_dot_product(t_vector *a, t_vector *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

/*	vec_len calculates the length of a vector */
double	vec_len(t_vector *vec)
{
	double	len;

	len = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	return (len);
}

/*	vec_subtract subtracts b from a
	- updates dest with the multiplied values */
void	vec_subtract(t_vector *dest, t_vector *a, t_vector *b)
{
	dest->x = a->x - b->x;
	dest->y = a->y - b->y;
	dest->z = a->z - b->z;
}

/*	vec_add returns adds 2 vectors together 
	- updates dest with the multiplied values */
void	vec_add(t_vector *dest, t_vector *a, t_vector *b)
{
	dest->x = a->x + b->x;
	dest->y = a->y + b->y;
	dest->z = a->z + b->z;
}

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