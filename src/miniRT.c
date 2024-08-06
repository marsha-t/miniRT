#include "../include/miniRT.h"

int main(int argc, char **argv)
{
    static t_meta meta_data;

    // meta_data.mlx_ptr = mlx_init();
    // if (!meta_data.mlx_ptr)
    //     return (0);
    map_data(&meta_data, argc, argv);
    printf("cy: %f,%f,%f %f,%f,%f\n", meta_data.cy->coord.x, meta_data.cy->coord.y, meta_data.cy->coord.z, meta_data.cy->axis.x, meta_data.cy->axis.y, meta_data.cy->axis.z);
    printf("cy: %f,%f,%f %f,%f,%f\n", meta_data.cy->next->coord.x, meta_data.cy->next->coord.y, meta_data.cy->next->coord.z, meta_data.cy->next->axis.x, meta_data.cy->next->axis.y, meta_data.cy->next->axis.z);
    return (0);
}

void	map_data(t_meta *meta_data, int argc, char **argv)
{
	ft_check_args(argc, argv);
	data_init(meta_data, argv[1]);
}

void    data_init(t_meta *meta_data, char *argv)
{
    char    *singleline;
    char    **split_str;
    int     fd;

    ft_printf("argv %s\n", argv);
    fd = get_fd(argv);
    while (1)
    {
        singleline = get_next_line(fd);
        ft_printf("%s\n", singleline);
        if (!singleline)
        {
            free(singleline);
            break ;
        }
        split_str = ft_split(singleline, ' ');
        ft_fill_data(meta_data, split_str);
        ft_printf("ads\n");
        // free_pointer(split_str);
        ft_printf("adsaasg\n");
        free(singleline);
        singleline = NULL;
    }
}

void    ft_fill_data(t_meta *meta_data, char **argv)
{
    static int pl;
    static int sp;
    static int cy;

    if (ft_strncmp(argv[0], "A", 1) == 0 && ft_strlen(argv[0]) == 1)
        fill_ambient(meta_data, argv);
    else if (ft_strncmp(argv[0], "C", 1) == 0 && ft_strlen(argv[0]) == 1)
        fill_camera(meta_data, argv);
    else if (ft_strncmp(argv[0], "L", 1) == 0 && ft_strlen(argv[0]) == 1)
        fill_light(meta_data, argv);
    else if (ft_strncmp(argv[0], "pl", 2) == 0 && ft_strlen(argv[0]) == 2)
    {
        if (pl++ == 0)
            meta_data->pl = create_pl(argv);
        else
            meta_data->pl->next = create_pl(argv);
    }
    else if (ft_strncmp(argv[0], "sp", 2) == 0 && ft_strlen(argv[0]) == 2)
    {
        if (sp++ == 0)
            meta_data->sp = create_sp(argv);
        else
            meta_data->sp->next = create_sp(argv);
    }
    else if (ft_strncmp(argv[0], "cy", 2) == 0 && ft_strlen(argv[0]) == 2)
    {
        if (cy++ == 0)
            meta_data->cy = create_cy(argv);
        else
            meta_data->cy->next = create_cy(argv);
    }
    ft_printf("pl %d sp %d cy %d\n", pl, sp, cy);
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
    ft_printf("free pointer count %d\n", count);
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

    if (pointer_count(argv) != 3)
    {
        ft_printf("Incorrect ambient data <A ratio RGBcolors>\n");
        exit(EXIT_FAILURE);
    }
    meta_data->amlight = malloc(sizeof(t_amlight *));
    meta_data->amlight->amlight_ratio = ft_atoi(argv[1]);
    rgb = ft_split(argv[2], ',');
    meta_data->amlight->colour.r = ft_atoi(rgb[0]);
    meta_data->amlight->colour.g = ft_atoi(rgb[1]);
    meta_data->amlight->colour.b = ft_atoi(rgb[2]);
    free_pointer(rgb);
}

void    fill_camera(t_meta *meta_data, char **argv)
{
    char    **coord_p;
    char    **orient_p;

    if (pointer_count(argv) != 4)
    {
        ft_printf("Incorrect camera data <C X,Y,Z NormalizedVector FOV>\n");
        exit(EXIT_FAILURE);
    }
    meta_data->camera = malloc(sizeof(t_camera *));
    coord_p = ft_split(argv[1], ',');
    meta_data->camera->coord.x = ft_strtof(coord_p[0]);
    meta_data->camera->coord.y = ft_strtof(coord_p[1]);
    meta_data->camera->coord.z = ft_strtof(coord_p[2]);
    orient_p = ft_split(argv[2], ',');
    ft_printf("enter here 2\n");
    meta_data->camera->orient.x = ft_strtof(orient_p[0]);
    meta_data->camera->orient.y = ft_strtof(orient_p[1]);
    meta_data->camera->orient.z = ft_strtof(orient_p[2]);
    meta_data->camera->fov = ft_atoi(argv[3]);
    ft_printf("enter here 3\n");
    // free_pointer(coord_p);
    // free_pointer(orient_p);
    ft_printf("enter here 4\n");
}

