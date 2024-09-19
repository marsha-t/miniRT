/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:47:43 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/11 17:47:43 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
	create_objects checks argv[0] to the id of each objects. 
	goes to each function of creating each object based on the id
*/
void	create_objects(t_meta *meta_data, char **argv)
{
	if (ft_strncmp(argv[0], "pl", 2) == 0 && ft_strlen(argv[0]) == 2)
		init_plane(meta_data, argv);
	else if (ft_strncmp(argv[0], "sp", 2) == 0 && ft_strlen(argv[0]) == 2)
		init_sphere(meta_data, argv);
	else if (ft_strncmp(argv[0], "cy", 2) == 0 && ft_strlen(argv[0]) == 2)
		init_cylinder(meta_data, argv);
	else if (ft_strncmp(argv[0], "cn", 2) == 0 && ft_strlen(argv[0]) == 2)
		init_cone(meta_data, argv);
}
