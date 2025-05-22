/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:25:42 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/05/22 15:18:09 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **env)

{
	t_mshell			data;
	struct sigaction	sa_quit;

	(void) argv;
	if (argc > 1)
	{
		ft_putendl_fd("Too many arguments!", 2);
		exit(EXIT_FAILURE);
	}
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
	ms_init_struct(&data, env);
	if (data.is_interactive)
		ms_loop_minishell(&data);
	else
		ms_loop_minishell_nointeractive(&data);
	return (0);
}
