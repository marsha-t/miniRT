/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:05:17 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/11 21:17:56 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
	check_norm iterates through each input value and check if each character
	is a digit. Also checks if the number of inputs is equal to three and if
	the value is between -1 and 1, and if all values are not 0.
	if condition fails, it frees the allocated memories and exits the program
*/
t_vector	check_norm(t_meta **meta_data, void *temp, char **src, char **argv)
{
	t_vector	vec;
	int			arg_count;
	double		temp_val;
	static int	count_zeroes;

	arg_count = -1;
	while (argv[++arg_count])
	{
		if (!(check_norm_val(*meta_data, src, arg_count, argv)))
			norm_exit(meta_data, temp, src, argv);
		temp_val = ft_strtod(argv[arg_count]);
		if (temp_val == (double)0)
			count_zeroes++;
		if (count_zeroes >= 3)
			norm_exit(meta_data, temp, src, argv);
	}
	if (arg_count != 3)
		norm_exit(meta_data, temp, src, argv);
	vec.x = ft_strtod(argv[0]);
	vec.y = ft_strtod(argv[1]);
	vec.z = ft_strtod(argv[2]);
	count_zeroes = 0;
	return (vec);
}

bool	check_norm_val(t_meta *meta_data, char **src, \
	int arg_count, char **argv)
{
	double	temp;
	int		index;

	(void)meta_data;
	(void)src;
	index = -1;
	while (argv[arg_count][++index])
	{
		if (ft_isdigit(argv[arg_count][index]) == 0 && \
			argv[arg_count][index] != '.'\
			&& argv[arg_count][index] != '-' && argv[arg_count][index] != '+')
			return (false);
	}
	temp = ft_strtod(argv[arg_count]);
	if (temp > 1 || temp < -1 || arg_count >= 3)
		return (false);
	return (true);
}

void	norm_exit(t_meta **meta_data, void *temp, char **src, char **argv)
{
	if (temp != NULL)
		free(temp);
	if (src != NULL)
		free_pointer(src);
	if (argv != NULL)
		free_pointer(argv);
	ft_printf(RED"A Incorrect normal vector input values\n"RST);
	free_exit(*meta_data);
	exit(EXIT_FAILURE);
}
