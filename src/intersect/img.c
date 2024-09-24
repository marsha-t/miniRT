/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:58:44 by mateo             #+#    #+#             */
/*   Updated: 2024/09/24 22:30:56 by emaravil         ###   ########.fr       */
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
	int			step;
	int			count;

	y = 0;
	count = 0;
	if (!meta_data->low_quality)
		step = 1;
	else
		step = 3;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		count = 0;
		while (x < WINDOW_WIDTH)
		{
			render_image(meta_data, x, y);
			meta_data->curr_arr[x] = meta_data->pixel.final;
			if (x > 0)
				render_x(meta_data, x, y);
			if (y > 0 && meta_data->low_quality == true)
				render_y(meta_data, x, y);
			x = x + 3;
		}
		while (count < WINDOW_WIDTH + 1)
		{
			meta_data->prev_arr[count] = meta_data->curr_arr[count];
			count++;
		}
		y = y + step;
	}
}

void	render_x(t_meta *meta_data, int x, int y)
{
	if (color_diff(meta_data->curr_arr[x - 3], meta_data->pixel.final) \
		> LOW_RES)
	{
		render_image(meta_data, x - 1, y);
		meta_data->curr_arr[x - 1] = meta_data->pixel.final;
		render_image(meta_data, x - 2, y);
		meta_data->curr_arr[x - 2] = meta_data->pixel.final;
	}
	else
		interpolate_x(meta_data, meta_data->curr_arr[x - 3], x, y);
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
	vec_add(&temp2, &meta_data->camera->orient, &temp1);
	vec_multiply_scalar(&temp1, &meta_data->img_up, (meta_data->img_width / 2)
		* (1 - (2 * ((double)j + 0.5) / (double)WINDOW_HEIGHT)));
	vec_add(&temp2, &temp2, &temp1);
	vec_add(&pixel, &temp2, &meta_data->camera->coord);
	vec_subtract(&meta_data->pixel.ray, &pixel, &meta_data->camera->coord);
	meta_data->pixel.ray.z = FOCAL_LENGTH;
	vec_normalise(&meta_data->pixel.ray);
}

void	render_y(t_meta *meta_data, int x, int y)
{
	int	x_min;
	int	y_min;

	x_min = x - 3;
	y_min = y - 3;
	while (x_min <= x)
	{
		if (color_diff(meta_data->prev_arr[x_min], meta_data->curr_arr[x_min]) \
			> LOW_RES)
		{
			render_image(meta_data, x_min, y - 1);
			render_image(meta_data, x_min, y - 2);
		}
		else
			interpolate_y(meta_data, meta_data->prev_arr[x_min], x_min, y);
		x_min++;
	}
}