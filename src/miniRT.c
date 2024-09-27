/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:47:25 by emaravil          #+#    #+#             */
/*   Updated: 2024/08/07 18:51:48 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	main(int argc, char **argv)
{
	t_meta	meta_data;

	print_banner();
	rt_mlxinit(&meta_data);
	meta_data_init(&meta_data);
	parse_data(&meta_data, argc, argv);
	setup_handlesignal(&meta_data);
	draw(&meta_data);
	mlx_put_image_to_window(meta_data.mlx_ptr, meta_data.mlx_win, 
		meta_data.img, 0, 0);
	mlx_hook(meta_data.mlx_win, 2, 1L << 0, handle_keypress, &meta_data);
	mlx_hook(meta_data.mlx_win, 3, 1L << 1, handle_keyrelease, &meta_data);
	mlx_hook(meta_data.mlx_win, 17, 0, ft_close, &meta_data);
	mlx_loop_hook(meta_data.mlx_ptr, &update, &meta_data);
	mlx_loop(meta_data.mlx_ptr);
	ft_close(&meta_data);
	free_exit(&meta_data);
	return (1);
}

void	draw(t_meta *meta_data)
{
	if (meta_data->move == true)
		ft_controls(meta_data);
	if (meta_data->rotate == true && meta_data->obj_select != 1 && \
		meta_data->obj_select != 5 && meta_data->obj_select != 6 && meta_data->obj_select != 7 )
		rotation(meta_data);
	prepare_data(meta_data);
	gen_img(meta_data);
}

void	img_mlx_pixel_put(t_meta *meta_data, int x, int y, int color)
{
	char	*dst;

	 if (x < 0 || y < 0 || x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT)
        return;

    if (!meta_data )
    {
        fprintf(stderr, "Error: meta_data  is not initialized.\n");
        return;
    }
	if (!meta_data->addr)
	{
		fprintf(stderr, "Error: meta_data->addr is not initialized.\n");
        return;
	}
	// if (!(x < 0 || y < 0 || x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT))
	// {
		dst = meta_data->addr + (y * meta_data->line_length + x * \
			(meta_data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	// }
}

void	increase_size(t_meta *meta_data, int key)
{
	double	*size;
	double	step;
	double	max;
	double	min;

	size = meta_data->obj_option->size;
	if (meta_data->obj_select == 6 || meta_data->obj_select == 5)
	{
		max = 1;
		min = 0.1;
		step = 0.01;
	}
	else
	{
		max = DBL_MAX;
		min = 1;
		step = 1;
	}
	if (key == KEY_Q && *size < max)
		*size += step;
	if (key == KEY_A && *size > min)
		*size -= step;
}
