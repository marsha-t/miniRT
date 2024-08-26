/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:58:44 by mateo             #+#    #+#             */
/*   Updated: 2024/08/26 11:38:29 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	gen_img loads the image buffer
	- iterates through each pixel and calculates intersection and 
		light components to get final colour for pixel */
void	gen_img(t_meta *meta_data)
{
	int x;
	int y;
	// int	pixel_processed;
	// double	progress;
	// char	progress_str[50];

	y = -1;
	// pixel_processed = 0;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
		{
			init_pixel(&meta_data->pixel);
			ray_dir(x, y, meta_data);
			intersect_closest(meta_data);
			prepare_intersect(&meta_data->pixel);
			if (meta_data->pixel.t >= 0 && meta_data->pixel.t != DBL_MAX)
			{
				get_checkerboard(meta_data);
				gen_final_colour(meta_data);
				// printf("after gen final color\n");
				// printf("x: %d y: %d\n", x, y);
				// printf("t: %f\n", meta_data->pixel.t);
				// printf(Y"pixel final: r: %f g: %f b: %f\n"RST, meta_data->pixel.final.r, meta_data->pixel.final.g, meta_data->pixel.final.b);
				img_mlx_pixel_put(meta_data, x, y, create_trgb(meta_data->pixel.final.r, meta_data->pixel.final.g, meta_data->pixel.final.b));
			}
			else
			{
				img_mlx_pixel_put(meta_data, x, y, create_trgb(0, 0, 0));
			}
			// pixel_processed++;
			// progress = ((double)pixel_processed / (WINDOW_WIDTH * WINDOW_HEIGHT)) * 100;
			// printf(Y"\rRendering progress: %.2f%%"RST, progress);
			// fflush(stdout);
			// snprintf(progress_str, sizeof(progress_str), "Rendering progress: %.2f%%", progress);
            // mlx_string_put(meta_data->mlx_ptr, meta_data->mlx_win, 10, 10, 0xFFFFFF, progress_str);
		}
	}
	// printf(Y"\rRendering progress: 100.00%%\n"RST);
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

	vec_multiply_scalar(&temp1, &meta_data->img_right, ((2 * ((double)i + 0.5) \
		/ (double)(WINDOW_WIDTH)) - 1) * (meta_data->img_width / 2) * meta_data->aspect_ratio);
	vec_add(&temp2, &meta_data->camera->orient, &temp1);
	vec_multiply_scalar(&temp1, &meta_data->img_up, (meta_data->img_width / 2) * \
		(1 - (2 * ((double)j + 0.5) / (double)WINDOW_HEIGHT)));
	vec_add(&temp2, &temp2, &temp1);
	vec_add(&pixel, &temp2, &meta_data->camera->coord);
	// Pworld = Camera->coord + (IMG_R * NDCx * img_wid/2) + (IMG_U * NDCy * img_h/2) + Camera->orient
	vec_subtract(&meta_data->pixel.ray, &pixel, &meta_data->camera->coord);
	meta_data->pixel.ray.z = FOCAL_LENGTH;
	vec_normalise(&meta_data->pixel.ray);
}
