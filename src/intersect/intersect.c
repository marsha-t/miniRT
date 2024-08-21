/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:07:21 by mateo             #+#    #+#             */
/*   Updated: 2024/08/21 04:37:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	intersect_closest iterates through all objects 
	- objects that previously intersected at negative at excluded
	- intersect_<shape> will update pixel data on value of t for closest intersection
	- compute closest intersection
*/
void	intersect_closest(t_meta *meta_data)
{
	t_sp	*sphere;
	t_pl	*plane;
	t_cy	*cylinder;
	t_cn	*cone;

	// printf("enter here\n");
	if (meta_data->sp_allocated && meta_data->sp)
	{
		sphere = meta_data->sp;
		while (sphere)
		{
			if (sphere->exclude == 0)
				intersect_sp(meta_data, sphere);
			sphere = sphere->next;
		}
	}
	if (meta_data->pl_allocated && meta_data->pl)
	{
		plane = meta_data->pl;
		while (plane)
		{
			if (plane->exclude == 0)
				intersect_pl(meta_data, plane);
			plane = plane->next;
		}
	}
	if (meta_data->cy_allocated && meta_data->cy)
	{
		cylinder = meta_data->cy;
		while (cylinder)
		{
			if (cylinder->exclude == 0)
				intersect_cy(meta_data, cylinder);
			cylinder = cylinder->next;
		}
	}
	if (meta_data->cn_allocated && meta_data->cn)
	{
		cone = meta_data->cn;
		while (cone)
		{
			if (cone->exclude == 0)
				intersect_cn(meta_data, cone);
			cone = cone->next;
		}
	}
	get_ray_pt(&meta_data->pixel.intersect, meta_data, meta_data->pixel.t);
}

/*	intersect_sp finds the intersection between ray and a given sphere
	- if intersection (t) is closer than the last intersection (pixel.t), 
		data in pixel (i.e., t, obj and surface) is updated
	- no update if no intersection or intersection is further than last intersection found
	- if intersection (t) is negative, object excluded from future calculations 
	 */
void	intersect_sp(t_meta *meta_data, t_sp *sphere)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;
	t_vector	temp;

	a = vec_dot_product(&meta_data->pixel.ray, &meta_data->pixel.ray);
	vec_subtract(&temp, &meta_data->camera->coord, &sphere->coord);
	b = vec_dot_product(&meta_data->pixel.ray, &temp) * 2;
	c = vec_dot_product(&temp, &temp) - ((sphere->radius) * (sphere->radius));
	// meta_data->pixel.coord = meta_data->light->coord;
	discriminant = (b*b) - (4*a*c);
	if (discriminant < 0)
		return ;
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	// printf("t: %f t1: %f t2: %f\n", meta_data->pixel.t, t1, t2);
	if (t1 < 0 && t2 < 0 && meta_data->pixel.t < 0)
	{
		sphere->exclude = 1;
		meta_data->pixel.t = -1;
		return ;
	}
	else if (t1 < 0 && t2 > 0 && t2 < meta_data->pixel.t && meta_data->pixel.t > 0)
	{
		meta_data->pixel.t = t2;
	}
	else if (t1 > 0 && t2 < 0 && t1 < meta_data->pixel.t && meta_data->pixel.t > 0)
	{
		meta_data->pixel.t = t1;
	}
	else if (t1 > 0 && t2 > 0 && t1 < t2 && t1 < meta_data->pixel.t && meta_data->pixel.t > 0)
	{
		meta_data->pixel.t = t1;
	}
	else if (t1 > 0 && t2 > 0 && t1 > t2 && t2 < meta_data->pixel.t && meta_data->pixel.t > 0)
	{
		meta_data->pixel.t = t2;
	}
	else if (t1 < 0 && t2 > 0 && meta_data->pixel.t < 0)
	{
		meta_data->pixel.t = t2;
	}
	else if (t1 > 0 && t2 < 0 && meta_data->pixel.t < 0)
	{
		meta_data->pixel.t = t1;
	}
	else if (t1 > 0 && t2 > 0 && t1 < t2 && meta_data->pixel.t < 0)
	{
		meta_data->pixel.t = t1;
	}
	else if (t1 > 0 && t2 > 0 && t1 > t2 && meta_data->pixel.t < 0)
	{
		meta_data->pixel.t = t2;
	}
	else if (t1 == t2 && meta_data->pixel.t < 0)
	{
		meta_data->pixel.t = t2;
	}
	else if (t1 == t2 && meta_data->pixel.t > t2 && meta_data->pixel.t > 0)
	{
		meta_data->pixel.t = t2;
	}
	else
	{
		// sphere->exclude = 1;
		// meta_data->pixel.t = -1;
		return ;
	}
	// printf("t: %f t1: %f t2: %f\n", meta_data->pixel.t, t1, t2);
	// printf("pixel.t: %f\n", meta_data->pixel.t);
	// if (t == 0)
	// {
	// 	meta_data->pixel.t = 0;
	// 	return ;
	// }
	// else if (t1 < 0 && t2 < 0)
	// {
	// 	sphere->exclude = 1;
	// 	meta_data->pixel.t = t;
	// 	return ;
	// }
	// else if (t > 0 && t < meta_data->pixel.t)
	// 	meta_data->pixel.t = t;
	// if (discriminant > 0)
	// {
	// 	t = (-b + sqrt(discriminant)) / (2.0 * a);
	// 	meta_data->pixel.t = t;
	// 	if (t <= 0)
	// 		return ; // exclude object accordingly (for t < 0)
	// 	// else if (t > 0 && t < meta_data->pixel.t)
	// }
	meta_data->pixel.obj = (void *)sphere;
	meta_data->pixel.final.r_n = sphere->colour.r_n;
	meta_data->pixel.final.g_n = sphere->colour.g_n;
	meta_data->pixel.final.b_n = sphere->colour.b_n;
	meta_data->pixel.surface = SF_SPHERE;
	meta_data->pixel.coord = sphere->coord;
	return ;
}

