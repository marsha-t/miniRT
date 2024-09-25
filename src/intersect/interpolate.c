/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:59:07 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/25 13:02:42 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	interpolate_x(t_meta *meta_data, t_colour prev, int x, int y)
{
	int			x_prev;
	t_colour	curr;
	t_colour	out;

	x_prev = x - 3;
	curr = meta_data->pixel.final;
	out.r = prev.r + (((curr.r - prev.r) / (x - x_prev)) * ((x - 2) - x_prev));
	out.g = prev.g + (((curr.g - prev.g) / (x - x_prev)) * ((x - 2) - x_prev));
	out.b = prev.b + (((curr.b - prev.b) / (x - x_prev)) * ((x - 2) - x_prev));
	meta_data->curr_arr[x - 2] = out;
	img_mlx_pixel_put(meta_data, x - 2, y, create_trgb(out.r, out.g, out.b));
	out.r = prev.r + (((curr.r - prev.r) / (x - x_prev)) * ((x - 1) - x_prev));
	out.g = prev.g + (((curr.g - prev.g) / (x - x_prev)) * ((x - 1) - x_prev));
	out.b = prev.b + (((curr.b - prev.b) / (x - x_prev)) * ((x - 1) - x_prev));
	meta_data->curr_arr[x - 1] = out;
	img_mlx_pixel_put(meta_data, x - 1, y, create_trgb(out.r, out.g, out.b));
}

void	interpolate_y(t_meta *meta_data, t_colour prev, int x, int y)
{
	int			y_prev;
	t_colour	curr;
	t_colour	out;

	y_prev = y - 3;
	curr = meta_data->pixel.final;
	out.r = prev.r + (((curr.r - prev.r) / (y - y_prev)) * ((y - 2) - y_prev));
	out.g = prev.g + (((curr.g - prev.g) / (y - y_prev)) * ((y - 2) - y_prev));
	out.b = prev.b + (((curr.b - prev.b) / (y - y_prev)) * ((y - 2) - y_prev));
	meta_data->curr_arr[x - 2] = meta_data->pixel.final;
	img_mlx_pixel_put(meta_data, x, y - 2, create_trgb(out.r, out.g, out.b));
	out.r = prev.r + (((curr.r - prev.r) / (y - y_prev)) * ((y - 1) - y_prev));
	out.g = prev.g + (((curr.g - prev.g) / (y - y_prev)) * ((y - 1) - y_prev));
	out.b = prev.b + (((curr.b - prev.b) / (y - y_prev)) * ((y - 1) - y_prev));
	meta_data->curr_arr[x - 1] = meta_data->pixel.final;
	img_mlx_pixel_put(meta_data, x, y - 1, create_trgb(out.r, out.g, out.b));
}


double	color_diff(t_colour prev, t_colour curr)
{
	double	out;

	out = sqrt(pow(prev.r - curr.r, 2) + pow(prev.g - curr.g, 2) + \
		pow(prev.b - curr.b, 2));
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
	{
		meta_data->pixel.final.r = 0;
		meta_data->pixel.final.g = 0;
		meta_data->pixel.final.b = 0;
		img_mlx_pixel_put(meta_data, x, y, create_trgb(0, 0, 0));
	}
}
