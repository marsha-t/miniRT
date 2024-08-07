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
    static t_meta meta_data;

    // meta_data.mlx_ptr = mlx_init();
    // if (!meta_data.mlx_ptr)
    //     return (0);
    print_banner();
    parse_data(&meta_data, argc, argv);
    print_cylinders(&meta_data);
    print_spheres(&meta_data);
    print_planes(&meta_data);
    // printf("cy: %f,%f,%f %f,%f,%f\n", meta_data.cy->coord.x, meta_data.cy->coord.y, meta_data.cy->coord.z, meta_data.cy->axis.x, meta_data.cy->axis.y, meta_data.cy->axis.z);
    // printf("cy: %f,%f,%f %f,%f,%f\n", meta_data.cy->next->coord.x, meta_data.cy->next->coord.y, meta_data.cy->next->coord.z, meta_data.cy->next->axis.x, meta_data.cy->next->axis.y, meta_data.cy->next->axis.z);
    free_exit(&meta_data);
    return (0);
}

void    print_cylinders(t_meta *meta_data)
{
    t_cy *current_cy = meta_data->cy;

    while (current_cy != NULL)
    {
        printf("cy: (%f, %f, %f) (%f, %f, %f)\n",\
            current_cy->coord.x, current_cy->coord.y,current_cy->coord.z, \
            current_cy->axis.x, current_cy->axis.y, current_cy->axis.z);
        current_cy = current_cy->next;
    }
}

void    print_spheres(t_meta *meta_data)
{
    t_sp *current_sp = meta_data->sp;

    while (current_sp != NULL)
    {
        printf("sp: (%f, %f, %f) (%d, %d, %d)\n",\
            current_sp->coord.x, current_sp->coord.y,current_sp->coord.z, \
            current_sp->colour.r, current_sp->colour.g, current_sp->colour.b);
        current_sp = current_sp->next;
    }
}

void    print_planes(t_meta *meta_data)
{
    t_pl *current_pl = meta_data->pl;

    while (current_pl != NULL)
    {
        printf("pl: (%f, %f, %f) (%f, %f, %f)\n",\
            current_pl->coord.x, current_pl->coord.y,current_pl->coord.z, \
            current_pl->normal.x, current_pl->normal.y, current_pl->normal.z);
        current_pl = current_pl->next;
    }
}

void    print_banner()
{
    ft_printf(Y" _____________________________________\n");
    ft_printf("|            _       _ _____ _______  |\n");
    ft_printf("|           (_)     (_)  __ \\__   __| |\n");
    ft_printf("|  _ __ ___  _ _ __  _| |__) | | |    |\n");
    ft_printf("| | '_ ` _ \\| | '_ \\| |  _  /  | |    |\n");
    ft_printf("| | | | | | | | | | | | | \\ \\  | |    |\n");
    ft_printf("| |_| |_| |_|_|_| |_|_|_|  \\_\\ |_|    |\n");
    ft_printf("|_____________________________________|\n"RST);
    ft_printf(B"\t\t    by: mateo|emaravil\n"RST);
    return ;
}

void    free_exit(t_meta *meta_data)
{
    if (meta_data->amlight != NULL)
        free(meta_data->amlight);
    if (meta_data->camera != NULL)
        free(meta_data->camera);
    if (meta_data->light != NULL)
        free(meta_data->light);
    free_objects(meta_data);
}

void    free_objects(t_meta *meta_data)
{
    t_sp    *sp;
    t_cy    *cy;
    t_pl    *pl;

    sp = meta_data->sp;
    cy = meta_data->cy;
    pl = meta_data->pl;
    while (meta_data->sp != NULL)
    {
        sp = sp->next;
        free(meta_data->sp);
        meta_data->sp = sp;
    }
    while (meta_data->cy != NULL)
    {
        cy = cy->next;
        free(meta_data->cy);
        meta_data->cy = cy;
    }
    while (meta_data->pl != NULL)
    {
        pl = pl->next;
        free(meta_data->pl);
        meta_data->pl = pl;
    }
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
        while (ft_isspace(singleline[index - 1]) > 0)
        {
            singleline[index - 1] = '\0';
            index--;
        }
        ft_fill_data(meta_data, singleline);
    }
}

