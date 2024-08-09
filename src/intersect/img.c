/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:58:44 by mateo             #+#    #+#             */
/*   Updated: 2024/08/09 14:53:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	gen_img loads the image buffer
	- iterates through each pixel and calculates intersection and 
		light components to get final colour for pixel */
void	gen_img(t_meta *meta_data)
{
	/* pseudo code
	while (i, j) // iterate through pixels i, j
	{
		init_pixel();
		compute ray
		find closest intersection
		{
			go through each obj and find intersection
			{
				if intersection occurs at closer t, update pixel struct
			}
		}
		determine colour
		{
			calculate ambient light
			go through each light
			{
				if in shadow, skip
				if not, final colour += diffuse + specular
			}

		}
		put_pixel()
	}
	*/
	init_pixel(&meta_data->pixel);
	ray_dir(0, 0, meta_data);
	print_vector("ray dir: ", &meta_data->pixel.ray);
	intersect_closest(meta_data);
	gen_final_colour(meta_data);
}

/*	init_pixel initialises the pixel struct to default values
	at the start of every calculation for each pixel (i, j) */
void	init_pixel(t_pixel *pixel)
{
	pixel->t = DBL_MAX;
	pixel->obj = 0;
	pixel->surface = -1;
}

/*	ray_dir calculates ray direction of a pixel (i, j)
*/
void	ray_dir(int i, int j, t_meta *meta_data)
{
	t_vector	temp1;
	t_vector	temp2;
	t_vector	pixel;

	vec_multiply_scalar(&temp1, &meta_data->img_right, (double)i + 0.5
			- meta_data->img_width / 2);
	vec_add(&temp2, &meta_data->img_center, &temp1);
	vec_multiply_scalar(&temp1, &meta_data->img_up, (meta_data->img_height - 1 - 2
				* (double)j) / 2);
	vec_subtract(&pixel, &temp2, &temp1);
	vec_subtract(&meta_data->pixel.ray, &pixel, &meta_data->camera->coord);
	vec_normalise(&meta_data->pixel.ray);
}
