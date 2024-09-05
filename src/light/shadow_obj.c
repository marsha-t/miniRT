/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:48:37 by mateo             #+#    #+#             */
/*   Updated: 2024/09/05 15:14:34 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
	in_shadow_* checks for intersections between light ray and given object
*/
bool	in_shadow_sp(t_meta *meta_data, t_vector *new_origin, double len)
{
	t_sp	*sphere;
	double	t;

	sphere = meta_data->sp;
	while (sphere)
	{
		t = intersect_sp_math(sphere, &meta_data->pixel.shadow, new_origin);
		if (t > 0 && t < len)
			return (true);
		sphere = sphere->next;
	}
	return (false);
}

bool	in_shadow_pl(t_meta *meta_data, t_vector *new_origin, double len)
{
	t_pl	*plane;
	double	t;

	plane = meta_data->pl;
	while (plane)
	{
		t = intersect_pl_math(plane, &meta_data->pixel.shadow, new_origin);
		if (t > 0 && t < len)
			return (true);
		plane = plane->next;
	}
	return (false);
}

bool	in_shadow_cy(t_meta *meta_data, t_vector *new_origin, double len)
{
	t_cy	*cylinder;
	double	t;

	cylinder = meta_data->cy;
	while (cylinder)
	{
		t = intersect_cy_curve_math(cylinder, &meta_data->pixel.shadow_spot,
				new_origin);
		if (t > 0 && t < len)
			return (true);
		t = intersect_cy_base_math(cylinder, SF_CY_BASE_B,
				&meta_data->pixel.shadow_spot, new_origin);
		if (t > 0 && t < len)
			return (true);
		t = intersect_cy_base_math(cylinder, SF_CY_BASE_T,
				&meta_data->pixel.shadow_spot, new_origin);
		if (t > 0 && t < len)
			return (true);
		cylinder = cylinder->next;
	}
	return (false);
}

bool	in_shadow_cn(t_meta *meta_data, t_vector *new_origin, double len)
{
	t_cn	*cone;
	double	t;

	cone = meta_data->cn;
	while (cone)
	{
		t = intersect_cn_curve_math(cone, &meta_data->pixel.shadow, new_origin);
		if (t > 0 && t < len)
			return (true);
		t = intersect_cn_base_math(cone, &meta_data->pixel.shadow, new_origin);
		if (t > 0 && t < len)
			return (true);
		cone = cone->next;
	}
	return (false);
}
