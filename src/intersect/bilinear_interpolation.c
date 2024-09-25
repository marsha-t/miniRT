/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bilinear_interpolation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:04:27 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/25 14:12:25 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	bilinear_interpolation(t_meta *meta_data, t_colour prev, int x, int y)
{
	meta_data->q4 = meta_data->pixel.final;
	meta_data->q3 = prev;
	meta_data->q2 = meta_data->prev_arr[x];
	meta_data->q1 = meta_data->prev_arr[x - 3];
	meta_data->x = x;
	meta_data->y = y;
}

// t_colour	calc_finalcolour(t_meta *meta_data, int x, int y)
// {
// 	t_colour	out;
// 	double		a1;
// 	double		a2;
// 	double		b1;
// 	double		b2;

// 	a1 = meta_data->x - x;
// 	a2 = x - (meta_data->x - 3);
// 	b1 = meta_data->y - y;
// 	b2 = y - (meta_data->y - 3);
// 	out.r = ((double)1 / (double)9) * ((((meta_data->q1.r * a1) 
// + (meta_data->q3.r * a2)) * b1) 
// 		+ (((a1 * meta_data->q))))
// }