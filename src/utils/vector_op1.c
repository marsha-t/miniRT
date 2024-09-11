/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 07:41:44 by mateo             #+#    #+#             */
/*   Updated: 2024/09/03 16:25:34 by mateo            ###   ########.fr       */
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

void	vec_inv(t_vector *dest, t_vector *a)
{
	dest->x = -(a->x);
	dest->y = -(a->y);
	dest->z = -(a->z);
}

/*	vec_add returns adds 2 vectors together 
	- updates dest with the multiplied values */
void	vec_add(t_vector *dest, t_vector *a, t_vector *b)
{
	dest->x = a->x + b->x;
	dest->y = a->y + b->y;
	dest->z = a->z + b->z;
}
