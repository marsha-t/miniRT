/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:07:18 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/11 22:51:12 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	cn_elements(t_meta *meta_data, t_cn *cn, char **argv)
{
	char	**coord;
	char	**axis;
	char	**colour;

	coord = ft_split(argv[1], ',');
	cn->coord = check_coord(&meta_data, cn, argv, coord);
	free_pointer(coord);
	axis = ft_split(argv[2], ',');
	cn->axis = check_norm(&meta_data, cn, argv, axis);
	free_pointer(axis);
	colour = ft_split(argv[5], ',');
	cn->colour = check_colour(&meta_data, cn, argv, colour);
	free_pointer(colour);
}

void	cn_bonus(t_meta *meta_data, t_cn *cn, char **argv)
{
	int		i;
	char	**bonus;

	i = 5;
	while (argv[++i])
	{
		bonus = ft_split(argv[i], ',');
		if (bonus[0][0] == 'c')
		{
			cn->checker = 1;
			cn->sqsize = check_checker(&meta_data, cn, argv, bonus);
			free_pointer(bonus);
			if (cn->sqsize.row < 1 || cn->sqsize.col < 1)
			{
				ft_printf(RED"Incorrect checkerboard square size values\n"RST);
				cone_exit(meta_data, NULL);
			}
		}
		else
		{
			ft_printf(RED"Incorrect bonus\n"RST);
			cone_exit(meta_data, argv);
		}
	}
}

/*
	create_cn creates a cone object and check if each value is valid.
	returns t_cn pointer.
*/
t_cn	*create_cn(t_meta *meta_data, char **argv)
{
	t_cn	*cn;

	ft_printf(G"\tCONE OBJECT ...\t"RST);
	cn = check_cn_args(meta_data, argv);
	cn_elements(meta_data, cn, argv);
	cn->height = check_double(&meta_data, cn, argv, argv[4]);
	cn->angle = check_double(&meta_data, cn, argv, argv[3]);
	if (cn->angle >= 90)
		cone_exit(meta_data, argv);
	cn->checker = 0;
	cn_bonus(meta_data, cn, argv);
	cn->next = NULL;
	ft_printf(G" OK \n"RST);
	return (cn);
}

t_cn	*check_cn_args(t_meta *meta_data, char **argv)
{
	t_cn	*cn;

	if (pointer_count(argv) < 6 || pointer_count(argv) > 7)
	{
		ft_printf(RED"Incorrect CN data <cn X,Y,Z Axis Angle Height\
			RGB [checkerboard]>\n"RST);
		free_args(meta_data, argv);
		exit(EXIT_FAILURE);
	}
	cn = malloc(sizeof(t_cn));
	if (!cn)
		free_args(meta_data, argv);
	return (cn);
}

void	cone_exit(t_meta *meta_data, char **argv)
{
	free_args(meta_data, argv);
	exit(EXIT_FAILURE);
}
