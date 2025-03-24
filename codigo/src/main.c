/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:41:09 by frivas            #+#    #+#             */
/*   Updated: 2025/03/24 13:10:58 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ms_sigbren_handler(int signo)
{
    printf("Señal capturada: %d (SIGINT)\n", signo);
    printf("\n");
    exit(0);
}

int main(int argc, char **argv, char **env)
{
    struct sigaction    sa_bren;
    struct sigaction    sa_quit;
    (void) argv;

    if (argc > 1)
    {
        ft_putendl_fd("Too many arguments!", 2);
        exit(EXIT_FAILURE);
    }
    sa_bren.sa_handler = ms_sigbren_handler;
	sa_bren.sa_flags = 0;
	sigaction(SIGINT, &sa_bren, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	ms_init_struct(env);
	return (0);
}