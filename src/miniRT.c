/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:47:25 by emaravil          #+#    #+#             */
/*   Updated: 2024/08/07 18:51:48 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int main(int argc, char **argv)
{
    t_meta meta_data;

    print_banner();
    parse_data(&meta_data, argc, argv);
    print_cylinders(&meta_data);
    print_spheres(&meta_data);
    print_planes(&meta_data);
    print_cones(&meta_data);
    free_exit(&meta_data);
    return (0);
}

void	parse_data(t_meta *meta_data, int argc, char **argv)
{
    ft_printf(Y"\nPARSING DATA FROM "RST);
    ft_printf("\t%s...\n", argv[1]);
	ft_check_args(argc, argv);
	read_data(meta_data, argv[1]);
    ft_printf(M"PARSING DATA  ...\t\t OK\n"RST);
}

void    read_data(t_meta *meta_data, char *argv)
{
    char    *singleline;
    int     fd;
    int     index;

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
        while (singleline[index++] != '\n')
            ;
        while (index >= 1 && ft_isspace(singleline[index - 1]) > 0)
        {
            singleline[index - 1] = '\0';
            index--;
        }
        if ((singleline[0] != '\n') && singleline[0] != '#' && (ft_strlen(singleline) > 0))
            ft_fill_data(meta_data, singleline);
        else if (singleline[0] == '\n' || singleline[0] == '#')
            free(singleline);
        else
            free(singleline);
    }
}
