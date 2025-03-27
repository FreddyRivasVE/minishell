/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:41:09 by frivas            #+#    #+#             */
/*   Updated: 2025/03/27 23:02:45 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mshell			data;
	struct sigaction	sa_ctrlc;
	struct sigaction	sa_quit;

	(void) argv;
	if (argc > 1)
	{
		ft_putendl_fd("Too many arguments!", 2);
		exit(EXIT_FAILURE);
	}
	sa_ctrlc.sa_handler = ms_sigctrlc_handler;
	sa_ctrlc.sa_flags = 0;
	sigemptyset(&sa_ctrlc.sa_mask);
	sigaction(SIGINT, &sa_ctrlc, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
	ms_init_struct(&data, env);
	ms_loop_minishell(&data);
	return (0);
}