/*	intersect_pl finds the intersection between ray and a given plane
	- if intersection (t) is closer than the last intersection (pixel.t), 
		data in pixel (i.e., t, obj and surface) is updated
	- no update if ray is parallel to plane or intersection is further than last intersection found
	- if intersection (t) is negative, plane is NOT excluded from future calculations 
	*/
void	intersect_pl(t_meta *meta_data, t_pl *plane)
{
	double		t;
	double		denom;
	t_vector	temp;

	// printf("intersect pl\n");
	denom = vec_dot_product(&plane->normal, &meta_data->pixel.ray);
	if (denom == 0)
		return ;
	vec_subtract(&temp, &meta_data->camera->coord, &plane->coord);
	t = -1 * ((vec_dot_product(&plane->normal, &temp)) / denom);
	if (t <= 0)
		return ;
	if (t > 0 && meta_data->pixel.t < 0)
		meta_data->pixel.t = t;
	else if (t < meta_data->pixel.t && meta_data->pixel.t > 0)
	{
		meta_data->pixel.t = t;
	}
	else
		return ;
	meta_data->pixel.obj = (void *)plane;
	meta_data->pixel.final.r_n = plane->colour.r_n;
	meta_data->pixel.final.g_n = plane->colour.g_n;
	meta_data->pixel.final.b_n = plane->colour.b_n;
	meta_data->pixel.surface = SF_PLANE;
	meta_data->pixel.coord = plane->coord;
	meta_data->pixel.normal = plane->normal;
	if (vec_dot_product(&plane->normal, &meta_data->pixel.ray) > 0)
	{
		vec_inv(&meta_data->pixel.normal, &plane->normal);
	}
	// printf("denom %f t: %f\n", denom, t);
	// printf("meta_data t: %f\n", meta_data->pixel.t);
}



/*	intersect_cy finds intersection between ray and cylinder
	- calls on intersect_cy_curve to check intersection with curved surface
	- calls on intersect_cy_base to check intersection with both bases
*/
void	intersect_cy(t_meta *meta_data, t_cy *cylinder)
{
	intersect_cy_curve(meta_data, cylinder);
	intersect_cy_base(meta_data, cylinder);
}

/*	intersect_cy_curve checks intersection with curved surface of cylinder
	- calls on update_t_cy_curve to check that intersection point is valid 
		and if so, update pixel data accordingly
	- no update if no intersection or intersection is further than last intersection found
	- if intersection (t) is negative, cylinder is excluded from future calculations 
	*/
