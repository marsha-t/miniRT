/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:54:15 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/25 13:58:19 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	update(t_meta *meta_data)
{
	if (meta_data->move || meta_data->rotate)
	{
		mlx_clear_window(meta_data->mlx_ptr, meta_data->mlx_win);
		mlx_destroy_image(meta_data->mlx_ptr, meta_data->img);
		meta_data->img = mlx_new_image(meta_data->mlx_ptr, WINDOW_WIDTH, \
			WINDOW_HEIGHT);
		draw(meta_data);
		mlx_put_image_to_window(meta_data->mlx_ptr, meta_data->mlx_win, \
			meta_data->img, 0, 0);
	}
	return (0);
}

int	handle_keypress(int key, void *param)
{
	t_meta	*meta_data;

	meta_data = (t_meta *)param;
	if (key == KEY_ESC)
		ft_close(meta_data);
	ft_key(key, meta_data);
	ft_controls_status(meta_data, key, true);
	ft_rotation_status(meta_data, key, true);
	if (key == NUMPAD_2 || key == NUMPAD_4 || key == NUMPAD_6 || \
		key == NUMPAD_8 || key == NUMPAD_PLUS || key == \
		NUMPAD_MIN || key == KEY_Q || key == KEY_A)
		meta_data->move = true;
	if (key == KEY_U || key == KEY_J || key == KEY_I || \
		key == KEY_K || key == KEY_O || key == KEY_L)
		meta_data->rotate = true;
	return (0);
}

int	handle_keyrelease(int key, void *param)
{
	t_meta	*meta_data;

	meta_data = (t_meta *)param;
	ft_controls_status(meta_data, key, false);
	ft_rotation_status(meta_data, key, false);
	meta_data->move = false;
	meta_data->rotate = false;
	return (0);
}

void	ft_controls(t_meta *meta_data)
{
	t_vector	*vector;

	vector = meta_data->obj_option->coord;
	if (meta_data->move_y_i)
		vector->y += 1;
	if (meta_data->move_y_d)
		vector->y -= 1;
	if (meta_data->move_x_d)
		vector->x -= 1;
	if (meta_data->move_x_i)
		vector->x += 1;
	if (meta_data->move_z_i)
		vector->z += 1;
	if (meta_data->move_z_d)
		vector->z -= 1;
}

void	ft_controls_status(t_meta *meta_data, int key, bool status)
{
	if (key == NUMPAD_8)
		meta_data->move_y_i = status;
	if (key == NUMPAD_2)
		meta_data->move_y_d = status;
	if (key == NUMPAD_4)
		meta_data->move_x_d = status;
	if (key == NUMPAD_6)
		meta_data->move_x_i = status;
	if (key == NUMPAD_PLUS)
		meta_data->move_z_i = status;
	if (key == NUMPAD_MIN)
		meta_data->move_z_d = status;
}
