/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 07:46:22 by mateo             #+#    #+#             */
/*   Updated: 2024/08/08 10:53:46 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	print_vector prints coordinates in t_vector
	- can add str (e.g., "img_up: ") before printing coordinates
		for easier debugging */
void	print_vector(char *str, t_vector *vec)
{
	if (str)
		printf("%s", str);
	printf("x: %f, y: %f, z: %f\n", vec->x, vec->y, vec->z);
}

/*	vec_cmp_num compares coordinates in vec to the provided x, y and z
	- returns 1 if the same; 0 otherwise
	- vector equivalent of strcmp
	- can use to check if vec is a zero vector */
int	vec_cmp_num(t_vector *vec, double x, double y, double z)
{
	if (vec->x == x && vec->y == y && vec->z == z)
		return (1);
	return (0);
}