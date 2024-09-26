/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:07:18 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/26 09:44:17 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	sp_elements(t_meta *meta_data, t_sp *sp, char **argv)
{
	char	**coord;
	char	**colour;

	coord = ft_split(argv[1], ',');
	sp->coord = check_coord(&meta_data, sp, argv, coord);
	free_pointer(coord);
	colour = ft_split(argv[3], ',');
	sp->colour = check_colour(&meta_data, sp, argv, colour);
	free_pointer(colour);
}

void	sp_bonus(t_meta *meta_data, t_sp *sp, char **argv)
{
	int		i;
	char	**bonus;

	i = 3;
	while (argv[++i])
	{
		bonus = ft_split(argv[i], ',');
		if (bonus[0][0] == 'c')
		{
			sp->checker = 1;
			sp->sqsize = check_checker(&meta_data, sp, argv, bonus);
			free_pointer(bonus);
		}
		else if (bonus[0][0] == 'b')
		{
			sp->bump = 1;
			sp->bump_img = check_bump(&meta_data, sp, argv, bonus);
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
	create_sp creates a sphere object and check if each value is valid.
	returns t_sp pointer.
*/
t_sp	*create_sp(t_meta *meta_data, char **argv)
{
	t_sp	*sp;

	ft_printf(G"\tSPHERE OBJECT ...\t"RST);
	sp = check_sp_args(meta_data, argv);
	sp_elements(meta_data, sp, argv);
	sp->diameter = check_double(&meta_data, sp, argv, argv[2]);
	sp->checker = 0;
	sp->bump = 0;
	sp_bonus(meta_data, sp, argv);
	sp->next = NULL;
	ft_printf(G" OK \n"RST);
	return (sp);
}

t_sp	*check_sp_args(t_meta *meta_data, char **argv)
{
	t_sp	*sp;

	if (pointer_count(argv) < 4 || pointer_count(argv) > 6)
	{
		ft_printf(RED"Incorrect SP data <cy X,Y,Z diameter RGB\
			[checkerboard] [bumpmap]>\n"RST);
		free_args(meta_data, argv);
		exit(EXIT_FAILURE);
	}
	sp = malloc(sizeof(t_sp));
	if (!sp)
	{
		free_args(meta_data, argv);
		exit(EXIT_FAILURE);
	}
	return (sp);
}