void	intersect_cy_curve(t_meta *meta_data, t_cy *cylinder)
{
	double	a;
	double	b;
	double	c;
	t_vector	temp;
	t_vector	d_perpen;
	t_vector	w;
	t_vector	w_perpen;
	double	discriminant;
	double	t;

	vec_multiply_scalar(&temp, &cylinder->axis, vec_dot_product(&meta_data->pixel.ray, &cylinder->axis));
	vec_subtract(&d_perpen, &meta_data->pixel.ray, &temp);
	vec_subtract(&w, &meta_data->camera->coord, &cylinder->coord);
	vec_multiply_scalar(&temp, &cylinder->axis, vec_dot_product(&w, &cylinder->axis));
	vec_subtract(&w_perpen, &w, &temp);
	a = vec_dot_product(&d_perpen, &d_perpen);
	b = vec_dot_product(&w_perpen, &d_perpen) * 2;
	c = vec_dot_product(&w_perpen, &w_perpen) - cylinder->radius * cylinder->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		printf("discriminant %f\n", discriminant);
		return ;
	}
	t = (- b - sqrt(discriminant)) / (2 * a);
	if (t == 0)
	{
		printf("curve t = 0\n");
		return ;
	}
	else if (t < 0)
	{
		printf("curve exclude\n");
		cylinder->exclude = 1;
		return ;
	}
	else if (t > 0 && t < meta_data->pixel.t)
		update_t_cy_curve(meta_data, cylinder, t);
	if (discriminant > 0)
	{
		t = (- b + sqrt(discriminant)) / (2 * a);
		if (t == 0)
		{
			printf("discriminant t = 0\n");
			return ;
		}
		else if (t < 0)
		{
			printf("discriminant exclude = 1\n");
			cylinder->exclude = 1;
			return ;
		}
		else if (t > 0 && t < meta_data->pixel.t)
			update_t_cy_curve(meta_data, cylinder, t);
	}
	printf("t: %f\n", meta_data->pixel.t);
}

/*	update_t_cy_curve updates data in pixel with t
	after checking that t is valid on a cylinder's curved surface
	i.e., that the point lies within cylinder height */
void	update_t_cy_curve(t_meta *meta_data, t_cy *cylinder, double t)
{
	t_vector	ray_pt;
	t_vector	temp;
	double		projection;

	get_ray_pt(&ray_pt, meta_data, t);
	vec_subtract(&temp, &ray_pt, &cylinder->coord);
	projection = vec_dot_product(&temp, &cylinder->axis);
	if (projection < - cylinder->height / 2 || projection > cylinder->height / 2)
		return ;
	else
	{
		meta_data->pixel.t = t;
		meta_data->pixel.obj = (void *)cylinder;
		meta_data->pixel.surface = SF_CY_CURVE;
	}
}

/*	intersect_cy_base checks intersection with BOTH bases of cylinder
	- checks that intersection point (if any) is within radius of cylinder
		and if so, update pixel data accordingly
	- no update if no intersection or intersection is further than last intersection found
	- if intersection (t) is negative, plane is NOT excluded from future calculations 
*/
void	intersect_cy_base(t_meta *meta_data, t_cy *cylinder)
{
	t_vector	temp;
	double	denom;
	double	t;
	double	len;

	denom = vec_dot_product(&cylinder->axis, &meta_data->pixel.ray);
	printf("denom %f\n", denom);
	if (denom == 0)
		return ;
	vec_subtract(&temp, &cylinder->base_bottom, &meta_data->camera->coord);
	t = vec_dot_product(&cylinder->axis, &temp) / denom;
	if (t == 0)
	{
		printf("t = 0\n");
		return ;
	}
	else if (t < 0)
	{
		printf("t < 0\n");
		cylinder->exclude = 1;
		return ;
	}
	len = vec_len(&temp);
	if (t > 0 && t < meta_data->pixel.t && len <= cylinder->radius)
	{
		meta_data->pixel.t = t;
		meta_data->pixel.obj = (void *)cylinder;
		meta_data->pixel.surface = SF_CY_BASE_B;
	}
	vec_subtract(&temp, &cylinder->base_top,& meta_data->camera->coord);
	t = vec_dot_product(&cylinder->axis, &temp) / denom;
	len = vec_len(&temp);
	if (t == 0)
	{
		printf("t = 0\n");
		return ;
	}
	else if (t < 0)
	{
		cylinder->exclude = 1;
		printf("exclude\n");
		return ;
	}
	if (t > 0 && t < meta_data->pixel.t && len <= cylinder->radius)
	{
		meta_data->pixel.t = t;
		meta_data->pixel.obj = (void *)cylinder;
		meta_data->pixel.surface = SF_CY_BASE_T;
	}
	printf("t: %f\n", meta_data->pixel.t);
}

