#include "../../include/miniRT.h"

/*
	check_coord iterates through each input value and check if each character
	is a digit. Also checks if the number of inputs is equal to three.
	if condition fails, it frees the allocated memories and exits the program
*/
t_vector    check_coord(t_meta **meta_data, void *temp, char **src, char **argv)
{
	t_vector    vec;
	int         index;
	int         arg_count;

	arg_count = -1;
	while(argv[++arg_count])
	{
		index = -1;
		while(argv[arg_count][++index])
		{
			if (ft_isdigit(argv[arg_count][index]) == 0 && \
				argv[arg_count][index] != '.' && argv[arg_count][index] != '-' \
				&& argv[arg_count][index] != '+')
			{
				if (temp != NULL)
					free(temp);
				free_pointerlist(2, src, argv);
				ft_printf(RED"Incorrect XYZ input values\n"RST);
				free_exit(*meta_data);
				exit(EXIT_FAILURE);
			}
		}
	}
	if (arg_count != 3)
	{
		if (temp != NULL)
			free(temp);
		free_pointerlist(2, src, argv);
		ft_printf(RED"Incorrect XYZ input values\n"RST);
		free_exit(*meta_data);
		exit(EXIT_FAILURE);
	}
	vec.x = ft_strtod(argv[0]);
	vec.y = ft_strtod(argv[1]);
	vec.z = ft_strtod(argv[2]);
	return (vec);
}

/*
	check_norm iterates through each input value and check if each character
	is a digit. Also checks if the number of inputs is equal to three and if
	the value is between -1 and 1, and if all values are not 0.
	if condition fails, it frees the allocated memories and exits the program
*/
t_vector    check_norm(t_meta **meta_data, void *temp, char **src, char **argv)
{
	t_vector    vec;
	int         arg_count;
	double      temp_val;
	static int  count_zeroes;

	arg_count = -1;
	while(argv[++arg_count])
	{
		if (!(check_norm_val(*meta_data, src, arg_count, argv)))
		{
			if (temp != NULL)
				free(temp);
			exit(EXIT_FAILURE);
		}
		temp_val = ft_strtod(argv[arg_count]);
		if (temp_val == (double)0)
			count_zeroes++;
		if (count_zeroes >= 3)
		{
			free_exit(*meta_data);
			ft_printf(RED"A Incorrect normal vector input values\n"RST);
			free_pointerlist(2, src, argv);
			if (temp != NULL)
				free(temp);
			exit(EXIT_FAILURE);
		}
	}
	if (arg_count != 3)
	{
		if (temp != NULL)
			free(temp);
		free_pointerlist(2, src, argv);
		ft_printf(RED"Incorrect XYZ input values\n"RST);
		free_exit(*meta_data);
		exit(EXIT_FAILURE);
	}
	vec.x = ft_strtod(argv[0]);
	vec.y = ft_strtod(argv[1]);
	vec.z = ft_strtod(argv[2]);
	count_zeroes = 0;
	return (vec);
}

