/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:41:09 by frivas            #+#    #+#             */
/*   Updated: 2025/03/24 15:36:35 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    t_mshell    		data;
    struct sigaction    sa_ctrlc;
    struct sigaction    sa_quit;
    (void) argv;

    if (argc > 1)
    {
        ft_putendl_fd("Too many arguments!", 2);
        exit(EXIT_FAILURE);
    }
    sa_ctrlc.sa_handler = ms_sigctrlc_handler;
	sa_ctrlc.sa_flags = 0;
	sigaction(SIGINT, &sa_ctrlc, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	ms_init_struct(&data, env);
	return (0);
}