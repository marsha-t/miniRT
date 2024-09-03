/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:25:52 by mateo             #+#    #+#             */
/*   Updated: 2024/09/03 13:14:02 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
	get_*_bm_normal:
	- uv maps to convert 3d coordinates to 2d coordinates
	- calculate horizontal and vertical gradients
	- perturb normal using gradients 
*/
t_vector get_sp_bm_normal(t_pixel *pixel, t_sp *sphere)
{
	double		u;
	double		v;
	
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
	double v;

	uv_map_cy_curve(pixel, cylinder, &u, &v);
	get_bm_gradient(&cylinder->bump_img, &u, &v);
	return (perturb_normal(&pixel->normal, u, v));
}

t_vector	get_cy_base_bm_normal(t_pixel *pixel, t_cy *cylinder)
{
	double	u;
	double v;
	
	uv_map_cy_base(pixel, cylinder, &u, &v);
	get_bm_gradient(&cylinder->bump_img, &u, &v);
	return (perturb_normal(&pixel->normal, u, v));
}

/*
	get_bm_gradient extracts height from bumpmap using u & v and its neighbours
	- wraps u & v as necessary to tile bump map across surface
	- interprets greyscale value as height
	- u replaced with horizontal gradient
	- v replaced with vertical gradient 
	- INTENSITY_SCALE: increase to make perturbations more subtle
*/
void	get_bm_gradient(t_img *img, double *u, double *v)
{
	int		x[2];
	int		y[2];
	int		c[2];
	char	*dst;

	x[0] = (((int)((1 - *u) * img->width)) + img->width / 2) % img->width;
	y[0] = (((int)((1 - *v) * img->height)) + img->height / 2) % img->height;
	x[1] = (x[0] + 1) % img->width;
	y[1] = (y[0] + 1) % img->height;
	dst = img->addr
		+ (y[0] * img->line_length + x[0] * (img->bits_per_pixel / 8));
	c[0] = *((unsigned int *)dst) & 0xff;
	dst = img->addr
		+ (y[0] * img->line_length + x[1] * (img->bits_per_pixel / 8));
	c[1] = *((unsigned int *)dst) & 0xff;
	*u = -((float)(c[0] - c[1])) / INTENSITY_SCALE;
	dst = img->addr
		+ (y[1] * img->line_length + x[0] * (img->bits_per_pixel / 8));
	c[1] = *((unsigned int *)dst) & 0xff;
	*v = -((float)(c[0] - c[1])) / INTENSITY_SCALE;
}

/*	
	perturb_normal adjusts the normal vector 
	by adding scaled versions of tangent and bitangent vectors
*/
t_vector	perturb_normal(t_vector *ori_normal, double u, double v)
{
	t_vector	tangent;
	t_vector	bitangent;
	t_vector	arbitrary;
	t_vector	new_normal;
	t_vector	temp;
	
	least_parallel_avector(&arbitrary, ori_normal);
	vec_cross_product(&tangent, ori_normal, &arbitrary);
	vec_normalise(&tangent);
	vec_cross_product(&bitangent, ori_normal, &tangent);
	vec_normalise(&bitangent);
	vec_multiply_scalar(&temp, &tangent, v);
	vec_add(&new_normal, ori_normal, &temp);
	vec_multiply_scalar(&temp, &bitangent, u);
	vec_add(&new_normal, &new_normal, &temp);
	vec_normalise(&new_normal);
	return (new_normal);
}
