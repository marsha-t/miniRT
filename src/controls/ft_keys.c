/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:52:23 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/25 14:51:12 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	ft_key(int key, void *param)
{
	t_meta	*meta_data;

	meta_data = (t_meta *)param;
	ft_objectselect(meta_data, key);
	navigate_cycn(meta_data, key);
	navigate_light(meta_data, key);
	navigate_sppl(meta_data, key);
	increase_size(meta_data, key);
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
	exit(0);
	return (0);
}
