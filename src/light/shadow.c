/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:32:46 by mateo             #+#    #+#             */
/*   Updated: 2024/09/03 16:41:50 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

bool	in_shadow_sp(t_meta *meta_data, t_vector *new_origin, double len)
{
	t_sp	*sphere;
	double	t;

	sphere = meta_data->sp;
	while (sphere)
	{
		t = intersect_sp_math(sphere, &meta_data->pixel.shadow,
				new_origin);
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
	t_cy *cylinder;
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
	cone = meta_data->cn;
	while (cone)
	{
		t = intersect_cn_curve_math(cone, &meta_data->pixel.shadow,
				&new_origin);
		if (t > 0 && t < len)
			return (true);
		t = intersect_cn_base_math(cone, &meta_data->pixel.shadow,
				&new_origin);
		if (t > 0 && t < len)
			return (true);
		cone = cone->next;
	}
	return (false);
}

/*	in_shadow checks whether intersection point is in shadow
	- returns true if valid intersection with any object
	- returns false otherwise */
bool	in_shadow(t_meta *meta_data, t_light *light)
{
	t_vector temp;
	// t_sp *sphere;
	// t_pl *plane;
	// t_cy *cylinder;
	// t_cn *cone;
	// double t;
	double len;
	t_vector new_origin;

	vec_subtract(&meta_data->pixel.shadow, &light->coord,
		&meta_data->pixel.intersect);
	vec_normalise(&meta_data->pixel.shadow);
	vec_subtract(&temp, &light->coord, &meta_data->pixel.intersect);
	len = vec_len(&temp);
	vec_multiply_scalar(&temp, &meta_data->pixel.normal, 0.001);
	vec_add(&new_origin, &meta_data->pixel.intersect, &temp);
	if (meta_data->sp_allocated && meta_data->sp != NULL)
	{
		if (in_shadow_sp(meta_data, &new_origin, len) == true)
			return (true);
		// sphere = meta_data->sp;
		// while (sphere)
		// {
		// 	t = intersect_sp_math(sphere, &meta_data->pixel.shadow,
		// 			&new_origin);
		// 	if (t > 0 && t < len)
		// 		return (true);
		// 	sphere = sphere->next;
		// }
	}
	if (meta_data->pl_allocated && meta_data->pl != NULL)
	{
		if (in_shadow_pl(meta_data, &new_origin, len) == true)
			return (true);
		// plane = meta_data->pl;
		// while (plane)
		// {
		// 	t = intersect_pl_math(plane, &meta_data->pixel.shadow, &new_origin);
		// 	if (t > 0 && t < len)
		// 		return (true);
		// 	plane = plane->next;
		// }
	}
	if (meta_data->cy_allocated && meta_data->cy != NULL)
	{
		if (in_shadow_cy(meta_data, &new_origin, len) == true)
			return (true);
		// cylinder = meta_data->cy;
		// while (cylinder)
		// {
		// 	t = intersect_cy_curve_math(cylinder, &meta_data->pixel.shadow,
		// 			&new_origin);
		// 	if (t > 0 && t < len)
		// 		return (true);
		// 	t = intersect_cy_base_math(cylinder, SF_CY_BASE_B,
		// 			&meta_data->pixel.shadow, &new_origin);
		// 	if (t > 0 && t < len)
		// 		return (true);
		// 	t = intersect_cy_base_math(cylinder, SF_CY_BASE_T,
		// 			&meta_data->pixel.shadow, &new_origin);
		// 	if (t > 0 && t < len)
		// 		return (true);
		// 	cylinder = cylinder->next;
		// }
	}
	if (meta_data->cn_allocated && meta_data->cn != NULL)
	{
		if (in_shadow_cn(meta_data, &new_origin, len) == true)
			return (true);
		// cone = meta_data->cn;
		// while (cone)
		// {
		// 	t = intersect_cn_curve_math(cone, &meta_data->pixel.shadow,
		// 			&new_origin);
		// 	if (t > 0 && t < len)
		// 		return (true);
		// 	t = intersect_cn_base_math(cone, &meta_data->pixel.shadow,
		// 			&new_origin);
		// 	if (t > 0 && t < len)
		// 		return (true);
		// 	cone = cone->next;
		// }
	}
	return (false);
}