void create_objects(t_meta *meta_data, char **argv)
{
    static int pl;
    static int sp;
    static int cy;
    t_cy *temp_cy;
    t_pl *temp_pl;
    t_sp *temp_sp;

    if (ft_strncmp(argv[0], "pl", 2) == 0 && ft_strlen(argv[0]) == 2)
    {
        if (pl == 0)
            meta_data->pl = create_pl(meta_data, argv);
        else
        {
            temp_pl = meta_data->pl;
            while (temp_pl->next != NULL)
                temp_pl = temp_pl->next;
            temp_pl->next = create_pl(meta_data, argv);
        }
        pl++;
    }
    else if (ft_strncmp(argv[0], "sp", 2) == 0 && ft_strlen(argv[0]) == 2)
    {
        if (sp == 0)
            meta_data->sp = create_sp(meta_data, argv);
        else
        {
            temp_sp = meta_data->sp;
            while (temp_sp->next != NULL)
                temp_sp = temp_sp->next;
            temp_sp->next = create_sp(meta_data, argv);
        }
        sp++;
    }
    else if (ft_strncmp(argv[0], "cy", 2) == 0 && ft_strlen(argv[0]) == 2)
    {
        if (cy == 0)
            meta_data->cy = create_cy(meta_data, argv);
        else
        {
            temp_cy = meta_data->cy;
            while (temp_cy->next != NULL)
                temp_cy = temp_cy->next;
            temp_cy->next = create_cy(meta_data, argv);
        }
        cy++;
    }
}

void    ft_fill_data(t_meta *meta_data, char *singleline)
{
    char **argv;
    static int count;

    argv = ft_split(singleline, ' ');
    free(singleline);
    ft_printf(B"Line %d"RST, ++count);
    if (ft_strncmp(argv[0], "A", 1) == 0 && ft_strlen(argv[0]) == 1)
    {
        fill_ambient(meta_data, argv);
        ft_printf(G" OK \n"RST);
    }
    else if (ft_strncmp(argv[0], "C", 1) == 0 && ft_strlen(argv[0]) == 1)
    {
        fill_camera(meta_data, argv);
        ft_printf(G" OK \n"RST);
    }
    else if (ft_strncmp(argv[0], "L", 1) == 0 && ft_strlen(argv[0]) == 1)
    {
        fill_light(meta_data, argv);
        ft_printf(G" OK \n"RST);
    }
    else if ((ft_strncmp(argv[0], "pl", 2) == 0 || \
        ft_strncmp(argv[0], "sp", 2) == 0 \
        || ft_strncmp(argv[0], "cy", 2) == 0) && ft_strlen(argv[0]) == 2)
        create_objects(meta_data, argv);
    else
    {
        ft_printf(RED"\tUNKNOWN OBJECT FOUND ...\n"RST);
        free_pointer(argv);
        free_exit(meta_data);
        exit(EXIT_FAILURE);
    }
    free_pointer(argv);
}

int     pointer_count(char **argv)
{
    int count;

    count = 0;
    while (argv[count])
        count++;
    return (count);
}

void	free_pointer(char **s)
{
	int	count;
	int	len;

	len = ft_strlen_dp(s);
	count = 0;
	while (count < len)
	{
		free(s[count]);
		count++;
	}
	free(s);
    s = NULL;
}

int	ft_strlen_dp(char **s)
{
	int	count;

	count = 0;
	while (s[count] != NULL)
	{
		count++;
	}
	return (count);
}

void    fill_ambient(t_meta *meta_data, char **argv)
{
    char    **rgb;
    static int count;

    meta_data->amlight = NULL;
    ft_printf(G"\tAMBIENT LIGHT ...\t"RST);
    if (pointer_count(argv) != 3 || (count > 0))
    {
        if ((count > 0))
            ft_printf(RED"\tMultiple declaration of Ambient light values\n"RST);
        else
            ft_printf(RED"\tIncorrect ambient data <A ratio RGBcolors>\n"RST);
        free_exit(meta_data);
        exit(EXIT_FAILURE);
    }
    count++;
    meta_data->amlight = malloc(sizeof(t_amlight));
    meta_data->amlight->amlight_ratio = check_double(&meta_data, NULL, argv, argv[1]);
    rgb = ft_split(argv[2], ',');
    meta_data->amlight->colour = check_colour(&meta_data, NULL, argv, rgb);
    free_pointer(rgb);
}

