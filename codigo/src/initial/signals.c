/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:11:19 by frivas            #+#    #+#             */
/*   Updated: 2025/05/05 18:30:26 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_handle_prompt(int sig)
{
	if (sig == SIGINT)
	{
		printf("^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ms_handle_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		//exit(130);
	}
}

void	ms_handle_child(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
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
		act.sa_handler = ms_handle_child;
	sigaction(SIGINT, &act, NULL);
}
