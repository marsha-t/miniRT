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
	meta_data_init(&meta_data);
	parse_data(&meta_data, argc, argv);
	rt_mlxinit(&meta_data);
	draw(&meta_data);
	mlx_put_image_to_window(meta_data.mlx_ptr, meta_data.mlx_win, \
		meta_data.img, 0, 0);
	mlx_hook(meta_data.mlx_win, 2, 0, handle_keypress, &meta_data);
	mlx_hook(meta_data.mlx_win, 3, 1L << 1, handle_keyrelease, &meta_data);
	mlx_hook(meta_data.mlx_win, 17, 0, ft_close, &meta_data);
	mlx_loop_hook(meta_data.mlx_ptr, &update, &meta_data);
	mlx_loop(meta_data.mlx_ptr);
	ft_close(&meta_data);
	free_exit(&meta_data);
	return (1);
}

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
	if (key == NUMPAD_2 || key == NUMPAD_4 || key == NUMPAD_6 || key == NUMPAD_8 \
		|| key == NUMPAD_PLUS || key == NUMPAD_MIN || key == KEY_Q || key == KEY_A)
		meta_data->move = true;
	if (key == KEY_U || key == KEY_J || key == KEY_I || key == KEY_K || key == KEY_O \
		|| key == KEY_L)
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

void	draw(t_meta *meta_data)
{
	ft_controls(meta_data);
	if (meta_data->obj_select == 7)
		translate_camera(meta_data);
	prepare_data(meta_data);
	gen_img(meta_data);
}

