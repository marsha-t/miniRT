/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:48:37 by mateo             #+#    #+#             */
/*   Updated: 2024/09/25 14:40:44 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
	in_shadow_* checks for intersections between light ray and given object
*/
bool	in_shadow_sp(t_meta *meta_data, t_vector *new_origin, \
	double len, bool check)
{
	t_sp	*sphere;
	double	t;

	sphere = meta_data->sp;
	while (sphere)
	{
		if (!check)
			t = intersect_sp_math(sphere, &meta_data->pixel.shadow, new_origin);
		else
			t = intersect_sp_math(sphere, &meta_data->pixel.shadow_spot, \
				new_origin);
		if (t > 0 && t < len)
			return (true);
		sphere = sphere->next;
	}
	return (false);
}

bool	in_shadow_pl(t_meta *meta_data, t_vector *new_origin, double len, \
	bool check)
{
	t_pl	*plane;
	double	t;

	plane = meta_data->pl;
	while (plane)
	{
		if (!check)
			t = intersect_pl_math(plane, &meta_data->pixel.shadow, new_origin);
		else
			t = intersect_pl_math(plane, &meta_data->pixel.shadow_spot, \
				new_origin);
		if (t > 0 && t < len)
			return (true);
		plane = plane->next;
	}
	return (false);
}

bool	in_shadow_cy(t_meta *meta_data, t_vector *new_origin, double len, \
	bool check)
{
	t_cy	*cylinder;
	double	t;

	cylinder = meta_data->cy;
	while (cylinder)
	{
		t = intersect_cy_curveval(meta_data, new_origin, cylinder, check);
		if (t > 0 && t < len)
			return (true);
		t = intersect_cy_base_math(cylinder, SF_CY_BASE_B,
				&meta_data->pixel.shadow, new_origin);
		if (t > 0 && t < len)
			return (true);
		if (!check)
			t = intersect_cy_base_math(cylinder, SF_CY_BASE_T,
					&meta_data->pixel.shadow, new_origin);
		else
			t = intersect_cy_base_math(cylinder, SF_CY_BASE_T,
					&meta_data->pixel.shadow_spot, new_origin);
		if (t > 0 && t < len)
			return (true);
		cylinder = cylinder->next;
	}
	return (false);
}

double	intersect_cy_curveval(t_meta *meta_data, t_vector *new_origin, \
	t_cy *cylinder, bool check)
{
	double	t;

	if (!check)
		t = intersect_cy_curve_math(cylinder, &meta_data->pixel.shadow, \
			new_origin);
	else
		t = intersect_cy_curve_math(cylinder, &meta_data->pixel.shadow_spot, \
			new_origin);
	return (t);
}

bool	in_shadow_cn(t_meta *meta_data, t_vector *new_origin, double len, \
	bool check)
{
	t_cn	*cone;
	double	t;

	cone = meta_data->cn;
	while (cone)
	{
		if (!check)
			t = intersect_cn_curve_math(cone, &meta_data->pixel.shadow, \
				new_origin);
		else
			t = intersect_cn_curve_math(cone, &meta_data->pixel.shadow_spot, \
				new_origin);
		if (t > 0 && t < len)
			return (true);
		t = intersect_cn_base_math(cone, &meta_data->pixel.shadow, new_origin);
		if (t > 0 && t < len)
			return (true);
		cone = cone->next;
	}
	return (false);
}
