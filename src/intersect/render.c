/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:19:06 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/26 21:13:14 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	render_image(t_meta *meta_data, int x, int y)
{
	if (!meta_data->addr)
		{
			fprintf(stderr, "here999\n");
			exit(EXIT_FAILURE);
		}
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
	{
		meta_data->pixel.final = meta_data->colour_init;
		img_mlx_pixel_put(meta_data, x, y, create_trgb(0, 0, 0));
	}
}

void	render_x(t_meta *meta_data, int x, int y)
{
	if (color_diff(meta_data->curr_arr[x - 3], meta_data->curr_arr[x]) \
		> LOW_RES)
	{
		if (!meta_data->addr)
		{
			fprintf(stderr, "here1\n");
			exit(EXIT_FAILURE);
		}
		render_image(meta_data, x - 1, y);
		meta_data->curr_arr[x - 1] = meta_data->pixel.final;
		if (!meta_data->addr)
		{
			fprintf(stderr, "here2\n");
			exit(EXIT_FAILURE);
		}
		render_image(meta_data, x - 2, y);
		meta_data->curr_arr[x - 2] = meta_data->pixel.final;
	}
	else
		interpolate_x(meta_data, meta_data->curr_arr[x - 3], x, y);
}

void	render_y(t_meta *meta_data, int x, int y)
{
	int	x_min;

	x_min = x - 3;
	while (x_min <= x)
	{
		if (color_diff(meta_data->prev_arr[x_min], meta_data->curr_arr[x_min]) \
			> LOW_RES)
		{
			if (!meta_data->addr)
		{
			fprintf(stderr, "here3\n");
			exit(EXIT_FAILURE);
		}
			render_image(meta_data, x_min, y - 1);
			if (!meta_data->addr)
		{
			fprintf(stderr, "here4\n");
			exit(EXIT_FAILURE);
		}
			render_image(meta_data, x_min, y - 2);
		}
		else
			interpolate_y(meta_data, meta_data->prev_arr[x_min], x_min, y);
		x_min++;
	}
}

void	render(t_meta *meta_data, int x, int y)
{
	if (!meta_data->addr)
		{
			fprintf(stderr, "here5\n");
			exit(EXIT_FAILURE);
		}
		render_image(meta_data, x, y);
	meta_data->curr_arr[x] = meta_data->pixel.final;
	if (x > 0)
		render_x(meta_data, x, y);
	if (y > 0 && meta_data->low_quality == true)
		render_y(meta_data, x, y);
}
