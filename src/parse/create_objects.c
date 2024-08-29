#include "../../include/miniRT.h"

/*
	create_objects checks argv[0] to the id of each objects. 
	goes to each function of creating each object based on the id
*/
void create_objects(t_meta *meta_data, char **argv)
{
	static int pl;
	static int sp;
	static int cy;
	static int cn;
	t_cy *temp_cy;
	t_pl *temp_pl;
	t_sp *temp_sp;
	t_cn *temp_cn;

	if (ft_strncmp(argv[0], "pl", 2) == 0 && ft_strlen(argv[0]) == 2)
	{
		if (pl == 0)
		{
			meta_data->pl = create_pl(meta_data, argv);
			meta_data->pl_allocated = true;
		}
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
		{
			meta_data->sp = create_sp(meta_data, argv);
			meta_data->sp_allocated = true;
		}
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
		{
			meta_data->cy = create_cy(meta_data, argv);
			meta_data->cy_allocated = true;
		}
		else
		{
			temp_cy = meta_data->cy;
			while (temp_cy->next != NULL)
				temp_cy = temp_cy->next;
			temp_cy->next = create_cy(meta_data, argv);
		}
		cy++;
	}
	else if (ft_strncmp(argv[0], "cn", 2) == 0 && ft_strlen(argv[0]) == 2)
	{
		if (cn == 0)
		{
			meta_data->cn = create_cn(meta_data, argv);
			meta_data->cn_allocated = true;
		}
		else
		{
			temp_cn = meta_data->cn;
			while (temp_cn->next != NULL)
				temp_cn = temp_cn->next;
			temp_cn->next = create_cn(meta_data, argv);
		}
		cn++;
	}
}

/*
	create_pl creates a plane object and check if each value is valid.
	returns t_pl pointer.
*/
t_pl    *create_pl(t_meta *meta_data, char **argv)
{
	t_pl    *pl;
	char    **coord;
	char    **normal;
	char    **colour;
	int	i;
	char	**bonus;

	ft_printf(G"\tPLANE OBJECT ...\t"RST);
	if (pointer_count(argv) < 4 || pointer_count(argv) > 6)
	{
		ft_printf(RED"Incorrect PL data <cy X,Y,Z NVector diameter height RGB [checkerboard] [bumpmap]>\n"RST);
		free_pointer(argv);
		free_exit(meta_data);
		exit(EXIT_FAILURE);
	}
	pl = malloc(sizeof(t_pl));
	if (!pl)
	{
		free_pointer(argv);
		free_exit(meta_data);
		exit(EXIT_FAILURE);
	}
	coord = ft_split(argv[1], ',');
	pl->coord = check_coord(&meta_data, pl, argv, coord);
	free_pointer(coord);
	normal = ft_split(argv[2], ',');
	pl->normal = check_norm(&meta_data, pl, argv, normal);
	free_pointer(normal);
	colour = ft_split(argv[3], ',');
	pl->colour = check_colour(&meta_data, pl, argv, colour);
	free_pointer(colour);
	pl->checker = 0;
	pl->bump = 0;
	i = 3;
	while (argv[++i])
	{
		bonus = ft_split(argv[i], ',');
		if (bonus[0][0] == 'c')
		{
			pl->checker = 1;
			pl->sqsize = check_checker(&meta_data, pl, argv, bonus);
			free_pointer(bonus);
		}
		else if (bonus[0][0] == 't')
		{
			pl->bump = 1;
		}
		else
		{
			free_pointer(bonus);
			ft_printf(RED"Incorrect bonus\n"RST);
			free_exit(meta_data);
			exit(EXIT_FAILURE);
		}
	}
	pl->next = NULL;
	ft_printf(G" OK \n"RST);
	return (pl);
}

/*
	create_sp creates a sphere object and check if each value is valid.
	returns t_sp pointer.
*/
t_sp    *create_sp(t_meta *meta_data, char **argv)
{
	t_sp    *sp;
	char    **coord;
	char    **colour;
	int	i;
	char	**bonus;

	ft_printf(G"\tSPHERE OBJECT ...\t"RST);
	if (pointer_count(argv) < 4 || pointer_count(argv) > 6)
	{
		ft_printf(RED"Incorrect SP data <sp X,Y,Z diameter RGB [checkerboard] [bumpmap]>\n"RST);
		free_pointer(argv);
		free_exit(meta_data);
		exit(EXIT_FAILURE);
	}
	sp = malloc(sizeof(t_sp));
	if (!sp)
	{
		free_pointer(argv);
		free_exit(meta_data);
		exit(EXIT_FAILURE);
	}
	coord = ft_split(argv[1], ',');
	sp->coord = check_coord(&meta_data, sp, argv, coord);
	free_pointer(coord);
	colour = ft_split(argv[3], ',');
	sp->colour = check_colour(&meta_data, sp, argv, colour);
	free_pointer(colour);
	sp->diameter = check_double(&meta_data, sp, argv, argv[2]);
	sp->checker = 0;
	sp->bump = 0;
	i = 3;
	while (argv[++i])
	{
		bonus = ft_split(argv[i], ',');
		if (bonus[0][0] == 'c')
		{
			sp->checker = 1;
			sp->sqsize = check_checker(&meta_data, sp, argv, bonus);
			free_pointer(bonus);
			if (sp->sqsize.row < 1 || sp->sqsize.col < 1)
			{
				ft_printf(RED"Incorrect checkerboard square size values\n"RST);
				free_exit(meta_data);
				exit(EXIT_FAILURE);
			}
		}
		else if (bonus[0][0] == 'b')
		{
			sp->bump = 1;
			// sp->bump_map = check_bump(&meta_data, sp, argv, bonus);
		}
		else
		{
			free_pointer(bonus);
			ft_printf(RED"Incorrect bonus\n"RST);
			free_exit(meta_data);
			exit(EXIT_FAILURE);
		}
	}
	sp->next = NULL;
	ft_printf(G" OK \n"RST);
	return (sp);
}

