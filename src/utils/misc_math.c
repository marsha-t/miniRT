/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 07:47:18 by mateo             #+#    #+#             */
/*   Updated: 2024/08/08 10:53:42 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*	deg_to_rad converts degrees to radians */
double	deg_to_rad(int degree)
{
	return (degree * (M_PI / 180.0));
}
