/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:49:37 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/11 18:58:16 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	init_sphere(t_meta *meta_data, char **argv)
{
	static int	sp;
	t_sp		*temp_sp;

	if (sp == 0)
	{
		meta_data->sp = create_sp(meta_data, argv);
		meta_data->sp_allocated = true;
	}
	else
	{
		temp_sp = meta_data->sp;
		while (temp_sp->next != NULL)
			temp_sp = temp_sp->next;
		temp_sp->next = create_sp(meta_data, argv);
	}
	sp++;
}

void	init_plane(t_meta *meta_data, char **argv)
{
	static int	pl;
	t_pl		*temp_pl;

	if (pl == 0)
	{
		meta_data->pl = create_pl(meta_data, argv);
		meta_data->pl_allocated = true;
	}
	else
	{
		temp_pl = meta_data->pl;
		while (temp_pl->next != NULL)
			temp_pl = temp_pl->next;
		temp_pl->next = create_pl(meta_data, argv);
	}
	pl++;
}

void	init_cylinder(t_meta *meta_data, char **argv)
{
	static int	cy;
	t_cy		*temp_cy;

	if (cy == 0)
	{
		meta_data->cy = create_cy(meta_data, argv);
		meta_data->cy_allocated = true;
	}
	else
	{
		temp_cy = meta_data->cy;
		while (temp_cy->next != NULL)
			temp_cy = temp_cy->next;
		temp_cy->next = create_cy(meta_data, argv);
	}
	cy++;
}

void	init_cone(t_meta *meta_data, char **argv)
{
	static int	cn;
	t_cn		*temp_cn;

	if (cn == 0)
	{
		meta_data->cn = create_cn(meta_data, argv);
		meta_data->cn_allocated = true;
	}
	else
	{
		temp_cn = meta_data->cn;
		while (temp_cn->next != NULL)
			temp_cn = temp_cn->next;
		temp_cn->next = create_cn(meta_data, argv);
	}
	cn++;
}
