/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:48:30 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/26 12:02:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	free_objects(t_meta *meta_data)
{
	free_spheres(meta_data);
	free_planes(meta_data);
	free_cones(meta_data);
	free_cylinders(meta_data);
	free(meta_data->obj_option);
}

void	free_spheres(t_meta *meta_data)
{
	t_sp	*sp;

	sp = NULL;
	sp = meta_data->sp;
	while (meta_data->sp_allocated && meta_data->sp != NULL)
	{
		sp = sp->next;
		free(meta_data->sp);
		meta_data->sp = NULL;
		meta_data->sp = sp;
	}
}

void	free_planes(t_meta *meta_data)
{
	t_pl	*pl;

	pl = NULL;
	pl = meta_data->pl;
	while (meta_data->pl_allocated && meta_data->pl != NULL)
	{
		pl = pl->next;
		free(meta_data->pl);
		meta_data->pl = NULL;
		meta_data->pl = pl;
	}
}

void	free_cylinders(t_meta *meta_data)
{
	t_cy	*cy;

	cy = NULL;
	cy = meta_data->cy;
	while (meta_data->cy_allocated && meta_data->cy != NULL)
	{
		cy = cy->next;
		free(meta_data->cy);
		meta_data->cy = NULL;
		meta_data->cy = cy;
	}
}

void	free_cones(t_meta *meta_data)
{
	t_cn	*cn;

	cn = NULL;
	cn = meta_data->cn;
	while (meta_data->cn_allocated && meta_data->cn != NULL)
	{
		cn = cn->next;
		free(meta_data->cn);
		meta_data->cn = NULL;
		meta_data->cn = cn;
	}
}
