/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:38:03 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/25 16:38:03 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_strtod(const char *str)
{
	double	result;
	int		sign;

	sign = 1;
	while (ft_isspace((unsigned char)*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	result = conv_double(str);
	result *= sign;
	return (result);
}

double	conv_double(const char *str)
{
	double	result;
	double	fraction;

	fraction = 1.0;
	result = 0.0;
	while (ft_isdigit((unsigned char)*str))
	{
		result = result * 10.0f + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (ft_isdigit((unsigned char)*str))
		{
			fraction /= 10.0;
			result += (*str - '0') * fraction;
			str++;
		}
	}
	return (result);
}
