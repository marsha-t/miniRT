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

int main(int argc, char **argv)
{
	t_meta meta_data;

	print_banner();
	meta_data_init(&meta_data);
	parse_data(&meta_data, argc, argv);
	rt_mlxinit(&meta_data);
	draw(&meta_data);
	mlx_put_image_to_window(meta_data.mlx_ptr, meta_data.mlx_win, meta_data.img, 0, 0);
	// print_spotlight(&meta_data);
	// prepare_data(&meta_data);
	// gen_img(&meta_data);
	// print_light(&meta_data);
	// print_planes(&meta_data);
	// print_spheres(&meta_data);
	// print_cones(&meta_data);
	// print_cylinders(&meta_data);
	mlx_hook(meta_data.mlx_win, 2, 1L << 0, ft_key, &meta_data);
	mlx_hook(meta_data.mlx_win, 17, 0, ft_close, &meta_data);
	mlx_loop(meta_data.mlx_ptr);
	ft_close(&meta_data);
	free_exit(&meta_data);
	return (1);
}

void    draw(t_meta *meta_data)
{
	prepare_data(meta_data);
	gen_img(meta_data);
}

void    rt_mlxinit(t_meta *meta_data)
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
	double cos_theta;
	double sin_theta;
	double new_x;
	double new_z;

	cos_theta = cos(theta_y);
	sin_theta = sin(theta_y);
	new_x = (cos_theta * orientation->x) + (sin_theta * orientation->z);
	new_z = (-sin_theta * orientation->x) + (cos_theta * orientation->z);
	orientation->x = new_x;
	orientation->z = new_z;
	// orientation->y = 1;
}

void	rotate_camera_x(t_vector *orientation, double theta_x)
{
	double cos_theta;
	double sin_theta;
	double new_y;
	double new_z;

	cos_theta = cos(theta_x);
	sin_theta = sin(theta_x);
	new_y = (cos_theta * orientation->y) - (sin_theta * orientation->z);
	new_z = (sin_theta * orientation->y) + (cos_theta * orientation->z);
	orientation->y = new_y;
	orientation->z = new_z;
	// orientation->x = 1;
}

void	rotate_camera_z(t_vector *orientation, double theta_z)
{
	double cos_theta;
	double sin_theta;
	double new_x;
	double new_y;

	cos_theta = cos(theta_z);
	sin_theta = sin(theta_z);
	new_x = (cos_theta * orientation->x) - (sin_theta * orientation->y);
	new_y = (sin_theta * orientation->x) + (cos_theta * orientation->y);
	orientation->x = new_x;
	orientation->y = new_y;
	// orientation->z = 1;
}

void ft_controls(t_meta *meta_data, int key)
{
	t_vector *vector;

	vector = meta_data->obj_option->coord;
	printf("vector x: %f y: %f z: %f\n", vector->x, vector->y, vector->z);
	printf("camera x: %f y: %f z: %f\n", meta_data->camera->coord.x, meta_data->camera->coord.y, meta_data->camera->coord.z);
	if (key == NUMPAD_8)
		vector->y += 5;
	if (key == NUMPAD_2)
		vector->y -= 5;
	if (key == NUMPAD_4)
		vector->x -= 5;
	if (key == NUMPAD_6)
		vector->x += 5;
	if (key == NUMPAD_PLUS)
		vector->z += 5;
	if (key == NUMPAD_MIN)
		vector->z -= 5;
}

