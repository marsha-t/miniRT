/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:32:46 by mateo             #+#    #+#             */
/*   Updated: 2024/08/22 12:16:54 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	in_shadow checks whether intersection point is in shadow
	- returns true if valid intersection with any object
	- returns false otherwise */
bool	in_shadow(t_meta *meta_data, t_light *light)
{
	t_vector temp;
	t_sp *sphere;
	t_pl *plane;
	t_cy *cylinder;
	t_cn *cone;
	double t;
	double len;

	vec_subtract(&meta_data->pixel.shadow, &light->coord,
		&meta_data->pixel.intersect);
	vec_normalise(&meta_data->pixel.shadow);
	vec_subtract(&temp, &light->coord, &meta_data->pixel.intersect);
	len = vec_len(&temp);
	if (meta_data->sp_allocated && meta_data->sp != NULL)
	{
		sphere = meta_data->sp;
		while (sphere)
		{
			t = intersect_sp_math(sphere, &meta_data->pixel.shadow,
					&meta_data->pixel.intersect);
			if (t > 0 && t < len)
				return (true);
			sphere = sphere->next;
		}
	}
	if (meta_data->pl_allocated && meta_data->pl != NULL)
	{
		plane = meta_data->pl;
		while (plane)
		{
			t = intersect_pl_math(plane, &meta_data->pixel.shadow,
					&meta_data->pixel.intersect);
			if (t > 0 && t < len)
				return (true);
			plane = plane->next;
		}
	}
	if (meta_data->cy_allocated && meta_data->cy != NULL)
	{
		cylinder = meta_data->cy;
		while (cylinder)
		{
			t = intersect_cy_curve_math(cylinder, &meta_data->pixel.shadow,
					&meta_data->pixel.intersect);
			if (t > 0 && t < len)
				return (true);
			t = intersect_cy_base_math(cylinder, SF_CY_BASE_B,
					&meta_data->pixel.shadow, &meta_data->pixel.intersect);
			if (t > 0 && t < len)
				return (true);
			t = intersect_cy_base_math(cylinder, SF_CY_BASE_T,
					&meta_data->pixel.shadow, &meta_data->pixel.intersect);
			if (t > 0 && t < len)
				return (true);
			cylinder = cylinder->next;
		}
	}
	if (meta_data->cn_allocated && meta_data->cn != NULL)
	{
		cone = meta_data->cn;
		while (cone)
		{
			t = intersect_cn_curve_math(cone, &meta_data->pixel.shadow,
					&meta_data->pixel.intersect);
			if (t > 0 && t < len)
				return (true);
			t = intersect_cn_base_math(cone, &meta_data->pixel.shadow,
					&meta_data->pixel.intersect);
			if (t > 0 && t < len)
				return (true);
			cone = cone->next;
		}
	}
	return (false);
}