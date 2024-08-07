#include "../../include/miniRT.h"

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