void	rt_mlxinit(t_meta *meta_data)
{
	meta_data->mlx_ptr = mlx_init();
	if (!meta_data->mlx_ptr)
		return ;
	meta_data->img = mlx_new_image(meta_data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (meta_data->img == NULL)
	{
		printf("Failed to create image\n");
		return ;
	}
	meta_data->addr = mlx_get_data_addr(meta_data->img, &meta_data->bits_per_pixel,\
		&meta_data->line_length, &meta_data->endian);
	if (meta_data->addr == NULL)
	{
		printf("Failed to create image\n");
		return ;
	}
	meta_data->mlx_win = mlx_new_window(meta_data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, \
		"MINIRT - MATEO | EMARAVIL");
	if (meta_data->mlx_win == NULL)
	{
		printf("Failed to create image\n");
		return ;
	}
}

void	rotate_camera_y(t_vector *orientation, double theta_y)
{
	double	cos_theta;
	double	sin_theta;
	double	new_x;
	double	new_z;

	cos_theta = cos(theta_y);
	sin_theta = sin(theta_y);
	new_x = (cos_theta * orientation->x) + (sin_theta * orientation->z);
	new_z = (-sin_theta * orientation->x) + (cos_theta * orientation->z);
	orientation->x = new_x;
	orientation->z = new_z;
}

void	rotate_camera_x(t_vector *orientation, double theta_x)
{
	double	cos_theta;
	double	sin_theta;
	double	new_y;
	double	new_z;

	cos_theta = cos(theta_x);
	sin_theta = sin(theta_x);
	new_y = (cos_theta * orientation->y) - (sin_theta * orientation->z);
	new_z = (sin_theta * orientation->y) + (cos_theta * orientation->z);
	orientation->y = new_y;
	orientation->z = new_z;
}

void	rotate_camera_z(t_vector *orientation, double theta_z)
{
	double	cos_theta;
	double	sin_theta;
	double	new_x;
	double	new_y;

	cos_theta = cos(theta_z);
	sin_theta = sin(theta_z);
	new_x = (cos_theta * orientation->x) - (sin_theta * orientation->y);
	new_y = (sin_theta * orientation->x) + (cos_theta * orientation->y);
	orientation->x = new_x;
	orientation->y = new_y;
}

void ft_controls(t_meta *meta_data)
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

void ft_controls_status(t_meta *meta_data, int key, bool status)
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

void ft_rotation_status(t_meta *meta_data, int key, bool status)
{
	if (key == KEY_U)
		meta_data->rot_x_i = status;
	if (key == KEY_J)
		meta_data->rot_x_d = status;
	if (key == KEY_I)
		meta_data->rot_y_i = status;
	if (key == KEY_K)
		meta_data->rot_y_d = status;
	if (key == KEY_O)
		meta_data->rot_z_i = status;
	if (key == KEY_L)
		meta_data->rot_z_d = status;
	if (key == KEY_R)
		meta_data->rot_reset = status;
}

void ft_objectselect(t_meta *meta_data, int key)
{

	if (key == KEY_1 && meta_data->sp_allocated)
	{
		printf(Y"SPHERE SELECTED\n"RST);
		meta_data->obj = (void *)meta_data->sp;
		meta_data->obj_option->coord = &meta_data->sp->coord;
		meta_data->obj_option->size = &meta_data->sp->diameter;
		meta_data->obj_select = 1;
	}
	else if (key == KEY_2 && meta_data->cy_allocated)
	{
		printf(Y"CYLINDER SELECTED\n"RST);
		meta_data->obj = (void *)meta_data->cy;
		meta_data->obj_option->coord = &meta_data->cy->coord;
		meta_data->obj_option->size = &meta_data->cy->diameter;
		meta_data->obj_select = 2;
	}
	else if (key == KEY_3 && meta_data->pl_allocated)
	{
		printf(Y"PLANE SELECTED\n"RST);
		meta_data->obj = (void *)meta_data->pl;
		meta_data->obj_option->coord = &meta_data->pl->coord;
		meta_data->obj_select = 3;
	}
	else if (key == KEY_4 && meta_data->cn_allocated)
	{
		printf(Y"CONE SELECTED\n"RST);
		meta_data->obj = (void *)meta_data->cn;
		meta_data->obj_option->coord = &meta_data->cn->coord;
		meta_data->obj_option->size = &meta_data->cn->height;
		meta_data->obj_select = 4;
	}
	else if (key == KEY_5 && meta_data->light_allocated)
	{
		printf(Y"LIGHT SELECTED\n"RST);
		meta_data->obj = (void *)meta_data->light;
		meta_data->obj_option->coord = &meta_data->light->coord;
		meta_data->obj_option->size = &meta_data->light->brightness;
		meta_data->obj_select = 5;
	}
	else if (key == KEY_6 && meta_data->sl_allocated)
	{
		printf(Y"SPOTLIGHT SELECTED\n"RST);
		meta_data->obj = (void *)meta_data->spotlight;
		meta_data->obj_option->coord = &meta_data->spotlight->coord;
		meta_data->obj_option->size = &meta_data->spotlight->brightness;
		meta_data->obj_select = 6;
	}
	else if (key == KEY_7 && meta_data->camera_allocated)
	{
		printf(Y"CAMERA SELECTED\n"RST);
		meta_data->obj = (void *)meta_data->camera;
		meta_data->obj_option->coord = &meta_data->camera->coord;
		meta_data->obj_option->size = &meta_data->camera->fov;
		meta_data->obj_select = 7;
	}
}

void    navigate(t_meta *meta_data, int key)
{
	t_sp *sp;
	t_pl *pl;
	t_cy *cy;
	t_cn *cn;
	t_light *light;
	t_spotlight *spotlight;

	sp = NULL;
	pl = NULL;
	cy = NULL;
	cn = NULL;
	light = NULL;
	spotlight = NULL;
	if (meta_data->obj_select == 1 && key == NUMPAD_5)
	{
		sp = (t_sp *)meta_data->obj;
		meta_data->obj_option->coord = &sp->coord;
		meta_data->obj_option->size = &sp->diameter;
		if (sp->next != NULL)
			meta_data->obj = (void *)sp->next;
		else
			meta_data->obj = (void *)meta_data->sp;
	}
	if (meta_data->obj_select == 2 && key == NUMPAD_5)
	{
		cy = (t_cy *)meta_data->obj;
		meta_data->obj_option->coord = &cy->coord;
		meta_data->obj_option->size = &cy->diameter;
		if (cy->next != NULL)
			meta_data->obj = (void *)cy->next;
		else
			meta_data->obj = (void *)meta_data->cy;
	}
	if (meta_data->obj_select == 3 && key == NUMPAD_5)
	{
		pl = (t_pl *)meta_data->obj;
		meta_data->obj_option->coord = &pl->coord;
		if (pl->next != NULL)
			meta_data->obj = (void *)pl->next;
		else
			meta_data->obj = (void *)meta_data->pl;
	}
	if (meta_data->obj_select == 4 && key == NUMPAD_5)
	{
		cn = (t_cn *)meta_data->obj;
		meta_data->obj_option->coord = &cn->coord;
		meta_data->obj_option->size = &cn->height;
		if (cn->next != NULL)
			meta_data->obj = (void *)cn->next;
		else
			meta_data->obj = (void *)meta_data->cn;
	}
	if (meta_data->obj_select == 5 && key == NUMPAD_5)
	{
		light = (t_light *)meta_data->obj;
		meta_data->obj_option->coord = &light->coord;
		if (light->next != NULL)
			meta_data->obj = (void *)light->next;
		else
			meta_data->obj = (void *)meta_data->light;
		meta_data->obj_option->size = &light->brightness;
	}
	if (meta_data->obj_select == 6 && key == NUMPAD_5)
	{
		spotlight = (t_spotlight *)meta_data->obj;
		meta_data->obj_option->coord = &spotlight->coord;
		if (spotlight->next != NULL)
			meta_data->obj = (void *)spotlight->next;
		else
			meta_data->obj = (void *)meta_data->spotlight;
		meta_data->obj_option->size = &spotlight->brightness;
	}
}

void    increase_size(t_meta *meta_data, int key)
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

/*	ft_key directs specific keypresses to various actions
	- close
*/
int	ft_key(int key, void *param)
{
	t_meta	*meta_data;

	meta_data = (t_meta *)param;
	ft_objectselect(meta_data, key);
	navigate(meta_data, key);
	increase_size(meta_data, key);
	if (key == KEY_W)
	{
		meta_data->mid_quality = true;
		meta_data->low_quality = true;
	}
	if (key == KEY_S)
	{
		meta_data->mid_quality = true;
		meta_data->low_quality = false;
	}
	if (key == KEY_E)
	{
		meta_data->mid_quality = false;
		meta_data->low_quality = false;
	}
	return (0);
}

void    translate_camera(t_meta *meta_data)
{
	if (meta_data->rot_x_i)
	{
		meta_data->pixel.theta_x += 0.001;
		if (meta_data->pixel.theta_x > (2 * M_PI))
			meta_data->pixel.theta_x = 0;
		rotate_camera_x(&meta_data->camera->orient, meta_data->pixel.theta_x);
	}
	if (meta_data->rot_x_d)
	{
		meta_data->pixel.theta_x -= 0.001;
		if (meta_data->pixel.theta_x < 0)
			meta_data->pixel.theta_x = 2 * M_PI;
		rotate_camera_x(&meta_data->camera->orient, meta_data->pixel.theta_x);
	}
	if (meta_data->rot_y_i)
	{
		meta_data->pixel.theta_y += 0.001;
		if (meta_data->pixel.theta_y > (2 * M_PI))
			meta_data->pixel.theta_y = 0;
		rotate_camera_y(&meta_data->camera->orient, meta_data->pixel.theta_y);
	}
	if (meta_data->rot_y_d)
	{
		meta_data->pixel.theta_y -= 0.001;
		if (meta_data->pixel.theta_y < 0)
			meta_data->pixel.theta_y = 2 * M_PI;
		rotate_camera_y(&meta_data->camera->orient, meta_data->pixel.theta_y);
	}
	if (meta_data->rot_z_i)
	{
		meta_data->pixel.theta_z += 0.001;
		if (meta_data->pixel.theta_z > (2 * M_PI))
			meta_data->pixel.theta_z = 0;
		rotate_camera_z(&meta_data->camera->orient, meta_data->pixel.theta_z);
	}
	if (meta_data->rot_z_d)
	{
		meta_data->pixel.theta_z -= 0.001;
		if (meta_data->pixel.theta_z < 0)
			meta_data->pixel.theta_z = 2 * M_PI;
		rotate_camera_z(&meta_data->camera->orient, meta_data->pixel.theta_z);
	}
	if (meta_data->rot_reset)
	{
		meta_data->pixel.theta_x = 0;
		meta_data->pixel.theta_y = 0;
		meta_data->pixel.theta_z = 0;
		meta_data->camera->orient = meta_data->orient;
	}
}

void    translate_light(t_vector *vector, int key)
{
	if (key == KEY_Q)
		vector->x += 10;
	if (key == KEY_A)
		vector->x -= 10;
	if (key == KEY_W)
		vector->y += 10;
	if (key == KEY_S)
		vector->y -= 10;
	if (key == KEY_E)
		vector->z += 10;
	if (key == KEY_D)
		vector->z -= 10;
}

void    translate_spotlight(t_vector *vector, int key)
{
	if (key == NUMPAD_7)
		vector->x += 10;
	if (key == NUMPAD_8)
		vector->x -= 10;
}

int	ft_close(t_meta *meta_data)
{
	mlx_destroy_window(meta_data->mlx_ptr, meta_data->mlx_win);
	mlx_destroy_image(meta_data->mlx_ptr, meta_data->img);
	// mlx_destroy_display(meta_data->mlx_ptr);
	free(meta_data->mlx_ptr);
	exit(0);
	return (0);
}

void	img_mlx_pixel_put(t_meta *meta_data, int x, int y, int color)
{
	char	*dst;

	if (!(x < 0 || y < 0 || x > WINDOW_WIDTH || y > WINDOW_HEIGHT))
	{
		dst = meta_data->addr + (y * meta_data->line_length + x * \
			(meta_data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void    meta_data_init(t_meta *meta_data)
{
	meta_data->amlight = NULL;
	meta_data->camera = NULL;
	meta_data->pixel.theta_x = 0;
	meta_data->pixel.theta_y = 0;
	meta_data->pixel.theta_z = 0;
	meta_data->light = NULL;
	meta_data->spotlight = NULL;
	meta_data->sp = NULL;
	meta_data->pl = NULL;
	meta_data->cy = NULL;
	meta_data->cn = NULL;
	meta_data->light_allocated = false;
	meta_data->camera_allocated = false;
	meta_data->amlight_allocated = false;
	meta_data->sp_allocated = false;
	meta_data->sl_allocated = false;
	meta_data->pl_allocated = false;
	meta_data->cy_allocated = false;
	meta_data->cn_allocated = false;
	meta_data->row = WINDOW_HEIGHT;
	meta_data->col = WINDOW_WIDTH;
	meta_data->pixel.coeff_ref = 0.5;
	meta_data->pixel.shine_fac = 20;
	meta_data->pixel.spot_theta = 10;
	meta_data->pixel.spot_p = 100;
	meta_data->pixel.spot_k0 = 0.001;
	meta_data->pixel.spot_k1 = 0.0001;
	meta_data->pixel.spot_k2 = 0.00001;
	meta_data->low_quality = false;
	meta_data->mid_quality = false;
}

// void    meta_data_init(t_meta *meta_data)
// {
//     meta_data->amlight = NULL;
//     meta_data->camera = NULL;
//     meta_data->light = NULL;
//     meta_data->sp = NULL;
//     meta_data->pl = NULL;
//     meta_data->cy = NULL;
//     meta_data->cn = NULL;
//     meta_data->light_allocated = false;
//     meta_data->camera_allocated = false;
//     meta_data->amlight_allocated = false;
//     meta_data->sp_allocated = false;
//     meta_data->pl_allocated = false;
//     meta_data->cy_allocated = false;
//     meta_data->cn_allocated = false;
// }

void	parse_data(t_meta *meta_data, int argc, char **argv)
{
	ft_printf(Y"\nPARSING DATA FROM "RST);
	ft_printf("\t%s...\n", argv[1]);
	ft_check_args(argc, argv);
	read_data(meta_data, argv[1]);
	ft_printf(M"PARSING DATA  ...\t\t OK\n"RST);
	meta_data->orient = meta_data->camera->orient;
}

void    read_data(t_meta *meta_data, char *argv)
{
	char    *singleline;
	int     fd;
	int     index;

	fd = get_fd(argv);
	while (1)
	{
		index = 0;
		singleline = get_next_line(fd);
		if (!singleline)
		{
			free(singleline);
			break ;
		}
		if ((ft_strchr(singleline, '\n')))
		{
			while (singleline[index++] != '\n')
				;
			while (index >= 1 && ft_isspace(singleline[index - 1]) > 0)
			{
				singleline[index - 1] = '\0';
				index--;
			}
		}
		if (*singleline && (singleline[0] != '\n') && singleline[0] != '#' && (ft_strlen(singleline) > 0))
			ft_fill_data(meta_data, singleline);
		else
			free(singleline);
	}
}
