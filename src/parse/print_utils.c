#include "../../include/miniRT.h"

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

void    print_cones(t_meta *meta_data)
{
    t_cn *current_cn = meta_data->cn;

    while (current_cn != NULL)
    {
        printf("cn: (%f, %f, %f) (%f, %f, %f)\n",\
            current_cn->coord.x, current_cn->coord.y,current_cn->coord.z, \
            current_cn->axis.x, current_cn->axis.y, current_cn->axis.z);
        current_cn = current_cn->next;
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