bool	in_shadow_spotlight(t_meta *meta_data, t_spotlight *spotlight)
{
	t_vector temp;
	// t_sp *sphere;
	// t_pl *plane;
	// t_cy *cylinder;
	// t_cn *cone;
	// double t;
	double len;
	double	d_attenuation;
	t_vector new_origin;

	vec_subtract(&meta_data->pixel.shadow_spot, &spotlight->coord,
		&meta_data->pixel.intersect);
	vec_normalise(&meta_data->pixel.shadow_spot);
	vec_subtract(&temp, &spotlight->coord, &meta_data->pixel.intersect);
	len = vec_len(&temp);
	vec_multiply_scalar(&temp, &spotlight->spot_dir, -1);
	meta_data->pixel.spot_attenuate = fmax(vec_dot_product(&meta_data->pixel.shadow_spot, &temp), 0.0);
	if (meta_data->pixel.spot_attenuate <= 0)
		return (true);
	vec_multiply_scalar(&temp, &meta_data->pixel.normal, 0.001);
	vec_add(&new_origin, &meta_data->pixel.intersect, &temp);
	if (meta_data->sp_allocated && meta_data->sp != NULL)
	{
		if (in_shadow_sp(meta_data, &new_origin, len) == true)
			return (true);
		// sphere = meta_data->sp;
		// while (sphere)
		// {
		// 	t = intersect_sp_math(sphere, &meta_data->pixel.shadow_spot,
		// 			&new_origin);
		// 	if (t > 0 && t < len)
		// 		return (true);
		// 	sphere = sphere->next;
		// }
	}
	if (meta_data->pl_allocated && meta_data->pl != NULL)
	{
		if (in_shadow_pl(meta_data, &new_origin, len) == true)
			return (true);
		// plane = meta_data->pl;
		// while (plane)
		// {
		// 	t = intersect_pl_math(plane, &meta_data->pixel.shadow_spot, &new_origin);
		// 	if (t > 0 && t < len)
		// 		return (true);
		// 	plane = plane->next;
		// }
	}
	if (meta_data->cy_allocated && meta_data->cy != NULL)
	{
		if (in_shadow_cy(meta_data, &new_origin, len) == true)
			return (true);
		// cylinder = meta_data->cy;
		// while (cylinder)
		// {
		// 	t = intersect_cy_curve_math(cylinder, &meta_data->pixel.shadow_spot,
		// 			&new_origin);
		// 	if (t > 0 && t < len)
		// 		return (true);
		// 	t = intersect_cy_base_math(cylinder, SF_CY_BASE_B,
		// 			&meta_data->pixel.shadow_spot, &new_origin);
		// 	if (t > 0 && t < len)
		// 		return (true);
		// 	t = intersect_cy_base_math(cylinder, SF_CY_BASE_T,
		// 			&meta_data->pixel.shadow_spot, &new_origin);
		// 	if (t > 0 && t < len)
		// 		return (true);
		// 	cylinder = cylinder->next;
		// }
	}
	if (meta_data->cn_allocated && meta_data->cn != NULL)
	{
		if (in_shadow_cn(meta_data, &new_origin, len) == true)
			return (true);
		// cone = meta_data->cn;
		// while (cone)
		// {
		// 	t = intersect_cn_curve_math(cone, &meta_data->pixel.shadow_spot,
		// 			&new_origin);
		// 	if (t > 0 && t < len)
		// 		return (true);
		// 	t = intersect_cn_base_math(cone, &meta_data->pixel.shadow_spot,
		// 			&new_origin);
		// 	if (t > 0 && t < len)
		// 		return (true);
		// 	cone = cone->next;
		// }
	}
	meta_data->pixel.spot_attenuate = pow(meta_data->pixel.spot_attenuate, meta_data->pixel.spot_p);
	d_attenuation = (double)1.0 / (meta_data->pixel.spot_k0 + (meta_data->pixel.spot_k1 * len) + (meta_data->pixel.spot_k2 * len * len));
	meta_data->pixel.spot_intensity = spotlight->brightness * d_attenuation * meta_data->pixel.spot_attenuate;
	return (false);
}
