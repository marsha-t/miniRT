/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:25:52 by mateo             #+#    #+#             */
/*   Updated: 2024/09/02 11:51:29 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	
	get_sp_bm_normal gets perturbed normal for a sphere
	- uv maps (convert 3d intersection to 2d uv coordinates)
	- scales and wraps uv coordinates
	- extracts normal vector from bumpmap using uv coordinates
	- converts vector from tangent space to world space
*/
t_vector get_sp_bm_normal(t_pixel *pixel, t_sp *sphere)
{
	double		theta;
	double		phi;
	// t_vector	temp;
	t_vector	bm_normal;

	uv_map_sp(pixel, sphere, &theta, &phi);
	// vec_subtract(&temp, &pixel->intersect, &sphere->coord);
	// phi = atan2(temp.z, temp.x);
	// theta = acos(temp.y / sphere->radius);
	// theta = 0.5 + theta / (2 * M_PI);
	// phi /= (M_PI);
	theta = theta * sphere->bump_img.scale;
	phi = phi * sphere->bump_img.scale;
	theta = fmod(theta, 1.0);
	phi = fmod(phi, 1.0);
	theta = theta * (double) sphere->bump_img.width;
	phi = phi * (double) sphere->bump_img.height;
	bm_normal = extract_bm(theta, phi, &sphere->bump_img);
	return (get_world_normal(&bm_normal, &pixel->normal));
}

/*
	get_cy_curve_bm_normal gets perturbed normal for cylinder curved surface
	- uv maps (convert 3d intersection to 2d uv coordinates)
	- scales and wraps uv coordinates
	- extracts normal vector from bumpmap using uv coordinates
	- converts vector from tangent space to world space
*/
t_vector	get_cy_curve_bm_normal(t_pixel *pixel, t_cy *cylinder)
{
	double	u;
	double v;
	t_vector	bm_normal;

	uv_map_cy_curve(pixel, cylinder, &u, &v);
	u = u * cylinder->bump_img.scale;
	v = v * cylinder->bump_img.scale;
	u = fmod(u, 1.0);
	v = fmod(v, 1.0);
	u = u * (double) cylinder->bump_img.width;
	v = v * (double) cylinder->bump_img.height;
	bm_normal = extract_bm(u, v, &cylinder->bump_img);
	return (get_world_normal(&bm_normal, &pixel->normal));		
}

/*
	get_cy_base_bm_normal gets perturbed normal for cylinder base
	- uv maps (convert 3d intersection to 2d uv coordinates)
	- scales and wraps uv coordinates
	- extracts normal vector from bumpmap using uv coordinates
	- converts vector from tangent space to world space
*/
t_vector	get_cy_base_bm_normal(t_pixel *pixel, t_cy *cylinder)
{
	double	u;
	double v;
	t_vector	bm_normal;
	
	uv_map_cy_base(pixel, cylinder, &u, &v);
	double area;
	area = cylinder->radius * cylinder->radius * M_PI;
	double scale;
	scale = area / cylinder->bump_img.area;
	// u = u * cylinder->bump_img.scale;
	// v = v * cylinder->bump_img.scale;
	u = fmod(u, 1.0);
	v = fmod(v, 1.0);
	u = u * (double) cylinder->bump_img.width;
	v = v * (double) cylinder->bump_img.height;
	bm_normal = extract_bm(u, v, &cylinder->bump_img);
	return (get_world_normal(&bm_normal, &pixel->normal));
}

/*	
	get_world_normal converts extracted vector from bumpmap
	from tangent space to world space
*/
t_vector	get_world_normal(t_vector *bm_normal, t_vector *ori_normal)
{
	t_vector	tangent;
	t_vector	bitangent;
	t_vector	arbitrary;
	t_vector	new_normal;

	least_parallel_avector(&arbitrary, ori_normal);
	vec_cross_product(&tangent, ori_normal, &arbitrary);
	vec_normalise(&tangent);
	vec_cross_product(&bitangent, ori_normal, &tangent);
	vec_normalise(&bitangent);
	new_normal.x = bm_normal->x * tangent.x + bm_normal->y * bitangent.x + bm_normal->z * ori_normal->x;
	new_normal.y = bm_normal->x * tangent.y + bm_normal->y * bitangent.y + bm_normal->z * ori_normal->y;
	new_normal.z = bm_normal->x * tangent.z + bm_normal->y * bitangent.z + bm_normal->z * ori_normal->z;
	return (new_normal);
}

/*	
	extract_bm extracts RGB values from bumpmap using uv coordinates
	and converts into normal vector
*/
t_vector extract_bm(int x, int y, t_img *img)
{
	char	*data;
	int	colour;
	t_vector	normal;
	
	data = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	colour = *(unsigned int *)data;
	normal.x = (double)(colour >> 16 & 0xFF) / 255.0;
	normal.y = (double)(colour >> 8 & 0xFF) / 255.0;
	normal.z = (double)(colour & 0xFF) / 255.0;
	normal.x = normal.x * 2 - 1;
	normal.y = normal.y * 2 - 1;
	normal.z = normal.z * 2 - 1;
	vec_normalise(&normal);
	// print_vector("bm: normal:", &normal);
	return (normal);
}


// t_vector get_pl_bm_normal(t_pixel *pixel, t_pl *plane) // how to calculate scale for plane
// {
// 	double		u;
// 	double		v;
// 	t_vector	bm_normal;

// 	uv_map_pl(pixel, plane, &u, &v);
// 	u = u / plane->bump_img.scale;
// 	v = v / plane->bump_img.scale;
// 	u = fmod(u, 1.0);
// 	v = fmod(v, 1.0);
// 	// is the bit below needed?
// 	// u = u * (double) sphere->bump_img.width;
// 	// v = v * (double) sphere->bump_img.height;
// 	bm_normal = extract_bm(u, v, &plane->bump_img);
// 	return (get_world_normal(&bm_normal, &pixel->normal));
// }