/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_select.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:50:31 by emaravil          #+#    #+#             */
/*   Updated: 2024/10/02 11:23:40 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	ft_objectselect(t_meta *meta_data, int key)
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
		meta_data->obj_option->size_a = &meta_data->cy->height;
		meta_data->obj_option->orient = &meta_data->cy->axis;
		meta_data->orient = meta_data->cy->axis;
		meta_data->obj_select = 2;
	}
	object_select_a(meta_data, key);
}

void	object_select_a(t_meta *meta_data, int key)
{
	if (key == KEY_5 && meta_data->light_allocated)
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
	object_select_b(meta_data, key);
}

void	object_select_b(t_meta *meta_data, int key)
{
	if (key == KEY_4 && meta_data->cn_allocated)
	{
		printf(Y"CONE SELECTED\n"RST);
		meta_data->obj = (void *)meta_data->cn;
		meta_data->obj_option->coord = &meta_data->cn->coord;
		meta_data->obj_option->size = &meta_data->cn->radius;
		meta_data->obj_option->size_a = &meta_data->cn->height;
		meta_data->obj_option->orient = &meta_data->cn->axis;
		meta_data->orient = meta_data->cn->axis;
		meta_data->obj_select = 4;
	}
	else if (key == KEY_7 && meta_data->camera_allocated)
	{
		printf(Y"CAMERA SELECTED\n"RST);
		meta_data->obj = (void *)meta_data->camera;
		meta_data->obj_option->coord = &meta_data->camera->coord;
		meta_data->obj_option->size = &meta_data->camera->fov;
		meta_data->obj_option->orient = &meta_data->camera->orient;
		meta_data->orient = meta_data->camera->orient;
		meta_data->obj_select = 7;
	}
	object_select_c(meta_data, key);
}

void	object_select_c(t_meta *meta_data, int key)
{
	if (key == KEY_3 && meta_data->pl_allocated)
	{
		printf(Y"PLANE SELECTED\n"RST);
		meta_data->obj = (void *)meta_data->pl;
		meta_data->obj_option->coord = &meta_data->pl->coord;
		meta_data->obj_option->orient = &meta_data->pl->normal;
		meta_data->orient = meta_data->pl->normal;
		meta_data->obj_select = 3;
	}
}
