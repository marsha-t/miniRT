/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:49:19 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/25 14:52:27 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	rt_mlxinit(t_meta *meta_data)
{
	meta_data->mlx_ptr = mlx_init();
	if (!meta_data->mlx_ptr)
		return ;
	meta_data->img = mlx_new_image(meta_data->mlx_ptr, \
		WINDOW_WIDTH, WINDOW_HEIGHT);
	meta_data->addr = mlx_get_data_addr(meta_data->img, \
		&meta_data->bits_per_pixel, &meta_data->line_length, \
		&meta_data->endian);
	meta_data->mlx_win = mlx_new_window(meta_data->mlx_ptr, \
		WINDOW_WIDTH, WINDOW_HEIGHT, \
		"MINIRT - MATEO | EMARAVIL");
	if (meta_data->img == NULL || meta_data->addr == NULL || \
		meta_data->mlx_win == NULL)
	{
		printf("Failed to create image\n");
		free_exit(meta_data);
		exit(EXIT_FAILURE);
	}
}
