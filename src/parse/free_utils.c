/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:14:10 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/11 20:14:10 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	free_pointerlist(int num, ...)
{
	va_list	args;
	void	**ptr;
	int		index;

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

int	pointer_count(char **argv)
{
	int	count;

	count = 0;
	while (argv[count])
		count++;
	return (count);
}

void	free_args(t_meta *meta_data, char **argv)
{
	if (argv != NULL)
		free_pointer(argv);
	free_exit(meta_data);
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