void    fill_camera(t_meta *meta_data, char **argv)
{
    char    **coord_p;
    char    **orient_p;
    static int count;

    ft_printf(G"\tCAMERA SETTINGS ...\t"RST);
    if (pointer_count(argv) != 4)
    {
        ft_printf(RED"Incorrect camera data <C XYZ NormVector FOV>\n" RST);
        free_exit(meta_data);
        exit(EXIT_FAILURE);
    }
    if (count > 0)
    {
        ft_printf(RED"Multiple declaration of Camera values\n"RST);
        free_exit(meta_data);
        exit(EXIT_FAILURE);
    }
    count++;
    meta_data->camera = malloc(sizeof(t_camera));
    coord_p = ft_split(argv[1], ',');
    meta_data->camera->coord = check_coord(&meta_data, NULL, argv, coord_p);
    orient_p = ft_split(argv[2], ',');
    meta_data->camera->orient = check_norm(&meta_data, NULL, argv, orient_p);
    meta_data->camera->fov = check_double(&meta_data, NULL, argv, argv[3]);
    free_pointerlist(2, coord_p, orient_p);
}

void    fill_light(t_meta *meta_data, char **argv)
{
    char    **coordlight_p;
    char    **rgb;
    static int count;

    ft_printf(G"\tLIGHT SETTINGS ...\t"RST);
    if (pointer_count(argv) != 4)
    {
        ft_printf(RED"Incorrect camera data <C X,Y,Z brightness RGB>\n"RST);
        free_exit(meta_data);
        exit(EXIT_FAILURE);
    }
    if (count > 0)
    {
        ft_printf(RED"Multiple declaration of Light values\n"RST);
        free_exit(meta_data);
        exit(EXIT_FAILURE);
    }
    count++;
    meta_data->light = malloc(sizeof(t_light));
    coordlight_p = ft_split(argv[1], ',');
    meta_data->light->coord = check_coord(&meta_data, NULL, argv, coordlight_p);
    meta_data->light->brightness = check_double(&meta_data, NULL, argv, argv[2]);
    rgb = ft_split(argv[3], ',');
    meta_data->light->colour = check_colour(&meta_data, NULL, argv, rgb);
    free_pointerlist(2, coordlight_p, rgb);
}

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
                free_exit(*meta_data);
                if (temp != NULL)
                    free(temp);
                free_pointerlist(2, src, argv);
                ft_printf(RED"Incorrect XYZ input values\n"RST);
                exit(EXIT_FAILURE);
            }
        }
    }
    vec.x = ft_strtod(argv[0]);
    vec.y = ft_strtod(argv[1]);
    vec.z = ft_strtod(argv[2]);
    return (vec);
}

t_vector    check_norm(t_meta **meta_data, void *temp, char **src, char **argv)
{
    t_vector    vec;
    int         arg_count;

    arg_count = -1;
    while(argv[++arg_count])
    {
        if (!(check_norm_val(*meta_data, src, arg_count, argv)))
        {
            if (temp != NULL)
                free(temp);
            exit(EXIT_FAILURE);
        }
    }
    vec.x = ft_strtod(argv[0]);
    vec.y = ft_strtod(argv[1]);
    vec.z = ft_strtod(argv[2]);
    return (vec);
}

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

bool    check_norm_val(t_meta *meta_data, char **src, int arg_count, char **argv)
{
    double temp;
    int index;

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
    temp = ft_strtod(argv[arg_count]);
    if (temp < -1 || temp > 1 || arg_count >= 3)
    {
        free_exit(meta_data);
        ft_printf(RED"A Incorrect normal vector input values\n"RST);
        free_pointerlist(2, src, argv);
        return (false);
    }
    return (true);
}

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
    rgb.r = ft_atoi(argv[0]);
    rgb.g = ft_atoi(argv[1]);
    rgb.b = ft_atoi(argv[2]);
    return (rgb);
}

