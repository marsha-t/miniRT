/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:32:46 by mateo             #+#    #+#             */
/*   Updated: 2024/09/03 16:29:57 by mateo            ###   ########.fr       */
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
		sphere = meta_data->sp;
		while (sphere)
		{
			t = intersect_sp_math(sphere, &meta_data->pixel.shadow,
					&new_origin);
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
			t = intersect_pl_math(plane, &meta_data->pixel.shadow, &new_origin);
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
					&new_origin);
			if (t > 0 && t < len)
				return (true);
			t = intersect_cy_base_math(cylinder, SF_CY_BASE_B,
					&meta_data->pixel.shadow, &new_origin);
			if (t > 0 && t < len)
				return (true);
			t = intersect_cy_base_math(cylinder, SF_CY_BASE_T,
					&meta_data->pixel.shadow, &new_origin);
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
					&new_origin);
			if (t > 0 && t < len)
				return (true);
			t = intersect_cn_base_math(cone, &meta_data->pixel.shadow,
					&new_origin);
			if (t > 0 && t < len)
				return (true);
			cone = cone->next;
		}
	}
	return (false);
}

bool	in_shadow_spotlight(t_meta *meta_data, t_spotlight *spotlight)
{
	t_vector temp;
	t_sp *sphere;
	t_pl *plane;
	t_cy *cylinder;
	t_cn *cone;
	double t;
	double len;
	double	d_attenuation;
	// double theta_rad;
	t_vector new_origin;

	vec_subtract(&meta_data->pixel.shadow_spot, &spotlight->coord,
		&meta_data->pixel.intersect);
	// print_vector("spot coord: ", &spotlight->coord);
	// print_vector("pixel.intersect: ", &meta_data->pixel.intersect);
	// print_vector("shadow_spot: ", &meta_data->pixel.shadow_spot);
	vec_normalise(&meta_data->pixel.shadow_spot);
	vec_subtract(&temp, &spotlight->coord, &meta_data->pixel.intersect);
	len = vec_len(&temp);
	// theta_rad = deg_to_rad(meta_data->pixel.spot_theta);
	// printf("degree %f theta_rad %f\n", meta_data->pixel.spot_theta, theta_rad);
	vec_multiply_scalar(&temp, &spotlight->spot_dir, -1);
	// meta_data->pixel.spot_attenuate = vec_dot_product(&meta_data->pixel.shadow_spot, &spotlight->spot_dir);
	meta_data->pixel.spot_attenuate = fmax(vec_dot_product(&meta_data->pixel.shadow_spot, &temp), 0.0);
	// print_vector("shadow_spot ", &meta_data->pixel.shadow_spot);
	// print_vector("spot_dir ", &spotlight->spot_dir);
	// printf("attenuate %f cos(theta) %f\n", meta_data->pixel.spot_attenuate, cos(theta_rad));
	if (meta_data->pixel.spot_attenuate <= 0)
		return (true);
	// if (cos(theta_rad) > meta_data->pixel.spot_attenuate)
	// 	return (true);
	vec_multiply_scalar(&temp, &meta_data->pixel.normal, 0.001);
	vec_add(&new_origin, &meta_data->pixel.intersect, &temp);
	if (meta_data->sp_allocated && meta_data->sp != NULL)
	{
		// printf("sphere\n");
		sphere = meta_data->sp;
		while (sphere)
		{
			t = intersect_sp_math(sphere, &meta_data->pixel.shadow_spot,
					&new_origin);
			if (t > 0 && t < len)
				return (true);
			sphere = sphere->next;
		}
	}
	if (meta_data->pl_allocated && meta_data->pl != NULL)
	{
		// printf("plane\n");
		plane = meta_data->pl;
		while (plane)
		{
			t = intersect_pl_math(plane, &meta_data->pixel.shadow_spot, &new_origin);
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
			t = intersect_cy_curve_math(cylinder, &meta_data->pixel.shadow_spot,
					&new_origin);
			if (t > 0 && t < len)
				return (true);
			t = intersect_cy_base_math(cylinder, SF_CY_BASE_B,
					&meta_data->pixel.shadow_spot, &new_origin);
			if (t > 0 && t < len)
				return (true);
			t = intersect_cy_base_math(cylinder, SF_CY_BASE_T,
					&meta_data->pixel.shadow_spot, &new_origin);
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
			t = intersect_cn_curve_math(cone, &meta_data->pixel.shadow_spot,
					&new_origin);
			if (t > 0 && t < len)
				return (true);
			t = intersect_cn_base_math(cone, &meta_data->pixel.shadow_spot,
					&new_origin);
			if (t > 0 && t < len)
				return (true);
			cone = cone->next;
		}
	}
	meta_data->pixel.spot_attenuate = pow(meta_data->pixel.spot_attenuate, meta_data->pixel.spot_p);
	d_attenuation = (double)1.0 / (meta_data->pixel.spot_k0 + (meta_data->pixel.spot_k1 * len) + (meta_data->pixel.spot_k2 * len * len));
	meta_data->pixel.spot_intensity = spotlight->brightness * d_attenuation * meta_data->pixel.spot_attenuate;
	return (false);
}