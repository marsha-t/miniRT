#include "../../include/miniRT.h"

/*
    ft_fill_data checks the singleline for each id from the .rt file.
    Subsequently it assigns to the associated function of each id.
    if an unknown id is declared in the .rt file, the function exits
    the program
*/
void    ft_fill_data(t_meta *meta_data, char *singleline)
{
    char **argv;
    static int light_count;
    static int spot_light_count;
    t_light *temp_light;
    t_spotlight *temp_spotlight;

    argv = ft_split(singleline, ' ');
    free(singleline);
    if (ft_strncmp(argv[0], "A", 1) == 0 && ft_strlen(argv[0]) == 1)
    {
        fill_ambient(meta_data, argv);
        meta_data->amlight_allocated = true;
        ft_printf(G" OK \n"RST);
    }
    else if (ft_strncmp(argv[0], "C", 1) == 0 && ft_strlen(argv[0]) == 1)
    {
        fill_camera(meta_data, argv);
        meta_data->camera_allocated = true;
        ft_printf(G" OK \n"RST);
    }
    else if (ft_strncmp(argv[0], "L", 1) == 0 && ft_strlen(argv[0]) == 1)
    {
        if (light_count == 0)
        {
            meta_data->light = create_light(meta_data, argv);
            meta_data->light_allocated = true;
        }
        else
        {
            temp_light = meta_data->light;
            while (temp_light->next != NULL)
                temp_light = temp_light->next;
            temp_light->next = create_light(meta_data, argv);
        }
        light_count++;
    }
    else if (ft_strncmp(argv[0], "SL", 1) == 0 && ft_strlen(argv[0]) == 2)
    {
        if (spot_light_count == 0)
        {
            meta_data->spotlight = create_spotlight(meta_data, argv);
            meta_data->sl_allocated = true;
        }
        else
        {
            temp_spotlight = meta_data->spotlight;
            while (temp_spotlight->next != NULL)
                temp_spotlight = temp_spotlight->next;
            temp_spotlight->next = create_spotlight(meta_data, argv);
        }
        spot_light_count++;
    }
    else if ((ft_strncmp(argv[0], "pl", 2) == 0 || \
        ft_strncmp(argv[0], "sp", 2) == 0 || ft_strncmp(argv[0], "cy", 2) == 0 || \
        ft_strncmp(argv[0], "cn", 2) == 0) && ft_strlen(argv[0]) == 2)
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

/*
    fill_ambient associats with the ambient setting of the ray tracing.
    this function fills out the amlight pointer of t_meta struct.
    allocates t_amlight and fills out the input values from the .rt file.
*/
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
        free_pointer(argv);
        free_exit(meta_data);
        exit(EXIT_FAILURE);
    }
    count++;
    meta_data->amlight = malloc(sizeof(t_amlight));
    if (!meta_data->amlight)
    {
        free_pointer(argv);
        free_exit(meta_data);
        exit(EXIT_FAILURE);
    }
    meta_data->amlight->amlight_ratio = check_double(&meta_data, NULL, argv, argv[1]);
    rgb = ft_split(argv[2], ',');
    meta_data->amlight->colour = check_colour(&meta_data, NULL, argv, rgb);
    free_pointer(rgb);
}

