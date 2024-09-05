/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:32:46 by mateo             #+#    #+#             */
/*   Updated: 2024/09/05 15:14:10 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	in_shadow checks whether intersection point is in shadow
	- returns true if valid intersection with any object
	- returns false otherwise */
bool	in_shadow(t_meta *meta_data, t_light *light)
{
	t_vector	temp;
	double		len;
	t_vector	new_origin;

	vec_subtract(&meta_data->pixel.shadow, &light->coord,
		&meta_data->pixel.intersect);
	vec_normalise(&meta_data->pixel.shadow);
	vec_subtract(&temp, &light->coord, &meta_data->pixel.intersect);
	len = vec_len(&temp);
	vec_multiply_scalar(&temp, &meta_data->pixel.normal, 0.001);
	vec_add(&new_origin, &meta_data->pixel.intersect, &temp);
	if (meta_data->sp_allocated && meta_data->sp != NULL
		&& in_shadow_sp(meta_data, &new_origin, len) == true)
		return (true);
	if (meta_data->pl_allocated && meta_data->pl != NULL
		&& in_shadow_pl(meta_data, &new_origin, len) == true)
		return (true);
	if (meta_data->cy_allocated && meta_data->cy != NULL
		&& in_shadow_cy(meta_data, &new_origin, len) == true)
		return (true);
	if (meta_data->cn_allocated && meta_data->cn != NULL
		&& in_shadow_cn(meta_data, &new_origin, len) == true)
		return (true);
	return (false);
}

bool	in_shadow_spotlight_setup(t_meta *meta_data, t_spotlight *spotlight,
		double *len, t_vector *new_origin)
{
	t_vector	temp;
	double		d_attenuation;

	vec_subtract(&meta_data->pixel.shadow_spot, &spotlight->coord,
		&meta_data->pixel.intersect);
	vec_normalise(&meta_data->pixel.shadow_spot);
	vec_subtract(&temp, &spotlight->coord, &meta_data->pixel.intersect);
	*len = vec_len(&temp);
	vec_multiply_scalar(&temp, &spotlight->spot_dir, -1);
	meta_data->pixel.spot_attenuate = \
		fmax(vec_dot_product(&meta_data->pixel.shadow_spot,
				&temp), 0.0);
	if (meta_data->pixel.spot_attenuate <= 0)
		return (true);
	vec_multiply_scalar(&temp, &meta_data->pixel.normal, 0.001);
	vec_add(new_origin, &meta_data->pixel.intersect, &temp);
	meta_data->pixel.spot_attenuate = pow(meta_data->pixel.spot_attenuate,
			meta_data->pixel.spot_p);
	d_attenuation = (double)1.0 / (meta_data->pixel.spot_k0
			+ (meta_data->pixel.spot_k1 * *len) + (meta_data->pixel.spot_k2
				* *len * *len));
	meta_data->pixel.spot_intensity = spotlight->brightness * d_attenuation
		* meta_data->pixel.spot_attenuate;
	return (false);
}

bool	in_shadow_spotlight(t_meta *meta_data, t_spotlight *spotlight)
{
	double		len;
	t_vector	new_origin;

	if (in_shadow_spotlight_setup(meta_data, spotlight, &len,
			&new_origin) == true)
		return (true);
	if (meta_data->sp_allocated && meta_data->sp != NULL
		&& in_shadow_sp(meta_data, &new_origin, len) == true)
		return (true);
	if (meta_data->pl_allocated && meta_data->pl != NULL
		&& in_shadow_pl(meta_data, &new_origin, len) == true)
		return (true);
	if (meta_data->cy_allocated && meta_data->cy != NULL
		&& in_shadow_cy(meta_data, &new_origin, len) == true)
		return (true);
	if (meta_data->cn_allocated && meta_data->cn != NULL
		&& in_shadow_cn(meta_data, &new_origin, len) == true)
		return (true);
	return (false);
}
