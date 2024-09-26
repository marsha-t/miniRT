/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:47:33 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/26 11:22:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	parse_data(t_meta *meta_data, int argc, char **argv)
{
	ft_printf(Y"\nPARSING DATA FROM "RST);
	ft_printf("\t%s...\n", argv[1]);
	ft_check_args(argc, argv);
	read_data(meta_data, argv[1]);
	ft_printf(M"PARSING DATA  ...\t\t OK\n"RST);
	if (!meta_data->camera_allocated)
	{
		free_exit(meta_data);
		printf(RED"No camera allocated!\n"RST);
		exit(EXIT_FAILURE);
	}
	meta_data->obj_option->orient = &meta_data->camera->orient;
	meta_data->obj_option->coord = &meta_data->camera->coord;
	meta_data->orient = meta_data->camera->orient;
}

void	read_data(t_meta *meta_data, char *argv)
{
	char	*singleline;
	int		fd;
	int		index;

	fd = get_fd(argv);
	while (1)
	{
		index = 0;
		singleline = get_next_line(fd);
		if (!singleline)
		{
			free(singleline);
			break ;
		}
		clean_data(meta_data, singleline, index);
	}
}

void	clean_data(t_meta *meta_data, char	*singleline, int index)
{
	if ((ft_strchr(singleline, '\n')))
	{
		while (singleline[index++] != '\n')
			;
		while (index >= 1 && ft_isspace(singleline[index - 1]) > 0)
		{
			singleline[index - 1] = '\0';
			index--;
		}
	}
	if (*singleline && (singleline[0] != '\n') && singleline[0] != '#' && \
		(ft_strlen(singleline) > 0))
		ft_fill_data(meta_data, singleline);
	else
		free(singleline);
}
