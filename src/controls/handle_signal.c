/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/09/25 13:52:23 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/26 11:58:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	handle_signal(int signal, siginfo_t *siginfo, void *context)
{
	static t_meta	*meta_data;

	if (siginfo == NULL && context != NULL)
	{
		meta_data = (t_meta *)context;
		return ;
	}
	printf("SIGINT %d captured. Exiting gracefully...\n", signal);
	ft_close(meta_data);
	exit(EXIT_SUCCESS);
}

void	setup_handlesignal(t_meta *meta_data)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		printf("Error with sigaction...\n");
		ft_close(meta_data);
		exit(EXIT_FAILURE);
	}
	handle_signal(0, NULL, meta_data);
}
