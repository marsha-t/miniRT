#include "../../include/miniRT.h"

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


