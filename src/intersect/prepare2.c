/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:32:29 by mateo             #+#    #+#             */
/*   Updated: 2024/09/05 17:32:47 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	prepare_obj adds derived parameters to object structs*/
void	prepare_obj(t_meta *meta_data)
{
	if (meta_data->sp)
		prepare_sp(meta_data->sp);
	if (meta_data->pl)
		prepare_pl(meta_data->pl);
	if (meta_data->cy)
		prepare_cy(meta_data->cy);
	if (meta_data->cn)
		prepare_cn(meta_data->cn);
}

/*	prepare_sp adds derived parameters to sphere nodes
	- normalise colour
	- add radius */
void	prepare_sp(t_sp *start)
{
	t_sp	*curr;

	curr = start;
	while (curr)
	{
		curr->radius = curr->diameter / 2;
		curr->colour.r_n = curr->colour.r / 255;
		curr->colour.g_n = curr->colour.g / 255;
		curr->colour.b_n = curr->colour.b / 255;
		curr = curr->next;
	}
}

/*	prepare_pl adds derived parameters to plane nodes
	- normalise colours */
void	prepare_pl(t_pl *start)
{
	t_pl	*curr;

	curr = start;
	while (curr)
	{
		curr->colour.r_n = curr->colour.r / 255;
		curr->colour.g_n = curr->colour.g / 255;
		curr->colour.b_n = curr->colour.b / 255;
		curr = curr->next;
	}
}

/*	prepare_cy adds derived parameters to cylinder nodes
	- normalise colours
	- centers of bottom and top base of cylinder
	- radius
	*/
void	prepare_cy(t_cy *start)
{
	t_cy		*curr;
	t_vector	temp;

	curr = start;
	while (curr)
	{
		vec_multiply_scalar(&temp, &curr->axis, curr->height / 2);
		vec_subtract(&curr->base_bottom, &curr->coord, &temp);
		vec_add(&curr->base_top, &curr->coord, &temp);
		curr->colour.r_n = curr->colour.r / 255;
		curr->colour.g_n = curr->colour.g / 255;
		curr->colour.b_n = curr->colour.b / 255;
		curr->radius = curr->diameter / 2;
		curr = curr->next;
	}
}

/*	prepare_cn adds derived parameters to cone nodes
	- normalise colours
	- radius of base
	- base center
	*/
void	prepare_cn(t_cn *start)
{
	t_cn		*curr;
	t_vector	temp;

	curr = start;
	while (curr)
	{
		curr->angle = curr->angle * (M_PI / 180);
		curr->radius = curr->height * tan(curr->angle);
		vec_multiply_scalar(&temp, &curr->axis, curr->height);
		vec_add(&curr->base, &curr->coord, &temp);
		curr->colour.r_n = curr->colour.r / 255;
		curr->colour.g_n = curr->colour.g / 255;
		curr->colour.b_n = curr->colour.b / 255;
		curr = curr->next;
	}
}
