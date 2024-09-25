/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:51:15 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/25 19:53:28 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	navigate_cy(t_meta *meta_data, int key)
{
	t_cy		*cy;

	cy = NULL;
	if (meta_data->obj_select == 2 && key == NUMPAD_5)
	{
		cy = (t_cy *)meta_data->obj;
		meta_data->obj_option->coord = &cy->coord;
		meta_data->obj_option->size = &cy->diameter;
		meta_data->obj_option->size_a = &cy->height;
		meta_data->obj_option->orient = &cy->axis;
		if (cy->next != NULL)
			meta_data->obj = (void *)cy->next;
		else
			meta_data->obj = (void *)meta_data->cy;
	}
	navigate_cn(meta_data, key);
}

void	navigate_cn(t_meta *meta_data, int key)
{
	t_cn		*cn;

	if (meta_data->obj_select == 4 && key == NUMPAD_5)
	{
		cn = (t_cn *)meta_data->obj;
		meta_data->obj_option->coord = &cn->coord;
		meta_data->obj_option->size = &cn->height;
		meta_data->obj_option->size_a = &cn->radius;
		meta_data->obj_option->orient = &cn->axis;
		if (cn->next != NULL)
			meta_data->obj = (void *)cn->next;
		else
			meta_data->obj = (void *)meta_data->cn;
	}
}

void	navigate_light(t_meta *meta_data, int key)
{
	t_light		*light;
	t_spotlight	*spotlight;

	light = NULL;
	spotlight = NULL;
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

void	navigate_sppl(t_meta *meta_data, int key)
{
	t_sp		*sp;
	t_pl		*pl;

	sp = NULL;
	pl = NULL;
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
	if (meta_data->obj_select == 3 && key == NUMPAD_5)
	{
		pl = (t_pl *)meta_data->obj;
		meta_data->obj_option->coord = &pl->coord;
		meta_data->obj_option->orient = &pl->normal;
		if (pl->next != NULL)
			meta_data->obj = (void *)pl->next;
		else
			meta_data->obj = (void *)meta_data->pl;
	}
}
