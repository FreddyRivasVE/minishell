/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:11:19 by frivas            #+#    #+#             */
/*   Updated: 2025/03/24 15:29:25 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void   ms_sigctrlc_handler(int signo)
{
    printf("Señal capturada: %d (SIGINT)\n", signo);
}