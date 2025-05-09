/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:11:19 by frivas            #+#    #+#             */
/*   Updated: 2025/05/09 12:11:38 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_terminal_settings(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag |= (ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

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

void	ms_handle_child(int sig)
{
	if (sig == SIGINT)
	{
		//act.sa_handler = SIG_DFL;
		//ft_putendl_fd("^D", 1);
		//ioctl(STDIN_FILENO, TIOCSTI, "\n");
		//reset_terminal_settings();
		//g_signal = SIGINT;
		//exit(130);
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
	else if (mode == MODE_CHILD)
		act.sa_handler = SIG_DFL;
		//act.sa_handler = ms_handle_child;
	sigaction(SIGINT, &act, NULL);
}
