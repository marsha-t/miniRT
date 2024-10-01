/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:26:43 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/11 17:26:43 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

// check_double iterates through each input value and check if each character
// is a digit. if condition fails, it frees the allocated memories an
//  exits the program
double	check_double(t_meta **meta_data, void *temp, char **src, char *str)
{
	int		index;
	double	result;

	index = -1;
	while (str[++index])
	{
		if (ft_isdigit(str[index]) == 0 && str[index] != '.'\
			&& str[index] != '-' && str[index] != '+')
		{
			free_exit(*meta_data);
			free_pointer(src);
			free(temp);
			ft_printf(RED"Incorrect DOUBLE input values\n"RST);
			exit(EXIT_FAILURE);
		}
	}
	result = ft_strtod(str);
	return (result);
}

int	check_int(t_meta **meta_data, char *str)
{
	int		index;
	double	result;

	index = -1;
	while (str[++index])
	{
		if (ft_isdigit(str[index]) == 0 && str[index] != '-' && \
			str[index] != '+')
		{
			free_exit(*meta_data);
			ft_printf(RED"Incorrect INT input values\n"RST);
			exit(EXIT_FAILURE);
		}
	}
	result = ft_atoi(str);
	return (result);
}

/*
	check_checker parses parameters for checkerboard patterns
	- checks that the values are non-zero and positive
	- checks that only 2 values are given
	- if checks fail, it frees the allocated memories and exits the program
	- otherwise, row and col are assigned the parsed values
*/
t_sqsize	check_checker(t_meta **meta_data, void *temp, \
	char **src, char **argv)
{
	int			arg_count;
	t_sqsize	sqsize;
	double		temp_val;

	arg_count = 0;
	while (argv[++arg_count])
	{
		temp_val = ft_strtod(argv[arg_count]);
		if (temp_val <= 0)
			checker_exit(meta_data, temp, src, argv);
	}
	if (arg_count != 3)
		checker_exit(meta_data, temp, src, argv);
	sqsize.row = ft_strtod(argv[1]);
	sqsize.col = ft_strtod(argv[2]);
	return (sqsize);
}

/*
	check_bump parses the bump map path
	- checks that only one element (separated by comma) waas given
	- loads xpm img
	- if checks fail, it frees the allocated memories and exits the program
	- otherwise, it returns the path
*/
t_img	check_bump(t_meta **meta_data, void *temp, char **src, \
	char **argv)
{
	t_img	bump_img;

	if (argv[2] || is_xpm_file(argv[1]) == false)
	{
		if (temp != NULL)
			free(temp);
		free_pointerlist(2, src, argv);
		if (argv[2])
			ft_printf(RED"Incorrect no. of bump map arguments\n"RST);
		else
			ft_printf(RED"Incorrect bump map file\n"RST);
		free_exit(*meta_data);
		exit(EXIT_FAILURE);
	}
	bump_img.img = mlx_xpm_file_to_image((*meta_data)->mlx_ptr, \
		argv[1], &bump_img.width, &bump_img.height);
	if (!bump_img.img)
		bump_exit(meta_data, temp, src, argv);
	bump_img.addr = mlx_get_data_addr(bump_img.img, &bump_img.bits_per_pixel, \
		&bump_img.line_length, &bump_img.endian);
	return (bump_img);
}

/*
	is_xpm_file checks that path ends with .xpm
*/
bool	is_xpm_file(char *path)
{
	char	*dot;

	dot = ft_strrchr(path, '.');
	if (dot == NULL)
		return (false);
	dot++;
	if (ft_strncmp(dot, "xpm", 4) != 0)
		return (false);
	return (true);
}
