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
    print_spotlight(&meta_data);
    // prepare_data(&meta_data);
    // gen_img(&meta_data);
    // print_light(&meta_data);
    // print_planes(&meta_data);
    // print_spheres(&meta_data);
    // print_cones(&meta_data);
    // print_cylinders(&meta_data);
    mlx_put_image_to_window(meta_data.mlx_ptr, meta_data.mlx_win, meta_data.img, 0, 0);
	mlx_hook(meta_data.mlx_win, 2, 1L << 0, ft_key, &meta_data);
    mlx_hook(meta_data.mlx_win, 17, 0, ft_close, &meta_data);
    mlx_loop(meta_data.mlx_ptr);
    ft_close(&meta_data);
    free_exit(&meta_data);
    return (1);
}

// void    copy_img(t_meta *meta_data)
// {
    
// }

// void    restore_img(t_meta *meta_data)
// {

// }

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
    // if (meta_data->mlx_win)
    // {
    //     mlx_destroy_window(meta_data->mlx_ptr, meta_data->mlx_win);
    // }
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

/*	ft_key directs specific keypresses to various actions
	- close
*/
int	ft_key(int key, void *param)
{
	t_meta *meta_data;

	meta_data = (t_meta *)param;
	if (key == KEY_ESC)
		ft_close(meta_data);
    else if (key == NUMPAD_0)
        printf("NUMPAD 0\n");
    else if (key == NUMPAD_1)
    {
        printf("NUMPAD 1\n");
        translate_camera(&meta_data->camera->coord, key);
    }
    else if (key == NUMPAD_2)
    {
        printf("NUMPAD 2\n");
        translate_camera(&meta_data->camera->coord, key);
    }
    else if (key == NUMPAD_3)
    {
        printf("NUMPAD 3\n");
        translate_camera(&meta_data->camera->coord, key);
    }
    else if (key == NUMPAD_4)
    {
        printf("NUMPAD 4\n");
        translate_camera(&meta_data->camera->coord, key);
    }
    else if (key == NUMPAD_5)
    {
        printf("NUMPAD 5\n");
        translate_camera(&meta_data->camera->coord, key);
    }
    else if (key == NUMPAD_6)
    {
        printf("NUMPAD 6\n");
        translate_camera(&meta_data->camera->coord, key);
    }
    else if (key == NUMPAD_7)
        printf("NUMPAD 7\n");
    else if (key == NUMPAD_8)
        printf("NUMPAD 8\n");
    else if (key == NUMPAD_9)
        printf("NUMPAD 9\n");
    else if (key == KEY_Q)
    {
        printf("Q\n");
        translate_light(&meta_data->light->coord, key);
    }
    else if (key == KEY_A)
    {
        printf("A\n");
        translate_light(&meta_data->light->coord, key);
    }
    else if (key == KEY_W)
    {
        printf("W\n");
        translate_light(&meta_data->light->coord, key);
    }
    else if (key == KEY_S)
    {
        printf("S\n");
        translate_light(&meta_data->light->coord, key);
    }
    else if (key == KEY_E)
    {
        printf("E\n");
        translate_light(&meta_data->light->coord, key);
    }
    else if (key == KEY_D)
    {
        printf("D\n");
        translate_light(&meta_data->light->coord, key);
    }
    else
    {
        printf("none %d\n", key);
    }
    mlx_clear_window(meta_data->mlx_ptr, meta_data->mlx_win);
    draw(meta_data);
    mlx_put_image_to_window(meta_data->mlx_ptr, meta_data->mlx_win, meta_data->img, 0, 0);
	return (0);
}

void    translate_camera(t_vector *vector, int key)
{
    if (key == NUMPAD_4)
        vector->x += 10;
    if (key == NUMPAD_1)
        vector->x -= 10;
    if (key == NUMPAD_5)
        vector->y += 10;
    if (key == NUMPAD_2)
        vector->y -= 10;
    if (key == NUMPAD_6)
        vector->z += 10;
    if (key == NUMPAD_3)
        vector->z -= 10;
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
    meta_data->light = NULL;
    meta_data->sp = NULL;
    meta_data->pl = NULL;
    meta_data->cy = NULL;
    meta_data->cn = NULL;
    meta_data->light_allocated = false;
    meta_data->camera_allocated = false;
    meta_data->amlight_allocated = false;
    meta_data->sp_allocated = false;
    meta_data->pl_allocated = false;
    meta_data->cy_allocated = false;
    meta_data->cn_allocated = false;
    meta_data->row = WINDOW_HEIGHT;
    meta_data->col = WINDOW_WIDTH;
    meta_data->pixel.coeff_ref = 0.5;
    meta_data->pixel.shine_fac = 20;
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
        // ft_printf("single line %s\n", singleline);
        while (singleline[index++] != '\n')
            ;
        while (index >= 1 && ft_isspace(singleline[index - 1]) > 0)
        {
            singleline[index - 1] = '\0';
            index--;
        }
        // ft_printf("single line %s\n", singleline);
        if (*singleline && (singleline[0] != '\n') && singleline[0] != '#' && (ft_strlen(singleline) > 0))
            ft_fill_data(meta_data, singleline);
        else
            free(singleline);
    }
}