/*
	check_double iterates through each input value and check if each character
	is a digit. if condition fails, it frees the allocated memories and exits the program
*/
double    check_double(t_meta **meta_data, void *temp, char **src, char *str)
{
	int index;
	double result;

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

int    check_int(t_meta **meta_data, char *str)
{
	int index;
	double result;

	index = -1;
	while(str[++index])
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
	check_norm_val iterates through each input value and check if each character
	is a digit. Also checks if the number of inputs is equal to three and if
	the value is between -1 and 1, and if all values are not 0.
	if condition fails, it frees the allocated memories and exits the program
*/
bool    check_norm_val(t_meta *meta_data, char **src, int arg_count, char **argv)
{
	double temp;
	int index;\

	index = -1;
    while(argv[arg_count][++index])
    {
        if (ft_isdigit(argv[arg_count][index]) == 0 && \
            argv[arg_count][index] != '.'\
            && argv[arg_count][index] != '-' && argv[arg_count][index] != '+')
        {
            free_exit(meta_data);
            ft_printf(RED"Incorrect normal vector input values\n"RST);
            free_pointerlist(2, src, argv);
            return (false);
        }
    }
    temp = ft_strtod(argv[arg_count]);\
    if (temp > 1 || temp < -1 || arg_count >= 3)
    // if ((temp != 1 && temp != 0 && temp != -1) || arg_count >= 3)
    {
        free_exit(meta_data);
        ft_printf(RED"A Incorrect normal vector input values\n"RST);
        free_pointerlist(2, src, argv);
        return (false);
    }
    return (true);
}

/*
	check_colour_val iterates through each input value and check if each character
	is a digit. Also checks if the number of inputs is equal to three and if
	the value is between 0 and 255.
	if condition fails, it frees the allocated memories and exits the program
*/
bool    check_colour_val(t_meta *meta_data, char **src, int arg_count, char **argv)
{
	int temp;
	int index;

	index = -1;
	while(argv[arg_count][++index])
	{
		if (ft_isdigit(argv[arg_count][index]) == 0 && \
			argv[arg_count][index] != '-' && argv[arg_count][index] != '+')
		{
			free_exit(meta_data);
			ft_printf(RED"Incorrect RGB input values\n"RST);
			free_pointerlist(2, src, argv);
			return (false);
		}
	}
	temp = ft_atoi(argv[arg_count]);
	if (!(temp >= 0 && temp <= 255) || arg_count >= 3)
	{
		free_exit(meta_data);
		ft_printf(RED"Incorrect RGB input values\n"RST);
		free_pointerlist(2, src, argv);
		return (false);
	}
	return (true);
}

/*
	check_colour iterates through each input value and check if each character
	is a digit. Also checks if the number of inputs is equal to three and if
	the value is between 0 and 255.
	if condition fails, it frees the allocated memories and exits the program
*/
t_colour    check_colour(t_meta **meta_data, void *temp, char **src, char **argv)
{
	t_colour    rgb;
	int         arg_count;

	arg_count = -1;
	while(argv[++arg_count])
	{
		if (!check_colour_val(*meta_data, src, arg_count, argv))
		{
			if (temp != NULL)
				free(temp);
			exit(EXIT_FAILURE);
		}
	}
	if (arg_count != 3)
	{
		if (temp != NULL)
			free(temp);
		free_pointerlist(2, src, argv);
		ft_printf(RED"Incorrect XYZ input values\n"RST);
		free_exit(*meta_data);
		exit(EXIT_FAILURE);
	}
	rgb.r = ft_atoi(argv[0]);
	rgb.g = ft_atoi(argv[1]);
	rgb.b = ft_atoi(argv[2]);
	return (rgb);
}

/*
	check_checker parses parameters for checkerboard patterns
	- checks that the values are non-zero and positive
	- checks that only 2 values are given
	- if checks fail, it frees the allocated memories and exits the program
	- otherwise, row and col are assigned the parsed values
*/
t_sqsize    check_checker(t_meta** meta_data, void *temp, char **src, char **argv)
{
	int		arg_count;
	t_sqsize	sqsize;
	double	temp_val;

	arg_count = 0;	
	while (argv[++arg_count])
	{
		temp_val = ft_strtod(argv[arg_count]);
		if (temp_val <= 0)
		{
			if (temp != NULL)
				free(temp);
			free_pointerlist(2, src, argv);
			ft_printf(RED"Incorrect checkerboard square size values\n"RST);
			free_exit(*meta_data);
			exit(EXIT_FAILURE);
		}
	}
	if (arg_count != 3)
	{
		if (temp != NULL)
			free(temp);
		free_pointerlist(2, src, argv);
		ft_printf(RED"Incorrect no. of checkerboard arguments\n"RST);
		free_exit(*meta_data);
		exit(EXIT_FAILURE);
	}
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
t_img	check_bump(t_meta** meta_data, void *temp, char **src, char **argv)
{
	t_img	bump_img;

	if (argv[2])
	{
		if (temp != NULL)
			free(temp);
		free_pointerlist(2, src, argv);
		ft_printf(RED"Incorrect no. of bump map arguments\n"RST);
		free_exit(*meta_data);
		exit(EXIT_FAILURE);
	}
	bump_img.img = mlx_xpm_file_to_image((*meta_data)->mlx_ptr, argv[1], &bump_img.width, &bump_img.height);
	if (!bump_img.img)
	{
		if (temp != NULL)
			free(temp);
		free_pointerlist(2, src, argv);
		ft_printf(RED"Error from mlx_xpm_file_to_image\n"RST);
		free_exit(*meta_data);
		exit(EXIT_FAILURE);
	}
	bump_img.addr = mlx_get_data_addr(bump_img.img, &bump_img.bits_per_pixel, &bump_img.line_length, &bump_img.endian);
	return (bump_img);
}