/*
	create_cy creates a sphere object and check if each value is valid.
	returns t_cy pointer.
*/
t_cy    *create_cy(t_meta *meta_data, char **argv)
{
	char    **coord;
	char    **axis;
	char    **colour;
	t_cy    *cy;
	int	i;
	char	**bonus;

	ft_printf(G"\tCYLINDER OBJECT ...\t"RST);
	if (pointer_count(argv) < 6 || pointer_count(argv) > 8)
	{
		ft_printf(RED"Incorrect CY data <cy X,Y,Z NVector diameter height RGB [checkerboard] [bumpmap]>\n"RST);
		free_pointer(argv);
		free_exit(meta_data);
		exit(EXIT_FAILURE);
	}
	cy = malloc(sizeof(t_cy));
	if (!cy)
	{
		free_pointer(argv);
		free_exit(meta_data);
		exit(EXIT_FAILURE);
	}
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
	cy->checker = 0;
	cy->bump = 0;
	i = 5;
	while (argv[++i])
	{
		bonus = ft_split(argv[i], ',');
		if (bonus[0][0] == 'c')
		{
			cy->checker = 1;
			cy->sqsize = check_checker(&meta_data, cy, argv, bonus);
			free_pointer(bonus);
			if (cy->sqsize.row < 1 || cy->sqsize.col < 1)
			{
				ft_printf(RED"Incorrect checkerboard square size values\n"RST);
				free_exit(meta_data);
				exit(EXIT_FAILURE);
			}
		}
		else if (bonus[0][0] == 't')
		{
			cy->bump = 1;
		}
		else
		{
			free_pointer(bonus);
			ft_printf(RED"Incorrect bonus\n"RST);
			free_exit(meta_data);
			exit(EXIT_FAILURE);
		}
	}
	cy->next = NULL;
	ft_printf(G" OK \n"RST);
	return (cy);
}

/*
	create_cn creates a cone object and check if each value is valid.
	returns t_cn pointer.
*/
t_cn    *create_cn(t_meta *meta_data, char **argv)
{
	char    **coord;
	char    **axis;
	char    **colour;
	t_cn    *cn;
	int	i;
	char	**bonus;

	ft_printf(G"\tCONE OBJECT ...\t\t"RST);
	if (pointer_count(argv) < 6 || pointer_count(argv) > 8)
	{
		ft_printf(RED"Incorrect CN data <cn X,Y,Z Axis Angle Height RGB [checkerboard] [bumpmap]>\n"RST);
		free_pointer(argv);
		free_exit(meta_data);
		exit(EXIT_FAILURE);
	}
	cn = malloc(sizeof(t_cn));
	if (!cn)
	{
		free_pointer(argv);
		free_exit(meta_data);
		exit(EXIT_FAILURE);
	}
	coord = ft_split(argv[1], ',');
	cn->coord = check_coord(&meta_data, cn, argv, coord);
	free_pointer(coord);
	axis = ft_split(argv[2], ',');
	cn->axis = check_norm(&meta_data, cn, argv, axis);
	free_pointer(axis);
	colour = ft_split(argv[5], ',');
	cn->colour = check_colour(&meta_data, cn, argv, colour);
	free_pointer(colour);
	cn->height = check_double(&meta_data, cn, argv, argv[4]);
	cn->angle = check_double(&meta_data, cn, argv, argv[3]);
	if (cn->angle >= 90)
	{
		
		free_pointer(argv);
		free_exit(meta_data);
		exit(EXIT_FAILURE);
	}
	cn->checker = 0;
	cn->bump = 0;
	i = 5;
	while (argv[++i])
	{
		bonus = ft_split(argv[i], ',');
		if (bonus[0][0] == 'c')
		{
			cn->checker = 1;
			cn->sqsize = check_checker(&meta_data, cn, argv, bonus);
			free_pointer(bonus);
			if (cn->sqsize.row < 1 || cn->sqsize.col < 1)
			{
				ft_printf(RED"Incorrect checkerboard square size values\n"RST);
				free_exit(meta_data);
				exit(EXIT_FAILURE);
			}
		}
		else if (bonus[0][0] == 't')
		{
			cn->bump = 1;
		}
		else
		{
			free_pointer(bonus);
			ft_printf(RED"Incorrect bonus\n"RST);
			free_exit(meta_data);
			exit(EXIT_FAILURE);
		}
	}
	cn->next = NULL;
	ft_printf(G" OK \n"RST);
	return (cn);
}
