/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:58:44 by mateo             #+#    #+#             */
/*   Updated: 2024/09/19 15:15:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	gen_img loads the image buffer
	- iterates through each pixel and calculates intersection and
		light components to get final colour for pixel */
void	gen_img(t_meta *meta_data)
{
	int	x;
	int	y;
	t_colour prev;

	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			render_image(meta_data, x, y);
			if (x > 0 && y > 0)
			{
				if (color_diff(prev, meta_data->pixel.final) > LOW_RES)
				{
					render_image(meta_data, x - 1, y);
					render_image(meta_data, x - 2, y);
				}
				else
					interpolate(meta_data, prev, x, y);
			}
			prev = meta_data->pixel.final;
			x = x + 3;
		}
	}
}

void	interpolate(t_meta *meta_data, t_colour prev, int x, int y)
{
	int	x_prev;
	t_colour curr;
	t_colour out;

	x_prev = x - 3;
	curr = meta_data->pixel.final;
	out.r = prev.r + (((curr.r - prev.r) / (x - x_prev)) * ((x - 2) - x_prev));
	out.g = prev.g + (((curr.g - prev.g) / (x - x_prev)) * ((x - 2) - x_prev));
	out.b = prev.b + (((curr.b - prev.b) / (x - x_prev)) * ((x - 2) - x_prev));
	img_mlx_pixel_put(meta_data, x - 2, y, create_trgb(out.r, out.g, out.b));
	out.r = prev.r + (((curr.r - prev.r) / (x - x_prev)) * ((x - 1) - x_prev));
	out.g = prev.g + (((curr.g - prev.g) / (x - x_prev)) * ((x - 1) - x_prev));
	out.b = prev.b + (((curr.b - prev.b) / (x - x_prev)) * ((x - 1) - x_prev));
	img_mlx_pixel_put(meta_data, x - 1, y, create_trgb(out.r, out.g, out.b));
}

double	color_diff(t_colour prev, t_colour curr)
{
	double out;

	out = sqrt(pow(prev.r - curr.r, 2) + pow(prev.g - curr.g, 2) + pow(prev.b - curr.b, 2));
	// printf("color diff %f\n", out);
	// printf("\tprev r %f g %f b %f || curr r %f g %f b %f\n", prev.r, prev.g, prev.b, curr.r, curr.g, curr.b);
	return (out);
}



void	render_image(t_meta *meta_data, int x, int y)
{
	init_pixel(&meta_data->pixel);
	ray_dir(x, y, meta_data);
	intersect_closest(meta_data);
	prepare_intersect(&meta_data->pixel);
	if (meta_data->pixel.t >= 0 && meta_data->pixel.t != DBL_MAX)
	{
		get_checkerboard(meta_data);
		gen_final_colour(meta_data);
		img_mlx_pixel_put(meta_data, x, y,
			create_trgb(meta_data->pixel.final.r,
				meta_data->pixel.final.g, meta_data->pixel.final.b));
	}
	else
		img_mlx_pixel_put(meta_data, x, y, create_trgb(0, 0, 0));
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