t_cy    *create_cy(t_meta *meta_data, char **argv)
{
    char    **coord;
    char    **axis;
    char    **colour;
    t_cy    *cy;

    ft_printf(G"\tCYLINDER OBJECT ...\t"RST);
    if (pointer_count(argv) != 6)
    {
        ft_printf("Incorrect CY data <cy X,Y,Z NVector diameter height RGB>\n");
        free_exit(meta_data);
        exit(EXIT_FAILURE);
    }
    cy = malloc(sizeof(t_cy));
    if (!cy)
        exit(EXIT_FAILURE);
    coord = ft_split(argv[1], ',');
    cy->coord = check_coord(&meta_data, cy, argv, coord);
    free_pointer(coord);
    axis = ft_split(argv[2], ',');
    cy->axis = check_norm(&meta_data, cy, argv, axis);
    free_pointer(axis);
    colour = ft_split(argv[5], ',');
    cy->colour = check_colour(&meta_data, cy, argv, colour);
    free_pointer(colour);
    cy->diameter = check_double(&meta_data, cy, argv, argv[3]);
    cy->height = check_double(&meta_data, cy, argv, argv[4]);
    cy->next = NULL;
    ft_printf(G" OK \n"RST);
    return (cy);
}

t_pl    *create_pl(t_meta *meta_data, char **argv)
{
    t_pl    *pl;
    char    **coord;
    char    **normal;
    char    **colour;

    ft_printf(G"\tPLANE OBJECT ...\t"RST);
    if (pointer_count(argv) != 4)
    {
        ft_printf("Incorrect PL data <cy X,Y,Z NVector diameter height RGB>\n");
        free_exit(meta_data);
        exit(EXIT_FAILURE);
    }
    pl = malloc(sizeof(t_pl));
    if (!pl)
        exit(EXIT_FAILURE);
    coord = ft_split(argv[1], ',');
    pl->coord = check_coord(&meta_data, pl, argv, coord);
    free_pointer(coord);
    normal = ft_split(argv[2], ',');
    pl->normal = check_norm(&meta_data, pl, argv, normal);
    free_pointer(normal);
    colour = ft_split(argv[3], ',');
    pl->colour = check_colour(&meta_data, pl, argv, colour);
    free_pointer(colour);
    pl->next = NULL;
    ft_printf(G" OK \n"RST);
    return (pl);
}

void    free_pointerlist(int num, ...)
{
    va_list args;
    void    **ptr;
    int     index;

    index = 0;
    va_start(args, num);
    while (index < num)
    {
        ptr = va_arg(args, void **);
        if (ptr != NULL)
            free_pointer((char **)ptr);
        index++;
    }
    va_end(args);
}
t_sp    *create_sp(t_meta *meta_data, char **argv)
{
    t_sp    *sp;
    char    **coord;
    char    **colour;

    ft_printf(G"\tSPHERE OBJECT ...\t"RST);
    if (pointer_count(argv) != 4)
    {
        ft_printf(RED"Incorrect SP data <sp X,Y,Z diameter RGB>\n"RST);
        exit(EXIT_FAILURE);
    }
    sp = malloc(sizeof(t_sp));
    if (!sp)
        exit(EXIT_FAILURE);
    coord = ft_split(argv[1], ',');
    sp->coord = check_coord(&meta_data, sp, argv, coord);
    free_pointer(coord);
    colour = ft_split(argv[3], ',');
    sp->colour = check_colour(&meta_data, sp, argv, colour);
    free_pointer(colour);
    sp->diameter = check_double(&meta_data, sp, argv, argv[2]);
    sp->next = NULL;
    ft_printf(G" OK \n"RST);
    return (sp);
}

void    ft_check_args(int argc, char **argv)
{
    char    *extnsn;

    if (argc != 2)
    {
        ft_putendl_fd(RED"\tWrong number of arguments..."RST, 2);
        exit(EXIT_FAILURE);
    }
    extnsn = ft_strchr_gnl(argv[1] + 1, '.');
    if (!extnsn)
    {
        ft_putendl_fd(RED"\tNo .rt extension..."RST, 2);
        exit(EXIT_FAILURE);
    }
    if (ft_strncmp(extnsn, ".rt", 3) && ft_strlen(extnsn) != 3)
    {
        ft_putendl_fd(RED"\tWrong extension (no .rt extension)"RST, 2);
        exit(EXIT_FAILURE);
    }
    check_fd(argv[1]);
}

void    check_fd(char *argv)
{
    int fd;

    fd = get_fd(argv);
    if (fd < 0)
    {
        ft_printf(RED"\tFile %s can not be found.\n"RST, argv);
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
}

int	get_fd(char *argv)
{
	char	*filedirectory;
	int		fd;

	filedirectory = argv;
	fd = open(filedirectory, O_RDONLY);
	return (fd);
}