/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:52:52 by brivera           #+#    #+#             */
/*   Updated: 2025/03/26 15:24:43 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include "../include/ms_structure.h"
# include <fcntl.h>

void    ms_sigctrlc_handler(int signo);
void	ms_init_struct(t_mshell *data, char **env);
void    print_list_content_char(t_list **lst);
void    ms_get_pront(t_mshell *data);

#endif