/*	intersect_cn finds intersection between ray and cone
	- calls on intersect_cn_curve to check intersection with curved surface
	- calls on intersect_cn_base to check intersection with base
*/
void	intersect_cn(t_meta *meta_data, t_cn *cone)
{
	intersect_cn_curve(meta_data, cone);
	intersect_cn_base(meta_data, cone);
}

/*	intersect_cy_curve checks intersection with curved surface of cylinder
	- calls on update_t_cy_curve to check that intersection point is valid 
		and if so, update pixel data accordingly
	- no update if no intersection or intersection is further than last intersection found
	- if intersection (t) is negative, cylinder is excluded from future calculations 
*/
void	intersect_cn_curve(t_meta *meta_data, t_cn *cone)
{
	double	a;
	double	b;
	double	c;
	t_vector	w;
	double	temp;
	double	discriminant;
	double	t;

	temp = (cone->radius * cone->radius) / (cone->height * cone->height);
	a = vec_dot_product(&meta_data->pixel.ray, &meta_data->pixel.ray);
	a -= temp * vec_dot_product(&meta_data->pixel.ray, &cone->axis);
	vec_subtract(&w, &meta_data->camera->coord, &cone->coord);
	b = vec_dot_product(&w, &meta_data->pixel.ray);
	b -= temp * vec_dot_product(&w, &cone->axis) * vec_dot_product(&meta_data->pixel.ray, &cone->axis);
	b *= 2;
	c = vec_dot_product(&w, &w) - temp * vec_dot_product(&w, &cone->axis);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return ;
	t = (- b - sqrt(discriminant)) / (2 * a);
	if (t == 0)
		return ;
	else if (t < 0)
	{
		cone->exclude = 1;
		return ;
	}
	else if (t > 0 && t < meta_data->pixel.t)
		update_t_cn_curve(meta_data, cone, t);
	if (discriminant > 0)
	{
		t = (- b + sqrt(discriminant)) / (2 * a);
		if (t == 0)
		return ;
		else if (t < 0)
		{
			cone->exclude = 1;
			return ;
		}
		else if (t > 0 && t < meta_data->pixel.t)
			update_t_cn_curve(meta_data, cone, t);
	}
}

/*	update_t_cn_curve updates data in pixel with t
	after checking that t is valid on a cone's curved surface
	i.e., that the point lies within cone height */
void	update_t_cn_curve(t_meta *meta_data, t_cn *cone, double t)
{
	t_vector	ray_pt;
	t_vector	temp;
	double		projection;

	get_ray_pt(&ray_pt, meta_data, t);
	vec_subtract(&temp, &ray_pt, &cone->coord);
	projection = vec_dot_product(&temp, &cone->axis);
	if (projection < 0 || projection > cone->height)
		return ;
	else
	{
		meta_data->pixel.t = t;
		meta_data->pixel.obj = (void *)cone;
		meta_data->pixel.surface = SF_CONE_CURVE;
	}
}

/*	intersect_cn_base checks intersection with base of cone
	- checks that intersection point (if any) is within radius of cone
		and if so, update pixel data accordingly
	- no update if no intersection or intersection is further than last intersection found
	- if intersection (t) is negative, plane is NOT excluded from future calculations 
*/
void	intersect_cn_base(t_meta *meta_data, t_cn *cone)
{
	t_vector	temp;
	double	denom;
	double	t;
	t_vector	ray_pt;

	denom = vec_dot_product(&meta_data->pixel.ray, &cone->axis);
	if (denom == 0)
		return ;
	vec_subtract(&temp, &cone->base, &meta_data->camera->coord);
	t = vec_dot_product(&temp, &cone->axis) / denom;
	if (t == 0)
		return ;
	else if (t < 0)
	{
		cone->exclude = 1;
		return ;
	}
	get_ray_pt(&ray_pt, meta_data, t);
	vec_subtract(&temp, &ray_pt, &cone->base);
	if (t > 0 && t < meta_data->pixel.t && vec_len(&temp) <= cone->radius)
	{
		meta_data->pixel.t = t;
		meta_data->pixel.obj = (void *)cone;
		meta_data->pixel.surface = SF_CONE_BASE;
	}
}

/*	get_ray_pt generates coordinates for point on ray
	- point = camera + t * ray_direction
*/
void	get_ray_pt(t_vector *dest, t_meta *meta_data, double t)
{
	t_vector	temp;

	// ft_printf("get_ray_pt\n");
	vec_multiply_scalar(&temp, &meta_data->pixel.ray, t);
	vec_add(dest, &meta_data->camera->coord, &temp);
}
