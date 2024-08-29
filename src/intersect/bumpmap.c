/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:25:52 by mateo             #+#    #+#             */
/*   Updated: 2024/08/29 21:10:36 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_vector get_sp_bm_normal(t_pixel *pixel, t_sp *sphere)
{
	double		theta;
	double		phi;
	t_vector	temp;

	vec_subtract(&temp, &pixel->intersect, &sphere->coord);
	phi = atan2(temp.z, temp.x);
	theta = acos(temp.y / sphere->radius);
	theta = 0.5 + theta / (2 * M_PI);
	phi /= (M_PI);
	theta = theta * sphere->bump_img.scale;
	phi = phi * sphere->bump_img.scale;
	theta = fmod(theta, 1.0);
	phi = fmod(phi, 1.0);
	theta = theta * sphere->bump_img.width;
	phi = phi * sphere->bump_img.height;
	return (get_bm_normal(theta, phi, &sphere->bump_img));
}

t_vector get_bm_normal(int x, int y, t_img *img)
{
	char	*data;
	int	colour;
	t_vector	normal;
	
	data = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	colour = *(unsigned int *)data;
	normal.x = (double)(colour >> 16 & 0xFF) / 255.0;
	normal.y = (double)(colour >> 8 & 0xFF) / 255.0;
	normal.z = (double)(colour & 0xFF) / 255.0;
	normal.x = normal.x * 2 - 1;
	normal.y = normal.y * 2 - 1;
	normal.z = normal.z * 2 - 1;
	vec_normalise(&normal);
	print_vector("normal:", &normal);
	return (normal);
}