/*
    fill_camera associats with the camera setting of the ray tracing.
    this function fills out the camera pointer of t_meta struct.
    allocates t_camera and fills out the input values from the .rt file.
*/
void    fill_camera(t_meta *meta_data, char **argv)
{
    char    **coord_p;
    char    **orient_p;
    static int count;

    ft_printf(G"\tCAMERA SETTINGS ...\t"RST);
    if (pointer_count(argv) != 4)
    {
        ft_printf(RED"Incorrect camera data <C XYZ NormVector FOV>\n" RST);
        free_pointer(argv);
        free_exit(meta_data);
        exit(EXIT_FAILURE);
    }
    if (count > 0)
    {
        ft_printf(RED"Multiple declaration of Camera values\n"RST);
        free_pointer(argv);
        free_exit(meta_data);
        exit(EXIT_FAILURE);
    }
    count++;
    meta_data->camera = malloc(sizeof(t_camera));
    if (!meta_data->camera)
    {
        free_pointer(argv);
        free_exit(meta_data);
        exit(EXIT_FAILURE);
    }
    coord_p = ft_split(argv[1], ',');
    meta_data->camera->coord = check_coord(&meta_data, NULL, argv, coord_p);
    free_pointer(coord_p);
    orient_p = ft_split(argv[2], ',');
    meta_data->camera->orient = check_norm(&meta_data, NULL, argv, orient_p);
    vec_normalise(&meta_data->camera->orient);
    free_pointer(orient_p);
    meta_data->camera->fov = check_double(&meta_data, NULL, argv, argv[3]);
    if (meta_data->camera->fov > 180)
    {
        free_pointer(argv);
        free_exit(meta_data);
        exit(EXIT_FAILURE);
    }
}

/*
    create_light creates a light source object and check if each value is valid.
    returns t_light pointer.
*/
t_light    *create_light(t_meta *meta_data, char **argv)
{
    char    **coordlight_p;
    char    **rgb;
    t_light *temp_light;

    ft_printf(G"\tLIGHT SETTINGS ...\t"RST);
    if (pointer_count(argv) != 4)
    {
        ft_printf(RED"Incorrect LIGHT data <C X,Y,Z brightness RGB>\n"RST);
        free_pointer(argv);
        free_exit(meta_data);
        exit(EXIT_FAILURE);
    }
    temp_light = malloc(sizeof(t_light));
    if (!temp_light)
    {
        free_pointer(argv);
        free_exit(meta_data);
        exit(EXIT_FAILURE);
    }
    coordlight_p = ft_split(argv[1], ',');
    temp_light->coord = check_coord(&meta_data, temp_light, argv, coordlight_p);
    free_pointer(coordlight_p);
    temp_light->brightness = check_double(&meta_data, temp_light, argv, argv[2]);
    rgb = ft_split(argv[3], ',');
    temp_light->colour = check_colour(&meta_data, temp_light, argv, rgb);
    free_pointer(rgb);
    temp_light->next = NULL;
    ft_printf(G" OK \n"RST);
    return (temp_light);
}

t_spotlight    *create_spotlight(t_meta *meta_data, char **argv)
{
    char    **coordspotlight_p;
    char    **rgb;
    char    **spot_dir;
    t_spotlight *temp_spotlight;

    ft_printf(G"\tSPOTLIGHT SETTINGS ...\t"RST);
    if (pointer_count(argv) != 5)
    {
        ft_printf(RED"Incorrect SPOTLIGHT data <C X,Y,Z brightness RGB>\n"RST);
        free_pointer(argv);
        free_exit(meta_data);
        exit(EXIT_FAILURE);
    }
    temp_spotlight = malloc(sizeof(t_spotlight));
    if (!temp_spotlight)
    {
        free_pointer(argv);
        free_exit(meta_data);
        exit(EXIT_FAILURE);
    }
    coordspotlight_p = ft_split(argv[1], ',');
    temp_spotlight->coord = check_coord(&meta_data, temp_spotlight, argv, coordspotlight_p);
    free_pointer(coordspotlight_p);
    spot_dir = ft_split(argv[2], ',');
    temp_spotlight->spot_dir = check_norm(&meta_data, temp_spotlight, argv, spot_dir);
    free_pointer(spot_dir);
    temp_spotlight->brightness = check_double(&meta_data, temp_spotlight, argv, argv[3]);
    rgb = ft_split(argv[4], ',');
    temp_spotlight->colour = check_colour(&meta_data, temp_spotlight, argv, rgb);
    free_pointer(rgb);
    temp_spotlight->next = NULL;
    ft_printf(G" OK \n"RST);
    return (temp_spotlight);
}