void ft_objectselect(t_meta *meta_data, int key)
{

	if (key == KEY_1 && meta_data->sp_allocated)
	{
		meta_data->obj = (void *)meta_data->sp;
		meta_data->obj_option->coord = &meta_data->sp->coord;
		meta_data->obj_option->size = &meta_data->sp->diameter;
		meta_data->obj_select = 1;
	}
	if (key == KEY_2 && meta_data->cy_allocated)
	{
		meta_data->obj = (void *)meta_data->cy;
		meta_data->obj_option->coord = &meta_data->cy->coord;
		meta_data->obj_option->size = &meta_data->cy->diameter;
		meta_data->obj_select = 2;
	}
	if (key == KEY_3 && meta_data->pl_allocated)
	{
		meta_data->obj = (void *)meta_data->pl;
		meta_data->obj_option->coord = &meta_data->pl->coord;
		meta_data->obj_select = 3;
	}
	if (key == KEY_4 && meta_data->cn_allocated)
	{
		meta_data->obj = (void *)meta_data->cn;
		meta_data->obj_option->coord = &meta_data->cn->coord;
		meta_data->obj_option->size = &meta_data->cn->height;
		meta_data->obj_select = 4;
	}
	if (key == KEY_5 && meta_data->light_allocated)
	{
		meta_data->obj = (void *)meta_data->light;
		meta_data->obj_option->coord = &meta_data->light->coord;
		meta_data->obj_option->size = &meta_data->light->brightness;
		meta_data->obj_select = 5;
	}
	if (key == KEY_6 && meta_data->sl_allocated)
	{
		meta_data->obj = (void *)meta_data->spotlight;
		meta_data->obj_option->coord = &meta_data->spotlight->coord;
		meta_data->obj_option->size = &meta_data->spotlight->brightness;
		meta_data->obj_select = 6;
	}
	if (key == KEY_7 && meta_data->camera_allocated)
	{
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
	printf("size: %f\n", *meta_data->obj_option->size);
}

/*	ft_key directs specific keypresses to various actions
	- close
*/
int	ft_key(int key, void *param)
{
	t_meta *meta_data;

	printf("key: %d\n", key);
	meta_data = (t_meta *)param;
	ft_controls(meta_data, key);
	ft_objectselect(meta_data, key);
	navigate(meta_data, key);
	increase_size(meta_data, key);
	if (meta_data->obj_select == 7)
		translate_camera(meta_data, key);
	mlx_clear_window(meta_data->mlx_ptr, meta_data->mlx_win);
	draw(meta_data);
	mlx_put_image_to_window(meta_data->mlx_ptr, meta_data->mlx_win, meta_data->img, 0, 0);
	return (0);
}

void    translate_camera(t_meta *meta_data, int key)
{
	if (key == KEY_U)
	{
		meta_data->pixel.theta_x += 0.001;
		rotate_camera_x(&meta_data->camera->orient, meta_data->pixel.theta_x);
	}
	if (key == KEY_J)
	{
		meta_data->pixel.theta_x -= 0.001;
		rotate_camera_x(&meta_data->camera->orient, meta_data->pixel.theta_x);
	}
	if (key == KEY_I)
	{
		meta_data->pixel.theta_y += 0.001;
		rotate_camera_y(&meta_data->camera->orient, meta_data->pixel.theta_y);
	}
	if (key == KEY_K)
	{
		meta_data->pixel.theta_y -= 0.001;
		rotate_camera_y(&meta_data->camera->orient, meta_data->pixel.theta_y);
	}
	if (key == KEY_O)
	{
		meta_data->pixel.theta_z += 0.001;
		rotate_camera_z(&meta_data->camera->orient, meta_data->pixel.theta_z);
	}
	if (key == KEY_L)
	{
		meta_data->pixel.theta_z -= 0.001;
		rotate_camera_z(&meta_data->camera->orient, meta_data->pixel.theta_z);
	}
	if (key == KEY_R)
	{
		meta_data->pixel.theta_x = 0;
		meta_data->pixel.theta_y = 0;
		meta_data->pixel.theta_z = 0;
		meta_data->camera->orient = meta_data->orient;
	}
	printf("theta x: %f y: %f z: %f\n", meta_data->pixel.theta_x, meta_data->pixel.theta_y, meta_data->pixel.theta_z);
	printf("orientation x: %f y: %f z: %f\n", meta_data->camera->orient.x, meta_data->camera->orient.y, meta_data->camera->orient.z);
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
