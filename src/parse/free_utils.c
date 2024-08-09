#include "../../include/miniRT.h"

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

void    free_exit(t_meta *meta_data)
{
    t_light *light;

    light = NULL;
    light = meta_data->light;
    if (meta_data->amlight != NULL)
        free(meta_data->amlight);
    if (meta_data->camera != NULL)
        free(meta_data->camera);
    while (meta_data->light_allocated && meta_data->light != NULL)
    {
        light = light->next;
        free(meta_data->light);
        meta_data->light = NULL;
        meta_data->light = light;
    }
    free_objects(meta_data);
}

void    free_objects(t_meta *meta_data)
{
    t_sp    *sp;
    t_cy    *cy;
    t_pl    *pl;
    t_cn    *cn;

    sp = NULL;
    sp = meta_data->sp;
    cy = NULL;
    cy = meta_data->cy;
    pl = NULL;
    pl = meta_data->pl;
    cn = NULL;
    cn = meta_data->cn;
    while (meta_data->pl_allocated && meta_data->pl != NULL)
    {
        pl = pl->next;
        free(meta_data->pl);
        meta_data->pl = NULL;
        meta_data->pl = pl;
    }
    while (meta_data->sp_allocated && meta_data->sp != NULL)
    {
        sp = sp->next;
        free(meta_data->sp);
        meta_data->sp = NULL;
        meta_data->sp = sp;
    }
    while (meta_data->cy_allocated && meta_data->cy != NULL)
    {
        cy = cy->next;
        free(meta_data->cy);
        meta_data->cy = NULL;
        meta_data->cy = cy;
    }
    while (meta_data->cn_allocated && meta_data->cn != NULL)
    {
        cn = cn->next;
        free(meta_data->cn);
        meta_data->cn = NULL;
        meta_data->cn = cn;
    }
}