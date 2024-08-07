#include "../../include/miniRT.h"

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
