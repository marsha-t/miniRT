/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:25:52 by mateo             #+#    #+#             */
/*   Updated: 2024/09/03 16:50:45 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
	get_*_bm_normal:
	- uv maps to convert 3d coordinates to 2d coordinates
	- calculate horizontal and vertical gradients
	- perturb normal using gradients
*/
t_vector	get_sp_bm_normal(t_pixel *pixel, t_sp *sphere)
{
	double	u;
	double	v;

	uv_map_sp(pixel, sphere, &u, &v);
	get_bm_gradient(&sphere->bump_img, &u, &v);
	return (perturb_normal(&pixel->normal, u, v));
}

t_vector	get_pl_bm_normal(t_pixel *pixel, t_pl *plane)
{
	double	u;
	double	v;

	uv_map_pl(pixel, plane, &u, &v);
	get_bm_gradient(&plane->bump_img, &u, &v);
	return (perturb_normal(&pixel->normal, u, v));
}

t_vector	get_cy_curve_bm_normal(t_pixel *pixel, t_cy *cylinder)
{
	double	u;
	double	v;

	uv_map_cy_curve(pixel, cylinder, &u, &v);
	get_bm_gradient(&cylinder->bump_img, &u, &v);
	return (perturb_normal(&pixel->normal, u, v));
}

t_vector	get_cy_base_bm_normal(t_pixel *pixel, t_cy *cylinder)
{
	double	u;
	double	v;

	uv_map_cy_base(pixel, cylinder, &u, &v);
	get_bm_gradient(&cylinder->bump_img, &u, &v);
	return (perturb_normal(&pixel->normal, u, v));
}
