/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:20:15 by mateo             #+#    #+#             */
/*   Updated: 2024/10/01 16:41:28 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	ft_key(int key, void *param)
{
	t_meta	*meta_data;

	meta_data = (t_meta *)param;
	ft_objectselect(meta_data, key);
	navigate_cy(meta_data, key);
	navigate_cn(meta_data, key);
	navigate_light(meta_data, key);
	navigate_sppl(meta_data, key);
	if (key == KEY_W)
		meta_data->low_quality = true;
	if (key == KEY_S)
		meta_data->low_quality = false;
	return (0);
}

int	ft_close(t_meta *meta_data)
{
	mlx_destroy_window(meta_data->mlx_ptr, meta_data->mlx_win);
	mlx_destroy_image(meta_data->mlx_ptr, meta_data->img);
	free(meta_data->mlx_ptr);
	free_exit(meta_data);
	exit(0);
	return (0);
}

void	increase_size_a(t_meta *meta_data, int key)
{
	double	*size;
	double	*size_a;

	size = meta_data->obj_option->size;
	size_a = meta_data->obj_option->size_a;
	if (key == KEY_Q && *size < DBL_MAX)
	{
		*size_a += 1;
		*size += 1;
	}
	if (key == KEY_A && *size > 1)
	{
		*size -= 1;
		*size_a -= 1;
	}
}
