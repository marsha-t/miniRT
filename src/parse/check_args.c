#include "../../include/miniRT.h"

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