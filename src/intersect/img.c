/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:58:44 by mateo             #+#    #+#             */
/*   Updated: 2024/08/13 11:56:58 by marvin           ###   ########.fr       */
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
	int x;
	int y;

	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
		{
			init_pixel(&meta_data->pixel);
			ray_dir(x, y, meta_data);
			if ((x == 200 && y == 200) || (x == 400 && y == 400) || (x == 600 && y == 600))
			{
				printf("x: %d y: %d\n", x, y);
				print_vector(RED"ray dir: "RST, &meta_data->pixel.ray);
				printf("t: %f\n", meta_data->pixel.t);
				// this is for checking the value of the normalized ray vector and t
			}
			intersect_closest(meta_data);
			if (meta_data->pixel.surface > 0)
			{
				gen_final_colour(meta_data);
				printf("r: %d g: %d b %d\n", meta_data->pixel.final.r, meta_data->pixel.final.g, meta_data->pixel.final.b);
				mlx_pixel_put(meta_data->mlx_ptr, meta_data->mlx_win, x, y, create_trgb(255, meta_data->pixel.final.r, meta_data->pixel.final.g, meta_data->pixel.final.b));
			}
			else
				mlx_pixel_put(meta_data->mlx_ptr, meta_data->mlx_win, x, y, 0x00000000);
		}
	}
	printf("loop out\n");
	// mlx_put_image_to_window(meta_data->mlx_ptr, meta_data->mlx_win, meta_data->img, 0, 0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
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

	// vec_multiply_scalar(&temp1, &meta_data->img_right, (double)i + 0.5
	// 		- meta_data->img_width / 2);
	vec_multiply_scalar(&temp1, &meta_data->img_right, ((2 * ((double)i + 0.5) \
		/ (WINDOW_WIDTH)) - 1) * (meta_data->img_width / 2));
	// vec_add(&temp2, &meta_data->img_center, &temp1);
	vec_add(&temp2, &meta_data->camera->orient, &temp1);
	// vec_multiply_scalar(&temp1, &meta_data->img_up, (meta_data->img_height - 1 - 2
	// 			* (double)j) / 2);
	vec_multiply_scalar(&temp1, &meta_data->img_up, (meta_data->img_height / 2) \
		- (((double)j + 0.5) * (meta_data->img_height / WINDOW_HEIGHT)));
	// vec_subtract(&pixel, &temp2, &temp1);
	vec_add(&temp2, &temp2, &temp1);
	vec_add(&pixel, &temp2, &meta_data->camera->coord);
	vec_subtract(&meta_data->pixel.ray, &pixel, &meta_data->camera->coord);
	vec_normalise(&meta_data->pixel.ray);
}
