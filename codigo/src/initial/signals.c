/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:11:19 by frivas            #+#    #+#             */
/*   Updated: 2025/05/14 17:46:32 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_handle_prompt(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("^C", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = SIGINT;
	}
}

void	ms_handle_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("^C", 1);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		g_signal = SIGINT;
	}
}

void	ms_set_signal_handler(int mode)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	if (mode == MODE_PROMPT)
		act.sa_handler = ms_handle_prompt;
	else if (mode == MODE_HEREDOC)
	{
		act.sa_handler = ms_handle_heredoc;
	}
	sigaction(SIGINT, &act, NULL);
}