void    fill_light(t_meta *meta_data, char **argv)
{
    char    **coordlight_p;
    char    **rgb;

    if (pointer_count(argv) != 4)
    {
        ft_printf("Incorrect camera data <C X,Y,Z brightness RGB>\n");
        exit(EXIT_FAILURE);
    }
    meta_data->light = malloc(sizeof(t_light *));
    coordlight_p = ft_split(argv[1], ',');
    meta_data->light->coord.x = ft_strtof(coordlight_p[0]);
    meta_data->light->coord.y = ft_strtof(coordlight_p[1]);
    meta_data->light->coord.z = ft_strtof(coordlight_p[2]);
    meta_data->light->brightness = ft_strtof(argv[2]);
    rgb = ft_split(argv[3], ',');
    meta_data->light->colour.r = ft_atoi(rgb[0]);
    meta_data->light->colour.g = ft_atoi(rgb[1]);
    meta_data->light->colour.b = ft_atoi(rgb[2]);
    // free_pointer(coordlight_p);
    // free_pointer(rgb);
}

t_cy    *create_cy(char **argv)
{
    char    **coord;
    char    **axis;
    char    **colour;
    t_cy    *cy;

    cy = malloc(sizeof(t_cy *));
    if (pointer_count(argv) != 6)
    {
        ft_printf("Incorrect camera data <cy X,Y,Z NVector diameter height RGB>\n");
        exit(EXIT_FAILURE);
    }
    coord = ft_split(argv[1], ',');
    cy->coord.x = ft_strtof(coord[0]);
    cy->coord.y = ft_strtof(coord[1]);
    cy->coord.z = ft_strtof(coord[2]);
    axis = ft_split(argv[2], ',');
    cy->axis.x = ft_strtof(axis[0]);
    cy->axis.y = ft_strtof(axis[1]);
    cy->axis.z = ft_strtof(axis[2]);
    colour = ft_split(argv[5], ',');
    cy->colour.r = ft_atoi(colour[0]);
    cy->colour.g = ft_atoi(colour[1]);
    cy->colour.b = ft_atoi(colour[2]);
    cy->diameter = ft_strtof(argv[3]);
    cy->height = ft_strtof(argv[4]);
    // free_pointer(coord);
    // free_pointer(axis);
    // free_pointer(colour);
    return (cy);
}

t_pl    *create_pl(char **argv)
{
    t_pl    *pl;
    char    **coord;
    char    **normal;
    char    **colour;

    pl = malloc(sizeof(t_pl *));
    if (pointer_count(argv) != 4)
    {
        ft_printf("Incorrect camera data <pl X,Y,Z NVector RGB>\n");
        exit(EXIT_FAILURE);
    }
    coord = ft_split(argv[1], ',');
    pl->coord.x = ft_strtof(coord[0]);
    pl->coord.y = ft_strtof(coord[1]);
    pl->coord.z = ft_strtof(coord[2]);
    normal = ft_split(argv[2], ',');
    pl->normal.x = ft_strtof(normal[0]);
    pl->normal.y = ft_strtof(normal[1]);
    pl->normal.z = ft_strtof(normal[2]);
    colour = ft_split(argv[3], ',');
    pl->colour.r = ft_atoi(colour[0]);
    pl->colour.g = ft_atoi(colour[1]);
    pl->colour.b = ft_atoi(colour[2]);
    // free_pointer(coord);
    // free_pointer(normal);
    // free_pointer(colour);
    ft_printf("pl\n");
    return (pl);
}

t_sp    *create_sp(char **argv)
{
    t_sp    *sp;
    char    **coord;
    char    **colour;

    sp = malloc(sizeof(t_sp *));
    if (pointer_count(argv) != 4)
    {
        ft_printf("Incorrect camera data <sp X,Y,Z diameter RGB>\n");
        exit(EXIT_FAILURE);
    }
    coord = ft_split(argv[1], ',');
    sp->coord.x = ft_strtof(coord[0]);
    sp->coord.y = ft_strtof(coord[1]);
    sp->coord.z = ft_strtof(coord[2]);
    colour = ft_split(argv[3], ',');
    sp->colour.r = ft_atoi(colour[0]);
    sp->colour.g = ft_atoi(colour[1]);
    sp->colour.b = ft_atoi(colour[2]);
    sp->diameter = ft_strtof(argv[2]);
    // free_pointer(coord);
    // free_pointer(colour);
    return (sp);
}

void    ft_check_args(int argc, char **argv)
{
    char    *extnsn;

    if (argc != 2)
    {
        ft_putendl_fd("Wrong number of arguments...", 2);
        exit(EXIT_FAILURE);
    }
    extnsn = ft_strchr_gnl(argv[1] + 1, '.');
    if (!extnsn)
    {
        ft_putendl_fd("No .rt extension...", 2);
        exit(EXIT_FAILURE);
    }
    if (ft_strncmp(extnsn, ".rt", 3) && ft_strlen(extnsn) != 3)
    {
        ft_putendl_fd("Wrong extension (no .rt extension)", 2);
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
        ft_printf("File %s can not be found.\n", argv);
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