/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:58:44 by mateo             #+#    #+#             */
/*   Updated: 2024/09/27 17:10:26 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	gen_img loads the image buffer
	- iterates through each pixel and calculates intersection and
		light components to get final colour for pixel */
void	gen_img(t_meta *meta_data)
{
	int			x;
	int			y;
	int			count;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		count = 0;
		while (x < WINDOW_WIDTH)
		{
			render(meta_data, x, y);
			x = x + meta_data->step_x;
		}
		while (count < WINDOW_WIDTH + 1)
		{
			meta_data->prev_arr[count] = meta_data->curr_arr[count];
			count++;
		}
		y = y + meta_data->step_y;
	}
}

void	init_colours(t_meta *meta_data)
{
	int			count;

	count = 0;
	if (meta_data->low_quality)
		meta_data->step_y = 3;
	else
		meta_data->step_y = 1;
	while (count < WINDOW_WIDTH + 1)
	{
		meta_data->prev_arr[count] = meta_data->colour_init;
		meta_data->curr_arr[count] = meta_data->colour_init;
		count++;
	}
}

int	create_trgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
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

	vec_multiply_scalar(&temp1, &meta_data->img_right, ((2 * ((double)i + 0.5)
				/ (double)(WINDOW_WIDTH)) - 1) * (meta_data->img_width / 2)
		* meta_data->aspect_ratio);
	vec_add(&temp2, &meta_data->img_forward, &temp1);

	vec_multiply_scalar(&temp1, &meta_data->img_up, (meta_data->img_width / 2)
		* (1 - (2 * ((double)j + 0.5) / (double)WINDOW_HEIGHT)));
	vec_add(&temp2, &temp2, &temp1);
	vec_add(&pixel, &temp2, &meta_data->camera->coord);
	vec_subtract(&meta_data->pixel.ray, &pixel, &meta_data->camera->coord);
	meta_data->pixel.ray.z = FOCAL_LENGTH;
	vec_normalise(&meta_data->pixel.ray);
}
