/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:59:07 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/26 21:09:32 by mateo            ###   ########.fr       */
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
	if (!meta_data->addr)
		{
			fprintf(stderr, "here4\n");
			exit(EXIT_FAILURE);
		}
	img_mlx_pixel_put(meta_data, x - 2, y, create_trgb(out.r, out.g, out.b));
	out.r = prev.r + (((curr.r - prev.r) / (x - x_prev)) * ((x - 1) - x_prev));
	out.g = prev.g + (((curr.g - prev.g) / (x - x_prev)) * ((x - 1) - x_prev));
	out.b = prev.b + (((curr.b - prev.b) / (x - x_prev)) * ((x - 1) - x_prev));
	meta_data->curr_arr[x - 1] = out;
	if (!meta_data->addr)
		{
			fprintf(stderr, "here5\n");
			exit(EXIT_FAILURE);
		}
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
	if (!meta_data->addr)
		{
			fprintf(stderr, "here6\n");
			exit(EXIT_FAILURE);
		}
		img_mlx_pixel_put(meta_data, x, y - 2, create_trgb(out.r, out.g, out.b));
	out.r = prev.r + (((curr.r - prev.r) / (y - y_prev)) * ((y - 1) - y_prev));
	out.g = prev.g + (((curr.g - prev.g) / (y - y_prev)) * ((y - 1) - y_prev));
	out.b = prev.b + (((curr.b - prev.b) / (y - y_prev)) * ((y - 1) - y_prev));
	meta_data->curr_arr[x - 1] = meta_data->pixel.final;
	if (!meta_data->addr)
		{
			fprintf(stderr, "here7\n");
			exit(EXIT_FAILURE);
		}
		img_mlx_pixel_put(meta_data, x, y - 1, create_trgb(out.r, out.g, out.b));
}

double	color_diff(t_colour prev, t_colour curr)
{
	double	out;

	out = sqrt(pow(prev.r - curr.r, 2) + pow(prev.g - curr.g, 2) + \
		pow(prev.b - curr.b, 2));
	return (out);
}
