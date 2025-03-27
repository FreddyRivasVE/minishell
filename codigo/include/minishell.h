/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:52:52 by brivera           #+#    #+#             */
/*   Updated: 2025/03/27 11:48:56 by brivera          ###   ########.fr       */
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
# include "../include/ms_struct.h"
# include <fcntl.h>

#define GREEN		"\033[92;1m"
#define CLEAR_COLOR	"\033[0m"
#define CYAN		"\033[96;1m"

void	ms_sigctrlc_handler(int signo);
void	ms_init_struct(t_mshell *data, char **env);
void	print_list_content_char(t_list **lst);
void	ms_get_prompt(t_mshell *data);
//void	ms_loop_minishell(t_mshell *data);

#endif
