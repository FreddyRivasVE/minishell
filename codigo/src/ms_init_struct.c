/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:16:48 by frivas            #+#    #+#             */
/*   Updated: 2025/03/24 14:50:18 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ms_init_struct(t_mshell *data, char **env)
{
    rl_catch_signals = 0;
    data->env = 0;
    data->pipes = 0;
    data->redirs = 0;
    data->commands = 0;
    data->exits = 0;
    data->inputs = 0;
    
    
    
    
}