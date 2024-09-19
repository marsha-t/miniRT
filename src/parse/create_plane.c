/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:07:18 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/11 20:22:20 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	pl_elements(t_meta *meta_data, t_pl *pl, char **argv)
{
	char	**coord;
	char	**normal;
	char	**colour;

	coord = ft_split(argv[1], ',');
	pl->coord = check_coord(&meta_data, pl, argv, coord);
	free_pointer(coord);
	normal = ft_split(argv[2], ',');
	pl->normal = check_norm(&meta_data, pl, argv, normal);
	free_pointer(normal);
	colour = ft_split(argv[3], ',');
	pl->colour = check_colour(&meta_data, pl, argv, colour);
	free_pointer(colour);
}

void	pl_bonus(t_meta *meta_data, t_pl *pl, char **argv)
{
	int		i;
	char	**bonus;

	i = 3;
	while (argv[++i])
	{
		bonus = ft_split(argv[i], ',');
		if (bonus[0][0] == 'c')
		{
			pl->checker = 1;
			pl->sqsize = check_checker(&meta_data, pl, argv, bonus);
			free_pointer(bonus);
		}
		else if (bonus[0][0] == 'b')
		{
			pl->bump = 1;
			pl->bump_img = check_bump(&meta_data, pl, argv, bonus);
		}
		else
		{
			ft_printf(RED"Incorrect bonus\n"RST);
			free_args(meta_data, bonus);
			exit(EXIT_FAILURE);
		}
	}
}

/*
	create_pl creates a plane object and check if each value is valid.
	returns t_pl pointer.
*/
t_pl	*create_pl(t_meta *meta_data, char **argv)
{
	t_pl	*pl;

	ft_printf(G"\tPLANE OBJECT ...\t"RST);
	pl = check_pl_args(meta_data, argv);
	pl_elements(meta_data, pl, argv);
	pl->checker = 0;
	pl->bump = 0;
	pl_bonus(meta_data, pl, argv);
	pl->next = NULL;
	ft_printf(G" OK \n"RST);
	return (pl);
}

t_pl	*check_pl_args(t_meta *meta_data, char **argv)
{
	t_pl	*pl;

	if (pointer_count(argv) < 4 || pointer_count(argv) > 6)
	{
		ft_printf(RED"Incorrect PL data <cy X,Y,Z NVector diameter height RGB\
			[checkerboard] [bumpmap]>\n"RST);
		free_args(meta_data, argv);
		exit(EXIT_FAILURE);
	}
	pl = malloc(sizeof(t_pl));
	if (!pl)
	{
		free_args(meta_data, argv);
		exit(EXIT_FAILURE);
	}
	return (pl);
}
