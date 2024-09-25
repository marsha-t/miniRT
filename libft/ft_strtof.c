/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/09/25 16:45:26 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/25 16:45:26 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_strtof(const char *str)
{
	float	result;
	int		sign;

	result = 0.0;
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
	result = conv_float(str);
	result *= sign;
	return (result);
}

float	conv_float(const char *str)
{
	float	result;
	float	fraction;

	fraction = 1.0;
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
			fraction /= 10.0f;
			result += (*str - '0') * fraction;
			str++;
		}
	}
	return (result);
}
